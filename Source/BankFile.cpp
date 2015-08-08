/*
 * ============================================================================
 *
 * BankFile.cpp
 * Class to hold/import/export a single instrument set (Audiobank format)
 * 
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2015 Sauraen
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

#include "BankFile.h"


BankFile::BankFile(ValueTree romdesc_) : romdesc(romdesc_){
    abfstructsnode = romdesc.getOrCreateChildWithName("abfstructs", nullptr);
    reset();
}

void BankFile::reset(){
    d = ValueTree("bank");
    //Bank data components
    ValueTree temp;
    temp = ValueTree("abindexentry");
    d.addChild(temp, -1, nullptr);
    temp = ValueTree("abheader");
    d.addChild(temp, -1, nullptr);
    temp = ValueTree("abbank");
    d.addChild(temp, -1, nullptr);
    temp = ValueTree("abdrumlist");
    d.addChild(temp, -1, nullptr);
    temp = ValueTree("absfxlist");
    d.addChild(temp, -1, nullptr);
    temp = ValueTree("instruments");
    d.addChild(temp, -1, nullptr);
    temp = ValueTree("drums");
    d.addChild(temp, -1, nullptr);
    temp = ValueTree("sfx");
    d.addChild(temp, -1, nullptr);
    temp = ValueTree("patchprops");
    d.addChild(temp, -1, nullptr);
    temp = ValueTree("samples");
    d.addChild(temp, -1, nullptr);
    temp = ValueTree("aladpcmbooks");
    d.addChild(temp, -1, nullptr);
    temp = ValueTree("aladpcmloops");
    d.addChild(temp, -1, nullptr);
    //Bank data parameters
    d.setProperty("NUM_INST", -1, nullptr);
    d.setProperty("NUM_DRUM", -1, nullptr);
    d.setProperty("NUM_SFX", -1, nullptr);
    d.setProperty("SSIindex", -1, nullptr);
}

/**
 * For a named data structure, returns a copy of the template from the romdesc.
 * Creates it if it does not exist.
 */
ValueTree BankFile::getCopyOfTemplate(String name){
    ValueTree stru = abfstructsnode.getChildWithProperty("name", name);
    if(!stru.isValid()){
        stru = ValueTree("struct");
        stru.setProperty("name", name, nullptr);
        abfstructsnode.addChild(stru, -1, nullptr);
    }
    //Struct local parameters
    if(name == "ALADPCMBook"){
        if(!stru.hasProperty("NUM_PRED")){
            stru.setProperty("NUM_PRED", -1, nullptr);
        }
    }else if(name == "ALADPCMLoop"){
        if(!stru.hasProperty("HAS_TAIL")){
            stru.setProperty("HAS_TAIL", -1, nullptr);
        }
    }
    return stru.createCopy();
}

/**
 * For a list within d with the given name, check if an item exists with the
 * given address. If it doesn't exist, create it. In either case, write back the
 * index within that list of the found/created item to the given node.
 */
void BankFile::checkAddListItem(String listname, int addressval, ValueTree node){
    if(addressval == 0){
        SEQ64::say("Error: trying to add nullptr list item!");
        return;
    }
    ValueTree dstru = d.getChildWithName(listname);
    ValueTree sub = dstru.getChildWithProperty("address", addressval);
    int dstruindex;
    if(sub.isValid()){
        dstruindex = dstru.indexOf(sub);
    }else{
        sub = ValueTree("item");
        sub.setProperty("address", addressval, nullptr);
        dstruindex = dstru.getNumChildren();
        dstru.addChild(sub, dstruindex, nullptr);
    }
    node.setProperty("index", dstruindex, nullptr);
    //Get item name from rdnamesnode
    ValueTree nnlist = rdnamesnode.getOrCreateChildWithName(listname, nullptr);
    ValueTree nnitem = nnlist.getChildWithProperty("index", dstruindex);
    if(!nnitem.isValid()){
        nnitem = ValueTree("item");
        nnitem.setProperty("index", dstruindex, nullptr);
        nnitem.setProperty("name", "[unnamed]", nullptr);
        nnlist.addChild(nnitem, -1, nullptr);
    }
    sub.setProperty("name", nnitem.getProperty("name"), nullptr);
    if(nnitem.hasProperty("map")) sub.setProperty("map", nnitem.getProperty("map"), nullptr);
    if(nnitem.hasProperty("program")) sub.setProperty("program", nnitem.getProperty("program"), nullptr);
    if(nnitem.hasProperty("drum")) sub.setProperty("drum", nnitem.getProperty("drum"), nullptr);
    if(nnitem.hasProperty("transpose")) sub.setProperty("transpose", nnitem.getProperty("transpose"), nullptr);
    if(nnitem.hasProperty("note")) sub.setProperty("note", nnitem.getProperty("note"), nullptr);
    if(nnitem.hasProperty("drumsplit1")) sub.setProperty("drumsplit1", nnitem.getProperty("drumsplit1"), nullptr);
    if(nnitem.hasProperty("drumsplit2")) sub.setProperty("drumsplit2", nnitem.getProperty("drumsplit2"), nullptr);
    if(nnitem.hasProperty("drumsplit3")) sub.setProperty("drumsplit3", nnitem.getProperty("drumsplit3"), nullptr);
}

/**
 * For any of the elements of d which are lists: for the existing contents of
 * the list (with addresses already saved to them), go through each element 
 * and load its struct as a new child of that element.
 */
void BankFile::loadElementList(ROM& rom, uint32 baseaddr, int bank_length, String listname, String elementname){
    //SEQ64::say("Loading element list " + listname + "...");
    uint32 a;
    ValueTree stru = d.getChildWithName(listname);
    ValueTree temp, item;
    int count = stru.getNumChildren();
    int ret;
    for(int i=0; i<count; i++){
        temp = stru.getChild(i);
        a = (int)temp.getProperty("address", 0);
        if(a == 0) continue;
        if(a >= bank_length){
            SEQ64::say("In " + listname + " list, item " + String(i) + ": ptr outside bank @" + ROM::hex(a) + "!"); 
            continue; 
        }
        item = getCopyOfTemplate(elementname);
        temp.addChild(item, -1, nullptr);
        ret = readStruct(rom, a + baseaddr, item);
        if(ret < 0){
            SEQ64::say("Reading " + elementname + " index " + String(i) + " from " + listname + " failed");
            return;
        }
    }
}

/**
 * Load a complete Audiobank file, given the bank number.
 */
bool BankFile::load(ROM& rom, int banknum){
    //Get file and index properties from RomDesc
    ValueTree abiinfonode = romdesc.getChildWithName("knownfilelist")
            .getChildWithProperty("type", "Audiobank Index");
    if(!abiinfonode.isValid()){
        SEQ64::say("Audiobank Index not defined in RomDesc!");
        return false;
    }
    uint32 abiaddr = (int)abiinfonode.getProperty("address");
    if(abiaddr >= rom.getSize()){
        SEQ64::say("Audiobank Index at invalid index " + ROM::hex(abiaddr) + "!");
        return false;
    }
    ValueTree abfinfonode = romdesc.getChildWithName("knownfilelist")
            .getChildWithProperty("type", "Audiobank");
    if(!abfinfonode.isValid()){
        SEQ64::say("Audiobank not defined in RomDesc!");
        return false;
    }
    uint32 abfaddr = (int)abfinfonode.getProperty("address");
    if(abfaddr >= rom.getSize()){
        SEQ64::say("Audiobank at invalid index " + ROM::hex(abfaddr) + "!");
        return false;
    }
    SEQ64::say("Loading bank file from index @" + ROM::hex(abiaddr) 
            + ", bank " + ROM::hex((uint8)banknum) + ", file @" + ROM::hex(abfaddr));
    //Load abindexentry
    uint32 abientryaddr;
    if((int)romdesc.getProperty("indextype", 1) == 2){
        abientryaddr = abiaddr + (16*banknum) + 16;
    }else{
        abientryaddr = abiaddr + (8*banknum) + 4;
    }
    //Load rdnamesnode
    ValueTree temp = romdesc.getOrCreateChildWithName("audiobankidx", nullptr);
    rdnamesnode = temp.getChildWithProperty("index", banknum);
    if(!rdnamesnode.isValid()){
        rdnamesnode = ValueTree("indexentry");
        rdnamesnode.setProperty("index", banknum, nullptr);
        rdnamesnode.setProperty("name", "[unnamed]", nullptr);
        temp.addChild(rdnamesnode, -1, nullptr);
    }
    //Init
    uint32 a, baseaddr;
    int strsize, i, count;
    ValueTree stru, item;
    reset();
    //========================================================================
    //Load index entry
    //========================================================================
    //SEQ64::say("Reading index entry...");
    stru = getCopyOfTemplate("ABIndexEntry");
    d.getChildWithName("abindexentry").addChild(stru, -1, nullptr);
    readStruct(rom, abientryaddr, stru);
    //Copy relevant data from index entry into C++ class
    temp = stru.getChildWithProperty("meaning", "Ptr Bank (in Audiobank)");
    if(!temp.isValid()){
        SEQ64::say("ABIndexEntry must include a field with meaning Ptr Bank (in Audiobank)!");
        return false;
    }
    uint32 ptr_bank = (int)temp.getProperty("value", 0x8000000);
    if(ptr_bank + abfaddr >= rom.getSize()){
        SEQ64::say("Ptr Bank " + ROM::hex(ptr_bank) + " + base " + ROM::hex(abfaddr) + " goes off end of ROM!");
        return false;
    }
    //
    temp = stru.getChildWithProperty("meaning", "Bank Length");
    if(!temp.isValid()){
        SEQ64::say("ABIndexEntry must include a field with meaning Bank Length!");
        return false;
    }
    uint32 bank_length = (int)temp.getProperty("value", 0x8000000);
    if(bank_length >= 0x20000){
        SEQ64::say("Bank Length " + ROM::hex(bank_length) + ", probably wrong!");
        return false;
    }
    //
    temp = stru.getChildWithProperty("meaning", "Sample Set Index number");
    if(temp.isValid()){
        d.setProperty("SSIindex", temp.getProperty("value", 0), nullptr);
    }
    //
    temp = stru.getChildWithProperty("meaning", "NUM_INST");
    if(temp.isValid()){
        d.setProperty("NUM_INST", temp.getProperty("value", 0), nullptr);
    }
    //
    temp = stru.getChildWithProperty("meaning", "NUM_DRUM");
    if(temp.isValid()){
        d.setProperty("NUM_DRUM", temp.getProperty("value", 0), nullptr);
    }
    //
    temp = stru.getChildWithProperty("meaning", "NUM_SFX");
    if(temp.isValid()){
        d.setProperty("NUM_SFX", temp.getProperty("value", 0), nullptr);
    }
    //========================================================================
    //Load bank header
    //========================================================================
    //SEQ64::say("Reading bank header...");
    stru = getCopyOfTemplate("ABHeader");
    d.getChildWithName("abheader").addChild(stru, -1, nullptr);
    a = abfaddr + ptr_bank;
    strsize = readStruct(rom, a, stru);
    a += strsize;
    baseaddr = a;
    //Read relevant data from header
    temp = stru.getChildWithProperty("meaning", "NUM_INST");
    if(temp.isValid()){
        d.setProperty("NUM_INST", temp.getProperty("value", 0), nullptr);
    }
    if((int)d.getProperty("NUM_INST") < 0){
        SEQ64::say("NUM_INST not defined in either ABIndexEntry or ABHeader!");
        return false;
    }
    //========================================================================
    //Load bank (main)
    //========================================================================
    //SEQ64::say("Reading bank main...");
    stru = getCopyOfTemplate("ABBank");
    d.getChildWithName("abbank").addChild(stru, -1, nullptr);
    strsize = readStruct(rom, a, stru);
    a += strsize;
    //========================================================================
    //Load DrumList and SFXList if they exist
    //========================================================================
    temp = d.getChildWithName("abdrumlist");
    if((int)temp.getProperty("address", -1) > 0){
        a = baseaddr + (int)temp.getProperty("address");
        SEQ64::say("Reading ABDrumList from @" + ROM::hex(a));
        stru = getCopyOfTemplate("ABDrumList");
        d.getChildWithName("abdrumlist").addChild(stru, -1, nullptr);
        readStruct(rom, a, stru);
    }else{
        SEQ64::say("No ABDrumList found");
    }
    temp = d.getChildWithName("absfxlist");
    if((int)temp.getProperty("address", -1) > 0){
        a = baseaddr + (int)temp.getProperty("address");
        SEQ64::say("Reading ABSFXList from @" + ROM::hex(a));
        stru = getCopyOfTemplate("ABSFXList");
        d.getChildWithName("absfxlist").addChild(stru, -1, nullptr);
        readStruct(rom, a, stru);
    }else{
        SEQ64::say("No ABSFXList found");
    }
    //========================================================================
    //Load lists of elements
    //========================================================================
    loadElementList(rom, baseaddr, bank_length, "instruments", "ABInstrument");
    loadElementList(rom, baseaddr, bank_length, "drums", "ABDrum");
    loadElementList(rom, baseaddr, bank_length, "sfx", "ABSound");
    loadElementList(rom, baseaddr, bank_length, "patchprops", "ABPatchProps");
    loadElementList(rom, baseaddr, bank_length, "samples", "ABSample");
    loadElementList(rom, baseaddr, bank_length, "aladpcmbooks", "ALADPCMBook");
    loadElementList(rom, baseaddr, bank_length, "aladpcmloops", "ALADPCMLoop");
    SEQ64::say("Done loading bank!");
    return true;
}
bool BankFile::save(ROM& rom, int banknum){
    //TODO
    return false;
}

int BankFile::readStruct(ROM& rom, uint32 addr, ValueTree stru){
    if(!stru.isValid()) return -1;
    int len = 0, fieldlen, fieldelementlen;
    int count = stru.getNumChildren();
    String struname = stru.getProperty("name", "Error");
    ValueTree field, sub, dstru, fieldelement;
    String datatype, ptrto, arraylenvar, meaning;
    bool ispointer, isarray, arrayloopflag;
    int arraylenfixed;
    uint32 a = addr;
    int val;
    int dstruindex;
    int arraycount, arraymax;
    for(int i=0; i<count; i++){
        field = stru.getChild(i);
        //Load field properties from stru
        datatype = field.getProperty("datatype", "uint32").toString();
        ispointer = field.getProperty("ispointer", false);
        if(ispointer){
            ptrto = field.getProperty("ptrto", "").toString();
        }else{
            ptrto = "";
        }
        isarray = field.getProperty("isarray", false);
        if(isarray){
            if(field.hasProperty("arraylenfixed")){
                arraylenfixed = field.getProperty("arraylenfixed", 0);
                arraylenvar = "";
                arraymax = arraylenfixed;
            }else{
                arraylenfixed = -1;
                arraylenvar = field.getProperty("arraylenvar", 0).toString();
                arraymax = -1;
                if(d.hasProperty(arraylenvar)){
                    arraymax = (int)d.getProperty(arraylenvar);
                }else if(stru.hasProperty(arraylenvar)){
                    arraymax = (int)stru.getProperty(arraylenvar);
                }else{
                    SEQ64::say("Invalid array length variable " + arraylenvar + "!");
                    return -1;
                }
                if(arraymax < 0){
                    SEQ64::say("Array length using not-yet-set variable " + arraylenvar + "!");
                    return -1;
                }
            }
        }
        meaning = field.getProperty("meaning", "None").toString();
        //Read data from ROM
        arrayloopflag = true;
        fieldlen = 0;
        arraycount = -1;
        while(arrayloopflag){
            //Pre-deal with arrays
            if(isarray){
                arraycount++;
                if(arraycount >= arraymax) break;
                fieldelement = ValueTree("element");
                fieldelement.setProperty("datatype", datatype, nullptr);
                field.addChild(fieldelement, -1, nullptr);
            }else{
                arrayloopflag = false;
                fieldelement = field;
            }
            //Read actual data
            if(datatype == "uint32" || datatype == "int32"){
                val = rom.readWord(a);
                fieldelementlen = 4;
            }else if(datatype == "uint16"){
                val = rom.readHalfWord(a);
                fieldelementlen = 2;
            }else if(datatype == "int16"){
                val = (int16)rom.readHalfWord(a);
                fieldelementlen = 2;
            }else if(datatype == "uint8"){
                val = rom.readByte(a);
                fieldelementlen = 1;
            }else if(datatype == "int8"){
                val = (int8)rom.readByte(a);
                fieldelementlen = 1;
            }else if(datatype == "ABSound" || datatype == "ALADPCMPredictor" || datatype == "ALADPCMTail"){
                sub = getCopyOfTemplate(datatype);
                fieldelement.addChild(sub, -1, nullptr);
                fieldelementlen = readStruct(rom, a, sub);
                val = 0;
            }else{
                SEQ64::say("Invalid data type " + datatype + "!");
                return -1;
            }
            //Length, address, data
            fieldlen += fieldelementlen;
            a += fieldelementlen;
            fieldelement.setProperty("value", val, nullptr);
            //Meaning
            if(ispointer && val != 0){
                if(ptrto == "ABHeader"){
                    //do nothing
                }else if(ptrto == "ABDrumList"){
                    dstru = d.getChildWithName("abdrumlist");
                    dstru.setProperty("address", val, nullptr);
                }else if(ptrto == "ABSFXList"){
                    dstru = d.getChildWithName("absfxlist");
                    dstru.setProperty("address", val, nullptr);
                }else if(ptrto == "ABInstrument"){
                    checkAddListItem("instruments", val, field);
                }else if(ptrto == "ABDrum"){
                    checkAddListItem("drums", val, field);
                }else if(ptrto == "ABPatchProps"){
                    checkAddListItem("patchprops", val, field);
                }else if(ptrto == "ABSample"){
                    checkAddListItem("samples", val, field);
                }else if(ptrto == "ATSample"){
                    //do nothing
                }else if(ptrto == "ALADPCMBook"){
                    checkAddListItem("aladpcmbooks", val, field);
                }else if(ptrto == "ALADPCMLoop"){
                    checkAddListItem("aladpcmloops", val, field);
                }else{
                    SEQ64::say("Invalid pointer type " + ptrto + "!");
                    return -1;
                }
            }
            if(meaning == "NUM_INST" || meaning == "NUM_DRUM" || meaning == "NUM_SFX"){
                if(isarray){
                    SEQ64::say("Array cannot have meaning " + meaning + "!");
                }else{
                    if((int)d.getProperty(meaning) >= 0){
                        SEQ64::say("Overwriting global property " + meaning + " with value " + String(val));
                    }
                    d.setProperty(meaning, val, nullptr);
                }
            }else if(meaning == "NUM_PRED" || meaning == "HAS_TAIL" || meaning == "Loop Start"){
                if(isarray){
                    SEQ64::say("Array cannot have meaning " + meaning + "!");
                }else{
                    if(meaning == "Loop Start"){
                        int ht = (val > 0) ? 1 : 0;
                        //SEQ64::say("Loop Start " + String(val) + ", setting HAS_TAIL to " + String(ht));
                        stru.setProperty("HAS_TAIL", ht, nullptr);
                    }else{
                        if((int)stru.getProperty(meaning) >= 0){
                            SEQ64::say("Overwriting local property " + meaning + " with value " + String(val));
                        }
                        stru.setProperty(meaning, val, nullptr);
                    }
                }
            }
        }
        len += fieldlen;
    }
    return len;
}
int BankFile::writeStruct(ROM& rom, uint32 addr, ValueTree stru){
    //TODO
	return -1;
}

int BankFile::getLength(){
    //TODO
	return -1;
}

int BankFile::getLength(ValueTree stru){
    if(!stru.isValid()) return 0;
    int count = stru.getNumChildren();
    int len = 0, baselen;
    ValueTree field, fieldstruct;
    String datatype;
    for(int i=0; i<count; i++){
        field = stru.getChild(i);
        datatype = field.getProperty("datatype", "uint32");
        if(datatype == "uint8" || datatype == "int8"){
            baselen = 1;
        }else if(datatype == "uint16" || datatype == "int16"){
            baselen = 2;
        }else if(datatype == "uint32" || datatype == "int32"){
            baselen = 4;
        }else{
            fieldstruct = abfstructsnode.getChildWithProperty("name", datatype);
            if(!fieldstruct.isValid()){
                SEQ64::say("Could not find struct named " + datatype + "!");
                baselen = 4;
            }else{
                baselen = getLength(fieldstruct);
            }
        }
        //TODO variable array lengths
    }
}

