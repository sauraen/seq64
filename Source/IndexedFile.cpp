/*
 * ============================================================================
 *
 * IndexedFile.cpp
 * Manipulation of indexed files (Audiobank, Audioseq, Audiotable)
 * 
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2018 Sauraen
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ============================================================================
*/

#include "IndexedFile.h"
#include "seq64.h"

IndexedFile::IndexedFile(ROM &rom_, ValueTree &romdesc_, String filename)
        : rom(rom_), romdesc(romdesc_), fname(filename){
    warnedOutsideFile = false;
    allowOutsideFile = true;
    iname = fname + " Index";
    cname = fname.toLowerCase().substring(5);
    reloadFileProps();
}

IndexedFile::~IndexedFile(){
    //nothing
}

void IndexedFile::invalidateFileProps(){
    iaddr = idataend = irealend = 0;
    faddr = fdataend = frealend = 0;
    icount = -1;
}
bool IndexedFile::reloadFileProps(){
    //SEQ64::say("Loading file properties for " + fname + " (and its index)...");
    indextype = (int)romdesc.getProperty("indextype", 1);
    if(indextype == 2){
        it_hdrlen = 16;
        it_entrylen = 16;
    }else{
        it_hdrlen = 4;
        it_entrylen = 8;
    }
    idxlistnode = romdesc.getOrCreateChildWithName("audio" + cname + "idx", nullptr);
    ValueTree kfilelistnode = romdesc.getOrCreateChildWithName("knownfilelist", nullptr);
    //Index parameters
    ValueTree indexnode = kfilelistnode.getChildWithProperty("type", iname);
    iaddr = indexnode.isValid() ? (int)indexnode.getProperty("address", 0) : 0;
    if(iaddr == 0 || rom.getSize() <= iaddr + 4){
        SEQ64::say("Bad " + iname + " iaddr = " + ROM::hex(iaddr));
        invalidateFileProps();
        return false;
    }
    icount = readICount();
    if(icount > 1000 || icount <= 0){
        SEQ64::say("Bad " + iname + " icount = " + ROM::hex((uint32)icount));
        invalidateFileProps();
        return false;
    }
    idataend = iaddr + it_hdrlen + (it_entrylen * icount);
    irealend = getRealEnd(rom, idataend);
    irealend = correctOverzealousRealEnd(irealend, -1);
    if((int)indexnode.getProperty("length", -1) != irealend - iaddr){
        SEQ64::say("Updating " + iname + " length to " + ROM::hex(irealend - iaddr));
    }
    indexnode.setProperty("length", (int)(irealend - iaddr), nullptr);
    //SEQ64::say(iname + ": minimum len 0x" + ROM::hex((uint32)(idataend - iaddr))
    //        + ", maximum len 0x"+ ROM::hex((uint32)(irealend - iaddr)));
    //File parameters
    ValueTree filenode = kfilelistnode.getChildWithProperty("type", fname);
    faddr = filenode.isValid() ? (int)filenode.getProperty("address", 0) : 0;
    if(faddr == 0 || rom.getSize() <= faddr + 4){
        SEQ64::say("Bad " + fname + " faddr = " + ROM::hex(faddr));
        invalidateFileProps();
        return false;
    }
    //Determine "file end"
    int fend_ext = -1;
    bool fend_from_mft = false;
    if((bool)filenode.getProperty("from_ft", false)){
        //Try loading from MFT
        int ftaddr = (int)romdesc.getProperty("ftaddr", 0);
        int ftindex = filenode.getProperty("ftindex", -1);
        if(ftaddr > 0 && ftaddr < rom.getSize() && ftindex >= 0){
            //Check address
            if(rom.readWord(ftaddr + 0x10*ftindex) == faddr){
                fend_ext = rom.readWord(ftaddr + 0x10*ftindex + 0x04);
                fend_from_mft = true;
            }else{
                SEQ64::say("Internal error reading MFT!");
            }
        }else{
            SEQ64::say("Invalid MFT address or index!");
        }
    }
    if(fend_ext < 0){
        SEQ64::say(fname + " not in MFT so guessing its end/length");
        //Starting from the beginning of the file, the first data
        //which is neither part of any object nor all zeros, is the
        //beginning of the next file
        bool still_looking = true;
        uint32 a = faddr;
        if(faddr == iaddr) a = idataend; //Don't clobber the index!
        uint32 confident_end = a;
        while(still_looking){
            //Get next nonzero
            while(a < rom.getSize() && rom.readByte(a) == 0) ++a;
            //See if this is in an object
            still_looking = false;
            for(int o=0; o<icount; ++o){
                uint32 oaddr, olen;
                getObjectAddrLen(o, oaddr, olen);
                if(olen == 0) continue;
                if(a >= faddr + oaddr && a < faddr + oaddr + olen){
                    a = faddr + oaddr + olen;
                    confident_end = a;
                    o = -1; //Restart loop through objects
                    still_looking = true;
                }
            }
        }
        //a is now pointing to first nonzero data not claimed by any object
        fend_ext = (a >> 4) << 4; //Round down
        if(confident_end > fend_ext) fend_ext = confident_end; //In case we rounded down into an object
        SEQ64::say("Guessed " + fname + " end @" + ROM::hex((uint32)fend_ext) + " (length " + ROM::hex((uint32)(fend_ext - faddr)) + ")");
    }
    filenode.setProperty("length", (int)(fend_ext - faddr), nullptr);
    //File data end and real end
    bool outsidefile = false;
    fdataend = faddr;
    for(int o=0; o<icount; ++o){
        uint32 oaddr, olen;
        getObjectAddrLen(o, oaddr, olen);
        if(olen == 0) continue;
        uint32 dend = oaddr + olen + faddr;
        if(dend > fend_ext && allowOutsideFile){
            SEQ64::say(iname + ": object " + String(o) + " outside file, ends @" + ROM::hex(dend));
            outsidefile = true;
            continue;
        }
        if(dend > fdataend) fdataend = dend;
    }
    frealend = getRealEnd(rom, fdataend);
    //SEQ64::say(fname + " file: minimum len 0x" + ROM::hex((uint32)(fdataend - faddr))
    //        + ", maximum len 0x"+ ROM::hex((uint32)(frealend - faddr)));
    if(!warnedOutsideFile && outsidefile){
        warnedOutsideFile = true;
        if(!NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon,
                    "Better read this one", 
                    fend_from_mft ? 
                    ("One or more " + cname + "s in " + iname + " were found to be outside " + fname
                    + " as defined in the Master File Table. This is partially supported, but "
                    "some features such as Compact may not work properly.\n\n"
                    "Click OK to accept this and continue, or click Cancel to turn off support "
                    "for " + cname + "s outside " + fname + " for this session (i.e. rescan "
                    + iname + " and force the end of " + fname + " to be the last end of a " + cname + ").")
                    :
                    ("Since " + fname + " was not defined in the Master File Table (or there isn't one), "
                    "seq64 scans " + fname + " to find the first data which does not belong to a " + cname +
                    " and is also not zero, and considers this to be the end of Audioseq--it's the first data "
                    "which is probably something else in the ROM.\n\n"
                    "After this process, one or more " + cname + "s in " + iname + 
                    " were found to be outside " + fname + ". This is partially supported, but "
                    "some features such as Compact may not work properly.\n\n"
                    "If you have good reason to believe there are supposed to be " + cname + "s outside "
                    + fname + ", click OK to accept this and continue.\n"
                    "If you think it's more likely that somehow garbage data got in the blank space "
                    "between " + cname + "s--perhaps a " + cname + " was manually written over a larger "
                    "one and the end of the old one was not cleared to zero--click Cancel and seq64 will rescan "
                    + iname + " and force the end of " + fname + " to be the last end of a " + cname + ".")
                    , nullptr, nullptr)){
            allowOutsideFile = false;
            return reloadFileProps(); //recursion, but warnedOutsideFile is now true so it won't happen again
        }
    }
    return true;
}

bool IndexedFile::writeFileLen(uint32 flen){
    ValueTree kfilelistnode = romdesc.getOrCreateChildWithName("knownfilelist", nullptr);
    ValueTree kfile = kfilelistnode.getChildWithProperty(Identifier("type"), fname);
    if(!kfile.isValid()){
        SEQ64::say("Internal error writing file length");
        return false;
    }
    //Update file length in RomDesc
    kfile.setProperty("length", (int)flen, nullptr);
    if((bool)kfile.getProperty("from_ft", false)){
        //Update file length in MFT
        int ftaddr = (int)romdesc.getProperty("ftaddr", 0);
        int ftindex = kfile.getProperty("ftindex", -1);
        if(ftaddr <= 0 || ftaddr > rom.getSize() || ftindex < 0){
            SEQ64::say("Invalid Master File Table or entry");
            return false;
        }
        //Sanity check
        if(rom.readWord(ftaddr + 0x10*ftindex) != faddr){
            SEQ64::say("Internal error editing Master File Table");
            return false;
        }
        rom.writeWord(ftaddr + 0x10*ftindex + 0x04, faddr + flen);
        SEQ64::say("Updated file length in MFT to 0x" + ROM::hex((uint32)flen, 6));
    }
    return true;
}

int16 IndexedFile::readICount(){
    return rom.readHalfWord(iaddr + ((indextype == 2) ? 0 : 2));
}

void IndexedFile::writeICount(int16 count){
    SEQ64::say("Changing " + iname + " from " + String(icount) + " to " + String(count) + " entries");
    rom.writeHalfWord(iaddr + ((indextype == 2) ? 0 : 2), count);
    icount = count;
    reloadFileProps();
}
    
bool IndexedFile::getObjectAddrLen(int o, uint32 &addr_within_file, uint32 &len){
    if(iaddr == 0 || o >= icount || o < 0) return false;
    addr_within_file = rom.readWord(iaddr + (it_entrylen*o) + it_hdrlen);
    len = rom.readWord(iaddr + (it_entrylen*o) + it_hdrlen + 4);
    return true;
}

bool IndexedFile::setObjectAddr(int o, uint32 addr){
    if(iaddr == 0 || o >= icount || o < 0) return false;
    rom.writeWord(iaddr + (it_entrylen*o) + it_hdrlen, addr);
    return true;
}

bool IndexedFile::setObjectLen(int o, uint32 len){
    if(iaddr == 0 || o >= icount || o < 0) return false;
    rom.writeWord(iaddr + (it_entrylen*o) + it_hdrlen + 4, len);
    return true;
}

bool IndexedFile::getObjectMetadata(int o, uint32 &md1, uint32 &md2){
    if(iaddr == 0 || o >= icount || o < 0) return false;
    if(indextype == 1){
        md1 = md2 = 0;
        return true;
    }
    md1 = rom.readWord(iaddr + (it_entrylen*o) + it_hdrlen + 8);
    md2 = rom.readWord(iaddr + (it_entrylen*o) + it_hdrlen + 12);
    return true;
}

bool IndexedFile::setObjectMetadata(int o, uint32 md1, uint32 md2){
    if(iaddr == 0 || o >= icount || o < 0) return false;
    if(indextype == 1) return false;
    rom.writeWord(iaddr + (it_entrylen*o) + it_hdrlen + 8, md1);
    rom.writeWord(iaddr + (it_entrylen*o) + it_hdrlen + 12, md2);
    return true;
}

String IndexedFile::getObjectName(int o){
    if(iaddr == 0 || o >= icount || o < 0) return "ERROR";
    ValueTree entry = idxlistnode.getChildWithProperty("index", o);
    if(entry.isValid()){
        return entry.getProperty("name", "").toString();
    }else{
        return "";
    }
}
bool IndexedFile::setObjectName(int o, String name){
    if(iaddr == 0 || o >= icount || o < 0) return false;
    ValueTree entry = idxlistnode.getChildWithProperty("index", o);
    if(name.isEmpty()){
        if(entry.isValid()){
            idxlistnode.removeChild(entry, nullptr);
        }
        return true;
    }
    if(!entry.isValid()){
        entry = ValueTree(Identifier("indexentry"));
        entry.setProperty("index", o, nullptr);
        idxlistnode.addChild(entry, idxlistnode.getNumChildren(), nullptr);
    }
    entry.setProperty("name", name, nullptr);
    return true;
}

String IndexedFile::getObjectDescription(int o){
    if(iaddr == 0 || o >= icount || o < 0) return "ERROR";
    uint32 addr, len, availsize;
    getObjectAddrLen(o, addr, len);
    String ret = ROM::hex((uint8)o) + " @" + ROM::hex(addr, 6) + " len " + ROM::hex(len, 
            iname == "Audiotable Index" ? 6 : 4);
    getObjectRealSize(o, availsize);
    if(availsize != len){
        ret += " (avail " + ROM::hex((uint32)availsize, 6) + ")";
    }
    String name = getObjectName(o);
    if(!name.isEmpty()) ret += ": " + name;
    return ret;
}
    
uint32 IndexedFile::getRealEnd(ROM &therom, uint32 dataend){
    uint32 realend;
    for(realend = dataend; realend < therom.getSize(); ++realend){
        if(therom.readByte(realend) != 0) break;
    }
    realend = (realend >> 4) << 4;
    if(dataend > realend) realend = dataend;
    return realend;
}

uint32 IndexedFile::correctOverzealousRealEnd(uint32 supposedrealend, int o_if_applicable){
    //Check that we're not grabbing the beginning of the next file,
	//in case the next file starts with a bunch of zeros (possible in Audiobank)
    for(int i=0; i<icount; ++i){
        if(i==o_if_applicable) continue;
        uint32 addr, len;
        getObjectAddrLen(i, addr, len);
        if(len == 0) continue;
        addr += faddr;
        if(supposedrealend >= addr && supposedrealend < addr + len){
            supposedrealend = addr;
        }
    }
    return supposedrealend;
}

bool IndexedFile::getObjectRealSize(int o, uint32 &realsize){
    uint32 oaddr, olen;
    if(!getObjectAddrLen(o, oaddr, olen)) return false;
    if(olen == 0){
        realsize = 0;
        return true;
    }
    uint32 realend = getRealEnd(rom, faddr+oaddr+olen);
	realend = correctOverzealousRealEnd(realend, o);
    realsize = realend-(faddr+oaddr);
    return true;
}

void IndexedFile::moveRestOfFile(uint32 dstart, int32 delta){
    uint32 flen = fdataend - faddr;
    uint8* fileptr = &((uint8*)rom.getData())[faddr];
    memmove(&fileptr[dstart+delta], &fileptr[dstart], flen - dstart);
    uint32 zstart = delta > 0 ? dstart : flen+delta;
    memset(&fileptr[zstart], 0, abs(delta)); //Zero region moved out of
    //Adjust later addresses in table
    for(int i=0; i<icount; ++i){
        uint32 oaddr, olen;
        getObjectAddrLen(i, oaddr, olen);
        if(olen == 0) continue;
        if(oaddr >= dstart && oaddr < flen){
            setObjectAddr(i, oaddr+delta);
        }
    }
}
    
bool IndexedFile::compact(){
    if(faddr == 0 || iaddr == 0 || icount < 0) return false;
    int possibleend, realend;
    //Minimize lengths of each object
    for(int i=0; i<icount; ++i){
        uint32 oaddr, olen;
        getObjectAddrLen(i, oaddr, olen);
        if(olen == 0) continue;
        for(realend=oaddr+olen+faddr-1; realend>=0; --realend){
            if(rom.readByte(realend) != 0) break;
        }
        ++realend; //Address after nonzero byte
        realend = ((realend + 15) >> 4) << 4; //Round up to multiple of 16
        if(oaddr+olen+faddr < realend){
            //We've actually grown the object instead--make sure we didn't
            //round up over someone else's data
            for(int b=oaddr+olen+faddr; b<realend; ++b){
                if(rom.readByte(b) != 0){
                    realend = b;
                    break;
                }
            }
        }
        if(oaddr+olen+faddr != realend){
            SEQ64::say("Changed length of item " + String(i) + " from 0x"
                    + ROM::hex(olen, 6) + " to 0x" + ROM::hex(realend-oaddr-faddr, 6));
        }
        setObjectLen(i, realend-oaddr-faddr);
    }
    //Get actual lengths of file and index (i.e. length until later non-zero data)
    uint32 ilen = irealend - iaddr;
    uint32 flen = frealend - faddr;
    //Compact
    int a = 0;
    if(iaddr == faddr) a = ilen; //Mario 64 format, don't clobber the index!
    while(a < flen){
        //Move to the next space not taken by any object
        for(int i=0; i<icount; ++i){
            uint32 oaddr, olen;
            getObjectAddrLen(i, oaddr, olen);
            if(olen == 0) continue;
            if(a >= oaddr && a < oaddr + olen){
                a = oaddr + olen;
                a = ((a + 15) >> 4) << 4; //round up
                i = -1; //Restart search through objects
            }
        }
        if(a >= flen) break;
        //Compute empty space to next object
        int nextoaddr = 1000000000;
        for(int i=0; i<icount; ++i){
            uint32 oaddr, olen;
            getObjectAddrLen(i, oaddr, olen);
            if(olen == 0) continue;
            if(oaddr >= a && oaddr < nextoaddr){
                nextoaddr = oaddr;
            }
        }
        if(nextoaddr >= flen){
            SEQ64::say("0x" + ROM::hex((uint32)(flen - a), 6) + " bytes empty at end");
            flen = a;
            break;
        }
        int delta = nextoaddr - a;
        if(delta <= 0){
            SEQ64::say("Internal error when compacting");
            return false;
        }
        SEQ64::say("Compacting away 0x" + ROM::hex((uint32)delta, 6) + " bytes of space");
        //Move later part of file down
        moveRestOfFile(nextoaddr, -delta);
    }
    if(!writeFileLen(flen)) return false;
    reloadFileProps();
    return true;
}

bool IndexedFile::makeRoom(int o, uint32 newtotallen){
    if(iaddr == 0 || o >= icount || o < 0) return false;
    //Get object params
    uint32 oaddr, olen;
    getObjectAddrLen(o, oaddr, olen);
    if(olen == 0){
        SEQ64::say("This is a pointer, not a real " + cname + "!");
        return false;
    }
    if(olen >= newtotallen){
        SEQ64::say("Asked to make room for entry " + String(o) + " to be 0x"
                + ROM::hex((uint32)newtotallen, 6) + " bytes, but it's already "
                + ROM::hex(olen, 6) + " bytes");
        return false;
    }
    //Get file params
    if(frealend - fdataend < newtotallen - olen){
        SEQ64::say("Need 0x" + ROM::hex((uint32)(newtotallen - olen), 6)
                + " bytes empty space to make room, but there are only 0x"
                + ROM::hex((uint32)(frealend - fdataend), 6) + " bytes empty at the end of "
                + fname + " file");
        return false;
    }
    //Move data
    SEQ64::say("Inserting 0x" + ROM::hex((uint32)(newtotallen-olen), 6) + " bytes empty space @"
            + ROM::hex((uint32)(oaddr+olen), 6));
    moveRestOfFile(oaddr+olen, newtotallen-olen);
    if(!writeFileLen(fdataend+newtotallen-olen)) return false;
    reloadFileProps();
    return true;
}

bool IndexedFile::createContents(int o){
    if(iaddr == 0 || o >= icount || o < 0) return false;
    uint32 addr, len;
    getObjectAddrLen(o, addr, len);
    if(len != 0){
        SEQ64::say("This entry already has contents!");
        return false;
    }
    if(frealend - fdataend < 0x10){
        SEQ64::say("There is no room at the end of " + fname + " for a new object!");
        return false;
    }
    memset(&((uint8*)rom.getData())[fdataend], 0xFF, 0x10);
    setObjectAddr(o, fdataend-faddr);
    setObjectLen(o, 0x10);
    if(!writeFileLen(fdataend-faddr+0x10)) return false;
    setObjectName(o, "New " + cname);
    reloadFileProps();
    return true;
}

bool IndexedFile::destroyContents(int o){
    if(iaddr == 0 || o >= icount || o < 0) return false;
    uint32 addr, len;
    getObjectAddrLen(o, addr, len);
    if(len == 0){
        SEQ64::say("This entry already doesn't have any contents!");
        return false;
    }
    memset(&((uint8*)rom.getData())[faddr+addr], 0, len);
    setObjectAddr(o, 0);
    setObjectLen(o, 0);
    setObjectName(o, "(Blank entry)");
    reloadFileProps();
    return true;
}

bool IndexedFile::addEntry(bool fromInsert){
    if(iaddr == 0 || icount <= 0) return false;
    if(irealend - idataend < it_entrylen){
        SEQ64::say("There is no room at the end of " + iname + " for a new entry!");
        return false;
    }
    writeICount(icount + 1); //This also updates icount
    if(!fromInsert) addBlankName(icount-1);
    return true;
}

bool IndexedFile::insertEntry(int o){
    if(iaddr == 0 || o >= icount || o < 0) return false;
    if(!addEntry(true)) return false;
    uint8* d = &((uint8*)rom.getData())[iaddr];
    memmove(&d[it_hdrlen + it_entrylen*(o+1)],
            &d[it_hdrlen + it_entrylen* o],
            (icount - 1 - o) * it_entrylen);
    memset( &d[it_hdrlen + it_entrylen* o], 0, it_entrylen);
    fixIndexNames(true, o);
    addBlankName(o);
    return true;
}

bool IndexedFile::removeEntry(int o){
    if(iaddr == 0 || o >= icount || o < 0) return false;
    uint8* d = &((uint8*)rom.getData())[iaddr];
    memmove(&d[it_hdrlen + it_entrylen* o],
            &d[it_hdrlen + it_entrylen*(o+1)],
            (icount - o - 1) * it_entrylen);
    memset( &d[it_hdrlen + it_entrylen*(icount-1)], 0, it_entrylen);
    writeICount(icount - 1); //This also updates icount
    fixIndexNames(false, o);
    return true;
}

void IndexedFile::addBlankName(int idx){
    ValueTree newentry("indexentry");
    newentry.setProperty("index", idx, nullptr);
    newentry.setProperty("name", "(Blank entry)", nullptr);
    idxlistnode.addChild(newentry, -1, nullptr);
}

void IndexedFile::fixIndexNames(bool add, int idx){
    for(int i=0; i<idxlistnode.getNumChildren(); ++i){
        ValueTree entry = idxlistnode.getChild(i);
        int eidx = entry.getProperty("index", -1);
        if(eidx == idx && !add){
            idxlistnode.removeChild(i, nullptr);
            --i;
        }else if(eidx >= idx){
            entry.setProperty("index", eidx + (add ? 1 : -1), nullptr);
        }
    }
}
    













