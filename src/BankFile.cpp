/*
 * ============================================================================
 *
 * BankFile.cpp
 * Class to hold/import/export a single bank (Audiobank format)
 * 
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2019 Sauraen
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
#include "ROM.h"
#include "seq64.h"

#define ALIGN(a, b) a += (b-1); a /= b; a *= b; do{((void)0);}while(false)


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
    temp = ValueTree("envelopes");
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
    d.setProperty("ATnum", -1, nullptr);
}

void BankFile::loadRDNamesNode(int banknum){
    //Load rdnamesnode
    ValueTree temp = romdesc.getOrCreateChildWithName("audiobankidx", nullptr);
    rdnamesnode = temp.getChildWithProperty("index", banknum);
    if(!rdnamesnode.isValid()){
        rdnamesnode = ValueTree("indexentry");
        rdnamesnode.setProperty("index", banknum, nullptr);
        rdnamesnode.setProperty("name", "[unnamed]", nullptr);
        temp.addChild(rdnamesnode, -1, nullptr);
    }
}
void BankFile::clearRDNamesNode(){
    if(!rdnamesnode.isValid()) return;
    rdnamesnode.removeAllChildren(nullptr);
}
void BankFile::copyRDItemPropsToItem(String listname, int itemindex, ValueTree dest){
    dest.setProperty("name", "[unnamed]", nullptr);
    if(!rdnamesnode.isValid()) return;
    ValueTree list = rdnamesnode.getChildWithName(listname);
    if(!list.isValid()) return;
    ValueTree item = list.getChildWithProperty("index", itemindex);
    if(!item.isValid()) return;
                                       dest.setProperty("name",       item.getProperty("name", "[unnamed]"), nullptr);
    if(item.hasProperty("map"))        dest.setProperty("map",        item.getProperty("map"), nullptr);
    if(item.hasProperty("program"))    dest.setProperty("program",    item.getProperty("program"), nullptr);
    if(item.hasProperty("drum"))       dest.setProperty("drum",       item.getProperty("drum"), nullptr);
    if(item.hasProperty("transpose"))  dest.setProperty("transpose",  item.getProperty("transpose"), nullptr);
    if(item.hasProperty("note"))       dest.setProperty("note",       item.getProperty("note"), nullptr);
    if(item.hasProperty("drumsplit1")) dest.setProperty("drumsplit1", item.getProperty("drumsplit1"), nullptr);
    if(item.hasProperty("drumsplit2")) dest.setProperty("drumsplit2", item.getProperty("drumsplit2"), nullptr);
    if(item.hasProperty("drumsplit3")) dest.setProperty("drumsplit3", item.getProperty("drumsplit3"), nullptr);
}
void BankFile::copyItemPropsToRDItem(String listname, int itemindex, ValueTree source){
    if(!rdnamesnode.isValid()) return;
    ValueTree list = rdnamesnode.getOrCreateChildWithName(listname, nullptr);
    ValueTree item = list.getChildWithProperty("index", itemindex);
    if(!item.isValid()){
        item = ValueTree("item");
        item.setProperty("index", itemindex, nullptr);
        list.addChild(item, -1, nullptr);
    }
    bool anyData = false;
    if(source.getProperty("name", "[unnamed]").toString() != "[unnamed]") anyData = true;
                                          item.setProperty("name",       source.getProperty("name", "[unnamed]"), nullptr);
    if(source.hasProperty("map"))        {item.setProperty("map",        source.getProperty("map"), nullptr);        anyData = true; }
    if(source.hasProperty("program"))    {item.setProperty("program",    source.getProperty("program"), nullptr);    anyData = true; }
    if(source.hasProperty("drum"))       {item.setProperty("drum",       source.getProperty("drum"), nullptr);       anyData = true; }
    if(source.hasProperty("transpose"))  {item.setProperty("transpose",  source.getProperty("transpose"), nullptr);  anyData = true; }
    if(source.hasProperty("note"))       {item.setProperty("note",       source.getProperty("note"), nullptr);       anyData = true; }
    if(source.hasProperty("drumsplit1")) {item.setProperty("drumsplit1", source.getProperty("drumsplit1"), nullptr); anyData = true; }
    if(source.hasProperty("drumsplit2")) {item.setProperty("drumsplit2", source.getProperty("drumsplit2"), nullptr); anyData = true; }
    if(source.hasProperty("drumsplit3")) {item.setProperty("drumsplit3", source.getProperty("drumsplit3"), nullptr); anyData = true; }
    if(!anyData){
        list.removeChild(item, nullptr);
        if(list.getNumChildren() == 0){
            rdnamesnode.removeChild(list, nullptr);
        }
    }
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

/*
void showProperties(ValueTree vt){
    int i;
    String s = "";
    for(i=0; i<vt.getNumProperties(); ++i){
        Identifier id = vt.getPropertyName(i);
        s = s + ", " + id.toString() + "=" + vt.getProperty(id).toString();
    }
    s = s.substring(2);
    SEQ64::say(s);
}
*/

/**
 * For a given list within d, check if an item exists with the
 * given address. If it doesn't exist, create it. In either case, write back the
 * index within that list of the found/created item to the given node.
 */
void BankFile::checkAddListItem(ValueTree list, int addressval, ValueTree node){
    if(addressval == 0){
        SEQ64::say("Error: trying to add nullptr list item!");
        return;
    }
    ValueTree sub = list.getChildWithProperty("address", addressval);
    int listindex;
    if(sub.isValid()){
        listindex = list.indexOf(sub);
    }else{
        sub = ValueTree("item");
        sub.setProperty("address", addressval, nullptr);
        listindex = list.getNumChildren();
        list.addChild(sub, listindex, nullptr);
        copyRDItemPropsToItem(list.getType().toString(), listindex, sub);
    }
    String subname = sub.getProperty("name", "[unnamed]");
    if(subname.startsWith("[")){
        //Unnamed item, use parent name
        ValueTree par = node.getParent();
        int childidx = par.indexOf(node);
        if(par.getParent().isValid() && par.getParent().getProperty("datatype", "none") == "ABSound"){
            childidx = par.getParent().getParent().indexOf(par.getParent());
            par = par.getParent().getParent();
        }
        if(par.getProperty("isarray", false)){
            par = par.getParent();
        }else{
            childidx = -1;
        }
        if(par.getType().toString() == "struct" && par.getParent().isValid() && par.getParent().getNumChildren() == 1){
            par = par.getParent();
        }
        String parname = getNodeDesc(par);
        if(childidx >= 0){
            parname = parname + ":" + String(childidx);
        }
        if(subname == "[unnamed]"){
            sub.setProperty("name", "[" + parname + "]", nullptr);
        }else{
            if(subname.length() < 100){
                sub.setProperty("name", subname.dropLastCharacters(1) + ", " + parname + "]", nullptr);
            }
        }
    }
    node.setProperty("index", listindex, nullptr);
}

/**
 * For any of the elements of d which are lists: for the existing contents of
 * the list (with addresses already saved to them), go through each element 
 * and load its struct as a new child of that element.
 */
bool BankFile::loadElementList(ROM& rom, uint32 baseaddr, uint32 bank_length, String listname, String elementname){
    SEQ64::say("Loading element list " + listname + "...");
    bool ret = true;
    uint32 a;
    ValueTree stru = d.getChildWithName(listname);
    ValueTree temp, item;
    int count = stru.getNumChildren();
    for(int i=0; i<count; i++){
        temp = stru.getChild(i);
        a = (int)temp.getProperty("address", 0);
        if(a == 0) continue;
        if(a >= bank_length){
            SEQ64::say("In " + listname + " list, item " + String(i) + ": ptr outside bank @" + ROM::hex(a) + "!");
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Load Bank",
                    "Pointer to outside bank (check terminal output for details).\n"
                    "Unless you've been editing the definition of the Audiobank format"
                    "(in which case you probably messed something up), this means"
                    "that what you tried to load was probably not actually bank data,"
                    "which usually means Audiobank or Audiobank Index got corrupted"
                    "by something (cough cough InstEd cough). The loaded bank will"
                    "almost certainly be broken.");
            ret = false;
        }
        item = getCopyOfTemplate(elementname);
        temp.addChild(item, -1, nullptr);
        if(readStruct(rom, a + baseaddr, item) < 0){
            SEQ64::say("Reading " + elementname + " index " + String(i) + " from " + listname + " failed");
            return false;
        }
    }
    return ret;
}

ValueTree BankFile::getListForPointer(String pointertype){
    if(pointertype == "ABDrumList"){
        return d.getChildWithName("abdrumlist");
    }else if(pointertype == "ABSFXList"){
        return d.getChildWithName("absfxlist");
    }else if(pointertype == "ABInstrument"){
        return d.getChildWithName("instruments");
    }else if(pointertype == "ABDrum"){
        return d.getChildWithName("drums");
    }else if(pointertype == "ABEnvelope"){
        return d.getChildWithName("envelopes");
    }else if(pointertype == "ABSample"){
        return d.getChildWithName("samples");
    }else if(pointertype == "ALADPCMBook"){
        return d.getChildWithName("aladpcmbooks");
    }else if(pointertype == "ALADPCMLoop"){
        return d.getChildWithName("aladpcmloops");
    }else{
        return ValueTree();
    }
}

BankFile::ABIEProps BankFile::getABIEProps(ROM& rom, int banknum){
    ABIEProps abiep;
    if(banknum < 0) return abiep;
    //Get file and index properties from RomDesc
    ValueTree abiinfonode = romdesc.getChildWithName("knownfilelist")
            .getChildWithProperty("type", "Audiobank Index");
    if(!abiinfonode.isValid()){
        SEQ64::say("Audiobank Index not defined in RomDesc!");
        return abiep;
    }
    abiep.abiaddr = (int)abiinfonode.getProperty("address");
    if(abiep.abiaddr >= rom.getSize()){
        SEQ64::say("Audiobank Index at invalid index " + ROM::hex(abiep.abiaddr) + "!");
        return abiep;
    }
    ValueTree abfinfonode = romdesc.getChildWithName("knownfilelist")
            .getChildWithProperty("type", "Audiobank");
    if(!abfinfonode.isValid()){
        SEQ64::say("Audiobank not defined in RomDesc!");
        return abiep;
    }
    abiep.abfaddr = (int)abfinfonode.getProperty("address");
    if(abiep.abfaddr >= rom.getSize()){
        SEQ64::say("Audiobank at invalid index " + ROM::hex(abiep.abfaddr) + "!");
        return abiep;
    }
    SEQ64::say("Loading bank file from index @" + ROM::hex(abiep.abiaddr) 
            + ", bank " + ROM::hex((uint8)banknum) + ", file @" + ROM::hex(abiep.abfaddr));
    //Load abindexentry
    if((int)romdesc.getProperty("indextype", 1) == 2){
        abiep.bank_count = rom.readHalfWord(abiep.abiaddr);
        abiep.abientryaddr = abiep.abiaddr + (16*banknum) + 16;
    }else{
        abiep.bank_count = rom.readHalfWord(abiep.abiaddr+2);
        abiep.abientryaddr = abiep.abiaddr + (8*banknum) + 4;
    }
    if(banknum >= abiep.bank_count) return abiep;
    abiep.abiestru = getCopyOfTemplate("ABIndexEntry");
    readStruct(rom, abiep.abientryaddr, abiep.abiestru);
    //Copy relevant data from index entry into C++ class
    ValueTree temp = abiep.abiestru.getChildWithProperty("meaning", "Ptr Bank (in Audiobank)");
    if(!temp.isValid()){
        SEQ64::say("ABIndexEntry must include a field with meaning Ptr Bank (in Audiobank)!");
        return abiep;
    }
    abiep.ptr_bank = (int)temp.getProperty("value", 0x8000000);
    if(abiep.ptr_bank + abiep.abfaddr >= rom.getSize()){
        SEQ64::say("Ptr Bank " + ROM::hex(abiep.ptr_bank) + " + base " 
                + ROM::hex(abiep.abfaddr) + " goes off end of ROM!");
        return abiep;
    }
    //
    temp = abiep.abiestru.getChildWithProperty("meaning", "Bank Length");
    if(!temp.isValid()){
        SEQ64::say("ABIndexEntry must include a field with meaning Bank Length!");
        return abiep;
    }
    abiep.bank_length = (int)temp.getProperty("value", 0x8000000);
    if(abiep.bank_length >= 0x20000){
        SEQ64::say("Bank Length " + ROM::hex(abiep.bank_length) + ", probably wrong!");
        return abiep;
    }
    abiep.valid = true;
    return abiep;
}


/**
 * Load a complete Audiobank file, given the bank number.
 */
bool BankFile::load(ROM& rom, int banknum){
    //Init
    uint32 a, baseaddr;
    int strsize;
    ValueTree temp, stru, item;
    reset();
    loadRDNamesNode(banknum);
    //========================================================================
    //Load index entry
    //========================================================================
    SEQ64::say("Reading index entry...");
    ABIEProps bankprops = getABIEProps(rom, banknum);
    if(!bankprops.valid) return false;
    d.getChildWithName("abindexentry").addChild(bankprops.abiestru, -1, nullptr);
    //
    temp = bankprops.abiestru.getChildWithProperty("meaning", "Sample Table number");
    if(temp.isValid()){
        d.setProperty("ATnum", temp.getProperty("value", 0), nullptr);
    }
    //
    temp = bankprops.abiestru.getChildWithProperty("meaning", "NUM_INST");
    if(temp.isValid()){
        d.setProperty("NUM_INST", temp.getProperty("value", 0), nullptr);
    }
    //
    temp = bankprops.abiestru.getChildWithProperty("meaning", "NUM_DRUM");
    if(temp.isValid()){
        d.setProperty("NUM_DRUM", temp.getProperty("value", 0), nullptr);
    }
    //
    temp = bankprops.abiestru.getChildWithProperty("meaning", "NUM_SFX");
    if(temp.isValid()){
        d.setProperty("NUM_SFX", temp.getProperty("value", 0), nullptr);
    }
    //========================================================================
    //Load bank header
    //========================================================================
    SEQ64::say("Reading bank header...");
    stru = getCopyOfTemplate("ABHeader");
    d.getChildWithName("abheader").addChild(stru, -1, nullptr);
    a = bankprops.abfaddr + bankprops.ptr_bank;
    strsize = readStruct(rom, a, stru);
    a += strsize;
    baseaddr = a;
    //Read relevant data from header
    temp = stru.getChildWithProperty("meaning", "Sample Table number");
    if(temp.isValid()){
        d.setProperty("ATnum", temp.getProperty("value", 0), nullptr);
    }
    if((int)d.getProperty("ATnum") < 0){
        SEQ64::say("Sample Table number not defined in either ABIndexEntry or ABHeader!");
        return false;
    }
    temp = stru.getChildWithProperty("meaning", "NUM_INST");
    if(temp.isValid()){
        d.setProperty("NUM_INST", temp.getProperty("value", 0), nullptr);
    }
    if((int)d.getProperty("NUM_INST") < 0){
        SEQ64::say("NUM_INST not defined in either ABIndexEntry or ABHeader!");
        return false;
    }
    temp = stru.getChildWithProperty("meaning", "NUM_DRUM");
    if(temp.isValid()){
        d.setProperty("NUM_DRUM", temp.getProperty("value", 0), nullptr);
    }
    if((int)d.getProperty("NUM_DRUM") < 0){
        SEQ64::say("NUM_DRUM not defined in either ABIndexEntry or ABHeader!");
        return false;
    }
    temp = stru.getChildWithProperty("meaning", "NUM_SFX");
    if(temp.isValid()){
        d.setProperty("NUM_SFX", temp.getProperty("value", 0), nullptr);
    }
    if((int)d.getProperty("NUM_SFX") < 0 && (int)romdesc.getProperty("indextype", 1) == 2){
        SEQ64::say("NUM_SFX not defined in either ABIndexEntry or ABHeader!");
        return false;
    }
    //========================================================================
    //Load bank (main)
    //========================================================================
    SEQ64::say("Reading bank main...");
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
    int ret = 1;
    ret &= (int)loadElementList(rom, baseaddr, bankprops.bank_length, "instruments", "ABInstrument");
    ret &= (int)loadElementList(rom, baseaddr, bankprops.bank_length, "drums", "ABDrum");
    ret &= (int)loadElementList(rom, baseaddr, bankprops.bank_length, "sfx", "ABSound");
    ret &= (int)loadElementList(rom, baseaddr, bankprops.bank_length, "envelopes", "ABEnvelope");
    ret &= (int)loadElementList(rom, baseaddr, bankprops.bank_length, "samples", "ABSample");
    ret &= (int)loadElementList(rom, baseaddr, bankprops.bank_length, "aladpcmbooks", "ALADPCMBook");
    ret &= (int)loadElementList(rom, baseaddr, bankprops.bank_length, "aladpcmloops", "ALADPCMLoop");
    if(ret) SEQ64::say("Done loading bank!");
    else SEQ64::say("Done loading bank...");
    return ret == 1;
}

int BankFile::save(ROM& rom, int banknum){
    //========================================================================
    //Put in all info determined at import
    //========================================================================
    SEQ64::say("Setting import-time variables...");
    ValueTree stru, temp;
    int NUM_INST = d.getChildWithName("abbank").getChild(0)
            .getChildWithProperty("meaning", "List of Ptrs to Insts").getNumChildren();
    int NUM_DRUM = d.getChildWithName("abdrumlist").getChild(0)
            .getChildWithProperty("meaning", "List of Ptrs to Drums").getNumChildren();
    int NUM_SFX  = d.getChildWithName("absfxlist").getChild(0)
            .getChildWithProperty("meaning", "List of Sounds").getNumChildren();
    d.setProperty("NUM_INST", NUM_INST, nullptr);
    d.setProperty("NUM_DRUM", NUM_DRUM, nullptr);
    d.setProperty("NUM_SFX",  NUM_SFX,  nullptr);
    //
    stru = d.getChildWithName("abindexentry").getChild(0);
    temp = stru.getChildWithProperty("meaning", "NUM_INST");
    if(temp.isValid()){
        temp.setProperty("value", NUM_INST, nullptr);
    }
    temp = stru.getChildWithProperty("meaning", "NUM_DRUM");
    if(temp.isValid()){
        temp.setProperty("value", NUM_DRUM, nullptr);
    }
    temp = stru.getChildWithProperty("meaning", "NUM_SFX");
    if(temp.isValid()){
        temp.setProperty("value", NUM_SFX, nullptr);
    }
    //
    stru = d.getChildWithName("abheader").getChild(0);
    temp = stru.getChildWithProperty("meaning", "NUM_INST");
    if(temp.isValid()){
        temp.setProperty("value", NUM_INST, nullptr);
    }
    temp = stru.getChildWithProperty("meaning", "NUM_DRUM");
    if(temp.isValid()){
        temp.setProperty("value", NUM_DRUM, nullptr);
    }
    temp = stru.getChildWithProperty("meaning", "NUM_SFX");
    if(temp.isValid()){
        temp.setProperty("value", NUM_SFX, nullptr);
    }
    fixAllStructImportValues(d.getChildWithName("aladpcmbooks"));
    fixAllStructImportValues(d.getChildWithName("aladpcmloops"));
    //========================================================================
    //Determine all struct lengths and addresses; write to other structs
    //========================================================================
    SEQ64::say("Determining all struct lengths and addresses...");
    int align = abfstructsnode.getProperty("align", 4);
    uint32 a = 0;
    stru = d.getChildWithName("abheader").getChild(0);
    uint32 headerlen = getStructLength(stru); //Don't add to a
    stru = d.getChildWithName("abbank").getChild(0);
    stru.setProperty("address", (int)a, nullptr);
    a += getStructLength(stru);
    ALIGN(a, align);
    stru = d.getChildWithName("abdrumlist").getChild(0);
    if(stru.isValid()){
        stru.setProperty("address", (int)a, nullptr);
        setAllReferencesAddress(d, "ABDrumList", -1, a);
        a += getStructLength(stru);
        ALIGN(a, align);
    }
    stru = d.getChildWithName("absfxlist").getChild(0);
    if(stru.isValid()){
        stru.setProperty("address", (int)a, nullptr);
        setAllReferencesAddress(d, "ABSFXList", -1, a);
        a += getStructLength(stru);
        ALIGN(a, align);
    }
    getAllStructLengths("ABInstrument", &a, align);
    getAllStructLengths("ABDrum", &a, align);
    getAllStructLengths("ABEnvelope", &a, align);
    getAllStructLengths("ABSample", &a, align);
    getAllStructLengths("ALADPCMBook", &a, align);
    getAllStructLengths("ALADPCMLoop", &a, align);
    uint32 totallen = headerlen + a;
    SEQ64::say("Checking all indexed ptrs for correct contents/nullptrs...");
    if(!validatePointerIndexes(d)) return -2;
    //========================================================================
    //Render to Audiobank format
    //========================================================================
    SEQ64::say("Rendering to Audiobank format...");
    a = 0;
    ROM bank(totallen, true);
    a += writeStruct(bank, a, d.getChildWithName("abheader").getChild(0));
    ALIGN(a, align);
    a += writeStruct(bank, a, d.getChildWithName("abbank").getChild(0));
    ALIGN(a, align);
    stru = d.getChildWithName("abdrumlist").getChild(0);
    if(stru.isValid()){
        a += writeStruct(bank, a, stru);
        ALIGN(a, align);
    }
    stru = d.getChildWithName("absfxlist").getChild(0);
    if(stru.isValid()){
        a += writeStruct(bank, a, stru);
        ALIGN(a, align);
    }
    writeAllItems(bank, d.getChildWithName("instruments"), &a, align);
    writeAllItems(bank, d.getChildWithName("drums"), &a, align);
    writeAllItems(bank, d.getChildWithName("envelopes"), &a, align);
    writeAllItems(bank, d.getChildWithName("samples"), &a, align);
    writeAllItems(bank, d.getChildWithName("aladpcmbooks"), &a, align);
    writeAllItems(bank, d.getChildWithName("aladpcmloops"), &a, align);
    if(a != totallen){
        SEQ64::say("Length mismatch, on scan pass was 0x" + ROM::hex((uint32)totallen)
                + " but on write pass it was 0x" + ROM::hex((uint32)a) + "!");
        return -1;
    }
    //========================================================================
    //Copy into ROM
    //========================================================================
    SEQ64::say("Copying to ROM...");
    //Get file and index properties from RomDesc
    ABIEProps origbank_props = getABIEProps(rom, banknum);
    if(!origbank_props.valid){
        SEQ64::say("Could not get bank file/index properties from RomDesc!");
        return -1;
    }
    //Figure out how much space we have to import
    uint32 newbank_maxsize = origbank_props.bank_length;
    uint32 newbank_startaddr = origbank_props.abfaddr + origbank_props.ptr_bank;
    if(banknum == origbank_props.bank_count - 1){
        //Last bank, go to end of bank and see how long there's zeros afterwards
        uint32 startaddr = origbank_props.abfaddr + origbank_props.ptr_bank + origbank_props.bank_length;
        uint32 endaddr = rom.getAddressOfNextData(startaddr);
        if(endaddr < startaddr){
            SEQ64::say("Last bank, error in looking for blank space after!");
        }else{
            newbank_maxsize = endaddr - newbank_startaddr;
        }
    }else{
        ABIEProps afterbank_props = getABIEProps(rom, banknum+1);
        newbank_maxsize = afterbank_props.ptr_bank - origbank_props.ptr_bank;
    }
    //Check importing
    if(totallen > newbank_maxsize){
        SEQ64::say("Cannot import bank length 0x" + ROM::hex((uint32)totallen) 
                + " into space 0x" + ROM::hex((uint32)newbank_maxsize) + "!");
        return totallen;
    }
    SEQ64::say("0x" + ROM::hex((uint32)newbank_maxsize) + " bytes available for importing");
    //Copy data
    rom.copyFrom(bank.getData(), newbank_startaddr, totallen);
    //Erase remaining data afterwards
    for(uint32 k=newbank_startaddr+totallen; k<newbank_startaddr+newbank_maxsize; k++){
        rom.writeByte(k, 0);
    }
    //Update fields in abindexentry
    stru = d.getChildWithName("abindexentry").getChild(0);
    temp = stru.getChildWithProperty("meaning", "Ptr Bank (in Audiobank)");
    if(!temp.isValid()){
        SEQ64::say("ABIndexEntry must include a field with meaning Ptr Bank (in Audiobank)!");
        return -1;
    }
    temp.setProperty("value", (int)origbank_props.ptr_bank, nullptr);
    temp = stru.getChildWithProperty("meaning", "Bank Length");
    if(!temp.isValid()){
        SEQ64::say("ABIndexEntry must include a field with meaning Bank Length!");
        return -1;
    }
    temp.setProperty("value", (int)totallen, nullptr);
    //Copy abindexentry
    writeStruct(rom, origbank_props.abientryaddr, d.getChildWithName("abindexentry").getChild(0));
    //Done
    SEQ64::say("Imported bank, 0x" + ROM::hex((uint32)totallen) + " bytes @" 
            + ROM::hex((uint32)newbank_startaddr) + "!");
    //========================================================================
    //Update RomDesc
    //========================================================================
    SEQ64::say("Updating RomDesc...");
    loadRDNamesNode(banknum);
    clearRDNamesNode();
    copyAllItemProps("instruments");
    copyAllItemProps("drums");
    copyAllItemProps("envelopes");
    copyAllItemProps("samples");
    copyAllItemProps("aladpcmbooks");
    copyAllItemProps("aladpcmloops");
    SEQ64::say("Done!!!");
    return 0;
}
void BankFile::getAllStructLengths(String pointertype, uint32* a, int align){
    ValueTree stru = getListForPointer(pointertype);
    ValueTree temp;
    for(int i=0; i<stru.getNumChildren(); i++){
        temp = stru.getChild(i);
        temp.setProperty("address", (int)(*a), nullptr);
        setAllReferencesAddress(d, pointertype, i, *a);
        *a += getStructLength(temp.getChild(0));
        ALIGN(*a, align);
    }
}
void BankFile::setAllReferencesAddress(ValueTree parent, String pointername, int index, uint32 address){
    if(!parent.isValid()) return;
    if((bool)parent.getProperty("ispointer", false) && !(bool)parent.getProperty("isarray", false)){
        if(parent.getProperty("ptrto", "Error").toString() == pointername 
                && (int)parent.getProperty("index", -1) == index){
            parent.setProperty("value", (int)address, nullptr);
        }
    }
    for(int i=0; i<parent.getNumChildren(); i++){
        setAllReferencesAddress(parent.getChild(i), pointername, index, address);
    }
}
bool BankFile::validatePointerIndexes(ValueTree node){
    //Validate that all pointers with an index are pointing to their reference's
    //address, or set their value to 0 if their index is invalid
    if(!node.isValid()) return false;
    int ret = 1;
    if((bool)node.getProperty("ispointer", false) && node.hasProperty("index")){
        String ptrto = node.getProperty("ptrto", "Error").toString();
        ValueTree list = getListForPointer(ptrto);
        if(!list.isValid()){
            SEQ64::say("Could not get list for pointer to " + ptrto + "!");
            ret = 0;
        }else{
            int ptridx = node.getProperty("index", 10000000);
            if(ptridx >= list.getNumChildren()){
                SEQ64::say("Pointer index to " + String(ptridx) + " out of bounds for " 
                    + String(list.getNumChildren()) + " " + ptrto + "s!");
                ret = 0;
            }else if(ptridx < 0){
                //Set address to -1
                SEQ64::say("Setting address to 0 for pointer to no " + ptrto + " (normal)");
                node.setProperty("value", 0, nullptr);
            }else{
                ValueTree target = list.getChild(ptridx);
                int naddr = node.getProperty("value", 1000000);
                int taddr = target.getProperty("address", 0);
                if(taddr != naddr){
                    SEQ64::say("Incorrect pointer to " + ptrto + " @" + ROM::hex((uint32)naddr)
                            + ", should be @" + ROM::hex((uint32)taddr) + "!");
                    ret = 0;
                }
            }
        }
    }
    for(int i=0; i<node.getNumChildren(); ++i){
        ret &= (int)validatePointerIndexes(node.getChild(i));
    }
    return ret > 0;
}
void BankFile::fixAllStructImportValues(ValueTree parent){
    if(!parent.isValid()) return;
    if(parent.getType().toString() == "struct"){
        if(parent.getProperty("name", "Error").toString() == "ALADPCMBook"){
            ValueTree np = parent.getChildWithProperty("meaning", "NUM_PRED");
            ValueTree pa = parent.getChildWithProperty("arraylenvar", "NUM_PRED");
            if(np.isValid() && pa.isValid()){
                int NUM_PRED = pa.getNumChildren();
                parent.setProperty("NUM_PRED", NUM_PRED, nullptr);
                np.setProperty("value", NUM_PRED, nullptr);
            }
            return;
        }else if(parent.getProperty("name", "Error").toString() == "ALADPCMLoop"){
            ValueTree st = parent.getChildWithProperty("meaning", "Loop Start");
            ValueTree ar = parent.getChildWithProperty("arraylenvar", "HAS_TAIL");
            if(st.isValid() && ar.isValid()){
                bool HAS_TAIL = (ar.getNumChildren() > 0);
                parent.setProperty("HAS_TAIL", HAS_TAIL, nullptr);
                if((int)st.getProperty("value", 0) > 0){
                    if(!HAS_TAIL) st.setProperty("value", 0, nullptr);
                }else{
                    //We have to generate a loop start value not zero
                    //Chose 16 because the tail has 16 points...?
                    if(HAS_TAIL) st.setProperty("value", 16, nullptr);
                }
            }
            return;
        }
    }
    for(int i=0; i<parent.getNumChildren(); i++){
        fixAllStructImportValues(parent.getChild(i));
    }
}
void BankFile::writeAllItems(ROM& bank, ValueTree parent, uint32* a, int align){
    for(int i=0; i<parent.getNumChildren(); i++){
        *a += writeStruct(bank, *a, parent.getChild(i).getChild(0));
        ALIGN(*a, align);
    }
}
void BankFile::copyAllItemProps(String listname){
    ValueTree dlist = d.getChildWithName(listname);
    if(!dlist.isValid()){
        SEQ64::say("copyAllItemProps error, list " + listname + "!");
        return;
    }
    for(int i=0; i<dlist.getNumChildren(); i++){
        copyItemPropsToRDItem(listname, i, dlist.getChild(i));
    }
}

bool BankFile::loadXML(File xmlfile){
    reset();
    std::unique_ptr<XmlElement> xml(XmlDocument::parse(xmlfile));
    if(xml == nullptr){
        SEQ64::say("Could not parse file as XML!");
        return false;
    }
    d = ValueTree::fromXml(*xml);
    if(!d.isValid()){
        SEQ64::say("Invalid XML/ValueTree contents!");
        return false;
    }
    return true;
}
bool BankFile::saveXML(File xmlfile){
    return xmlfile.replaceWithText(d.toXmlString());
}

int BankFile::readStruct(ROM& rom, uint32 addr, ValueTree stru){
    if(!stru.isValid()) return 0;
    if(stru.getType().toString() != "struct"){
        SEQ64::say("readStruct() on non-struct type " + stru.getType().toString() + "!");
        return 0;
    }
    int len = 0, fieldlen, fieldelementlen;
    int count = stru.getNumChildren();
    String struname = stru.getProperty("name", "Error");
    ValueTree field, sub, dstru, fieldelement;
    String datatype, ptrto, arraylenvar, meaning;
    bool ispointer, isarray, arrayloopflag;
    int arraylenfixed;
    uint32 a = addr;
    uint32 val;
    int arraycount, arraymax = 0;
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
                    return 0;
                }
                if(arraymax < 0){
                    SEQ64::say("Array length using not-yet-set variable " + arraylenvar + "!");
                    return 0;
                }
            }
            if(arraymax > 1000){
                SEQ64::say("Asked to read array " + String(arraymax) + " entries long in struct " + struname 
                    + " type " + datatype + ", which is probably wrong, reading 0 entries instead!");
                arraymax = 0;
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
                fieldelement.setProperty("ispointer", ispointer, nullptr);
                if(ispointer) fieldelement.setProperty("ptrto", ptrto, nullptr);
                field.addChild(fieldelement, -1, nullptr);
            }else{
                arrayloopflag = false;
                fieldelement = field;
            }
            //Read actual data
            bool dontwritevalue = false;
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
            }else if(datatype == "float32"){
                val = rom.readWord(a);
                fieldelementlen = 4;
                jassert(sizeof(float) == 4);
                float f = *(float*)&val;
                fieldelement.setProperty("value", f, nullptr);
                val = 0;
                dontwritevalue = true;
            }else if(datatype == "ABSound" || datatype == "ALADPCMPredictor" || datatype == "ALADPCMTail"){
                sub = getCopyOfTemplate(datatype);
                fieldelement.addChild(sub, -1, nullptr);
                fieldelementlen = readStruct(rom, a, sub);
                val = 0;
            }else{
                SEQ64::say("Invalid data type " + datatype + "!");
                return 0;
            }
            //Length, address, data
            fieldlen += fieldelementlen;
            a += fieldelementlen;
            if(!dontwritevalue) fieldelement.setProperty("value", (int)val, nullptr);
            //Meaning
            if(ispointer && val != 0){
                dstru = getListForPointer(ptrto);
                if(dstru.isValid()){
                    if(ptrto == "ABDrumList" || ptrto == "ABSFXList"){
                        if(dstru.hasProperty("address")){
                            SEQ64::say("Multiple pointers to " + ptrto + ", changing address from " 
                                    + dstru.getProperty("address", "Error").toString() + " to "
                                    + String(val) + "!");
                        }
                        dstru.setProperty("address", (int)val, nullptr);
                    }else{
                        checkAddListItem(dstru, val, fieldelement);
                    }
                }
            }
            /*if(meaning == "NUM_INST" || meaning == "NUM_DRUM" || meaning == "NUM_SFX"){
                if(isarray){
                    SEQ64::say("Array cannot have meaning " + meaning + "!");
                }else{
                    if((int)d.getProperty(meaning) >= 0){
                        SEQ64::say("Overwriting global property " + meaning + " with value " + String(val));
                    }
                    d.setProperty(meaning, val, nullptr);
                }
            }else */ if(meaning == "NUM_PRED" || meaning == "HAS_TAIL" || meaning == "Loop Start"){
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
                        stru.setProperty(meaning, (int)val, nullptr);
                    }
                }
            }
        }
        len += fieldlen;
    }
    return len;
}

int BankFile::getStructLength(ValueTree stru){
    if(!stru.isValid()) return 0;
    if(stru.getType().toString() != "struct"){
        SEQ64::say("getStructLength() on non-struct type " + stru.getType().toString() + "!");
        return 0;
    }
    int len = 0, fieldlen, fieldelementlen;
    int count = stru.getNumChildren();
    String struname = stru.getProperty("name", "Error");
    ValueTree field, sub, dstru, fieldelement;
    String datatype, arraylenvar;
    bool isarray, arrayloopflag;
    int arraycount, arraymax = 0;
    for(int i=0; i<count; i++){
        field = stru.getChild(i);
        //Load field properties from stru
        datatype = field.getProperty("datatype", "uint32").toString();
        isarray = field.getProperty("isarray", false);
        if(isarray){
            if(field.hasProperty("arraylenfixed")){
                arraymax = field.getProperty("arraylenfixed", 0);
            }else{
                arraylenvar = field.getProperty("arraylenvar", 0).toString();
                arraymax = -1;
                if(d.hasProperty(arraylenvar)){
                    arraymax = (int)d.getProperty(arraylenvar);
                }else if(stru.hasProperty(arraylenvar)){
                    arraymax = (int)stru.getProperty(arraylenvar);
                }else{
                    SEQ64::say("Invalid array length variable " + arraylenvar + "!");
                    return 0;
                }
                if(arraymax < 0){
                    SEQ64::say("Array length using not-yet-set variable " + arraylenvar + "!");
                    return 0;
                }
            }
        }
        //Read data from ROM
        arrayloopflag = true;
        fieldlen = 0;
        arraycount = -1;
        while(arrayloopflag){
            //Pre-deal with arrays
            if(isarray){
                arraycount++;
                if(arraycount >= arraymax) break;
                fieldelement = field.getChild(arraycount);
            }else{
                arrayloopflag = false;
                fieldelement = field;
            }
            //Read actual data
            if(datatype == "uint32" || datatype == "int32" || datatype == "float32"){
                fieldelementlen = 4;
            }else if(datatype == "uint16" || datatype == "int16"){
                fieldelementlen = 2;
            }else if(datatype == "uint8" || datatype == "int8"){
                fieldelementlen = 1;
            }else if(datatype == "ABSound" || datatype == "ALADPCMPredictor" || datatype == "ALADPCMTail"){
                fieldelementlen = getStructLength(fieldelement.getChild(0));
            }else{
                SEQ64::say("Invalid data type " + datatype + "!");
                return 0;
            }
            //Length
            fieldlen += fieldelementlen;
        }
        len += fieldlen;
    }
    return len;
}

int BankFile::writeStruct(ROM& rom, uint32 addr, ValueTree stru){
    if(!stru.isValid()) return 0;
    if(stru.getType().toString() != "struct"){
        SEQ64::say("writeStruct() on non-struct type " + stru.getType().toString() + "!");
        return 0;
    }
    int len = 0, fieldlen, fieldelementlen;
    int count = stru.getNumChildren();
    String struname = stru.getProperty("name", "Error");
    ValueTree field, sub, dstru, fieldelement;
    String datatype, arraylenvar;
    bool isarray, arrayloopflag;
    int arraylenfixed;
    uint32 a = addr;
    uint32 val;
    int arraycount, arraymax = 0;
    for(int i=0; i<count; i++){
        field = stru.getChild(i);
        //Load field properties from stru
        datatype = field.getProperty("datatype", "uint32").toString();
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
                    return 0;
                }
                if(arraymax < 0){
                    SEQ64::say("Array length using not-yet-set variable " + arraylenvar + "!");
                    return 0;
                }
            }
        }
        //Write data to ROM
        arrayloopflag = true;
        fieldlen = 0;
        arraycount = -1;
        while(arrayloopflag){
            //Pre-deal with arrays
            if(isarray){
                arraycount++;
                if(arraycount >= arraymax) break;
                fieldelement = field.getChild(arraycount);
            }else{
                arrayloopflag = false;
                fieldelement = field;
            }
            //Data
            val = (int)fieldelement.getProperty("value", 0);
            //Write actual data
            if(datatype == "uint32" || datatype == "int32"){
                rom.writeWord(a, val);
                fieldelementlen = 4;
            }else if(datatype == "uint16"){
                rom.writeHalfWord(a, (uint16)val);
                fieldelementlen = 2;
            }else if(datatype == "int16"){
                rom.writeHalfWord(a, (int16)val);
                fieldelementlen = 2;
            }else if(datatype == "uint8"){
                rom.writeByte(a, (uint8)val);
                fieldelementlen = 1;
            }else if(datatype == "int8"){
                rom.writeByte(a, (int8)val);
                fieldelementlen = 1;
            }else if(datatype == "float32"){
                float f = fieldelement.getProperty("value", 0.0f);
                val = *(uint32*)&f;
                rom.writeWord(a, val);
                fieldelementlen = 4;
            }else if(datatype == "ABSound" || datatype == "ALADPCMPredictor" || datatype == "ALADPCMTail"){
                fieldelementlen = writeStruct(rom, a, fieldelement.getChild(0));
            }else{
                SEQ64::say("Invalid data type " + datatype + "!");
                return 0;
            }
            //Length, address
            fieldlen += fieldelementlen;
            a += fieldelementlen;
        }
        len += fieldlen;
    }
    return len;
}

String BankFile::getFieldDesc(ValueTree field, bool cformatting){
    if(!field.isValid()) return "Error!";
    String desc = String();
    if(cformatting) desc = "  ";
    String datatype = field.getProperty("datatype", "ErrorType");
    if((bool)field.getProperty("ispointer", false)){
        String ptrto = field.getProperty("ptrto", "ErrorType");
        if(datatype == "uint32" || datatype == "int32"){
            desc += ptrto + "*";
        }else{
            desc += "(" + datatype + ")(" + ptrto + "*)";
        }
    }else{
        desc += datatype;
    }
    desc += " ";
    desc += field.getProperty("name", "").toString();
    if((bool)field.getProperty("isarray", false)){
        if(field.hasProperty("arraylenfixed")){
            desc += "[0x" + ROM::hex((uint8)(int)field.getProperty("arraylenfixed", 0)) + "]";
        }else{
            desc += "[" + field.getProperty("arraylenvar", "Error").toString() + "]";
        }
    }
    if(field.hasProperty("defaultval")){
        desc += " = 0x" + String::toHexString((int)field.getProperty("defaultval"));
    }
    if(cformatting) desc += ";";
    String meaning = field.getProperty("meaning", "None").toString();
    if(meaning != "None"){
        if(cformatting){
            desc += " //" + meaning;
        }else{
            desc += "(" + meaning + ")";
        }
    }
    return desc;
}
String BankFile::getNodeDesc(ValueTree node){
    if(!node.isValid()) return "Error!";
    String type = node.getType().toString();
    ValueTree parent = node.getParent();
    if(parent.isValid()){
        if(type == "struct" && parent.getNumChildren() == 1){
            return getNodeDesc(parent);
        }else if(type == "item"){
            String parenttype = parent.getType().toString();
            if(parenttype == "instruments" || parenttype == "drums" || parenttype == "sfx" || parenttype == "envelopes"
                    || parenttype == "samples" || parenttype == "aladpcmbooks" || parenttype == "aladpcmloops"){
                return String(parent.indexOf(node)) + ". " + node.getProperty("name", "Error!").toString();
            }
        }
    }
    if((bool)node.getProperty("ispointer", false)){
        NodeValueInfo ni = getNodeValueInfo(node, false);
        if(ni.valueeditable){
            String ret;
            if(ni.valueequiv == "nullptr"){
                ret = " = nullptr;";
            }else{
                ret = " = &" + node.getProperty("ptrto", "Error!").toString() + "[" + ni.value + "]; //" + ni.valueequiv;
            }
            if(type == "element"){
                return parent.getProperty("name", "Error!").toString() + "[" + String(parent.indexOf(node)) + "]" + ret;
            }
            if(type == "field"){
                return node.getProperty("name", "Error!").toString() + ret;
            }
        }
    }
    if(node.hasProperty("name")){
        return node.getProperty("name", "Error!").toString();
    }
    if(type == "field" || type == "element"){
        return getFieldDesc(node, false);
    }else{
        return type;
    }
}
String BankFile::getNodeName(ValueTree node){
    if(!node.isValid()) return "Error!";
    return node.getProperty("name", "").toString();
}
bool BankFile::isNodeNameEditable(ValueTree node){
    if(!node.isValid()) return false;
    return (node.getType().toString() == "item");
}
bool BankFile::setNodeName(ValueTree node, String name){
    if(!isNodeNameEditable(node)) return false;
    if(!node.hasProperty("name")) return false;
    node.setProperty("name", name, nullptr);
    return true;
}
String BankFile::getNodeType(ValueTree node){
    if(!node.isValid()) return "Error!";
    String vttype = node.getType().toString();
    String typestr = "";
    if(vttype == "field"){
        typestr = node.getProperty("datatype", "Error").toString();
        if((bool)node.getProperty("ispointer", false)){
            typestr = "Ptr (" + typestr + ") to " + node.getProperty("ptrto", "Error").toString();
        }
        if((bool)node.getProperty("isarray", false)){
            typestr = "Array of " + typestr;
            if(node.hasProperty("arraylenfixed")){
                typestr += " (" + node.getProperty("arraylenfixed").toString() + ")";
            }else if(node.hasProperty("arraylenvar")){
                typestr += " (" + node.getProperty("arraylenvar").toString() + ")";
            }else{
                SEQ64::say("Array with no fixed or variable size!");
            }
        }
    }else{
        typestr = vttype;
    }
    return typestr;
}
bool BankFile::isMeaningDeterminedAtImport(String meaning){
    return (   meaning == "NUM_INST"
            || meaning == "NUM_DRUM"
            || meaning == "NUM_SFX"
            || meaning == "NUM_PRED"
            || meaning == "Ptr Bank (in Audiobank)"
            || meaning == "Bank Length"
            || meaning == "Ptr Drum List"
            || meaning == "Ptr SFX List");
}
BankFile::NodeValueInfo BankFile::getNodeValueInfo(ValueTree node, bool hex){
    NodeValueInfo ret;
    if(!node.isValid()) return ret;
    String type = node.getType().toString();
    String meaning = node.getProperty("meaning", "None");
    if(type == "field" || type == "element"){
        if(isMeaningDeterminedAtImport(meaning)){
            ret.valueequiv = "Determined at import";
        }else if((bool)node.getProperty("isarray", false)){
            ret.valueequiv = "Open array to edit";
        }else if(node.getNumChildren() != 0){
            ret.valueequiv = "Open struct to edit";
        }else{
            ret.valueeditable = true;
            type = node.getProperty("datatype", "uint32");
            if(type == "float32"){
                float f = node.getProperty("value", 0.0f);
                ret.value = String(f);
                ret.valueequiv = "0x" + ROM::hex(*(uint32*)&f);
            }else{
                int val = (int)node.getProperty("value", 0);
                if((bool)node.getProperty("ispointer", false)){
                    ret.valuereference = true;
                    val = (int)node.getProperty("index", -1);
                    String ptrto = node.getProperty("ptrto", "Error");
                    ValueTree dest = getListForPointer(ptrto);
                    if(dest.isValid()){
                        dest = dest.getChild(val);
                        if(!dest.isValid()){
                            ret.valueequiv = "nullptr";
                        }else{
                            ret.valueequiv = dest.getProperty("name", "[unnamed]");
                        }
                    }
                }
                if(hex){
                    if(type == "uint8" || type == "int8" || ret.valuereference){
                        ret.value = ROM::hex((uint8)val);
                    }else{
                        ret.value = ROM::hex((uint32)val);
                    }
                }else{
                    ret.value = String(val);
                }
            }
        }
    }
    return ret;
}
bool BankFile::setNodeValue(ValueTree node, String input, bool hex){
    if(!node.isValid()) return false;
    String type = node.getType().toString();
    String meaning = node.getProperty("meaning", "None");
    if(type != "field" && type != "element") return false;
    if(isMeaningDeterminedAtImport(meaning)) return false;
    if((bool)node.getProperty("isarray", false)) return false;
    if(node.getNumChildren() != 0) return false;
    //Get value based on datatype
    String datatype = node.getProperty("datatype", "Error");
    if(datatype == "float32"){
        if((bool)node.getProperty("ispointer", false)) return false;
        float f = input.getFloatValue();
        node.setProperty("value", f, nullptr);
        return true;
    }else if(datatype ==  "int8" || datatype ==  "int16" || datatype ==  "int32" || 
             datatype == "uint8" || datatype == "uint16" || datatype == "uint32"){
        int val = 0;
        if(hex) val = input.getHexValue32();
            else val = input.getIntValue();
        if(datatype == "int8"){
            if(val < -0x80 || val > 0x7F) return false;
        }else if(datatype == "uint8"){
            if(val < 0 || val > 0xFF) return false;
        }else if(datatype == "int16"){
            if(val < -0x8000 || val > 0x7FFF) return false;
        }else if(datatype == "uint16"){
            if(val < 0 || val > 0xFFFF) return false;
        }
        if((bool)node.getProperty("ispointer", false)){
            node.setProperty("index", val, nullptr);
        }else{
            node.setProperty("value", val, nullptr);
        }
        return true;
    }else{
        SEQ64::say("BankFile::setNodeValue() error: datatype == " + datatype);
        return false;
    }
}
int BankFile::getNodeListFlags(ValueTree nodein, ValueTree nodeselected){
    if(!nodein.isValid()) return 0;
    String inname = nodein.getType().toString();
    if(inname == "instruments" || inname == "drums" || inname == "sfx" || inname == "envelopes"
            || inname == "samples" || inname == "aladpcmbooks" || inname == "aladpcmloops"){
        if(nodeselected.isValid()){
            return canAdd | canDupl | canDel | canMove;
        }else{
            return canAdd;
        }
    }
    if(inname == "field"){
        if((bool)nodein.getProperty("isarray", false) && nodein.hasProperty("arraylenvar")){
            if(nodeselected.isValid()){
                return canAdd | canDupl | canDel | canMove;
            }else{
                return canAdd;
            }
        }
    }
    if(!nodeselected.isValid()) return 0;
    String selname = nodeselected.getType().toString();
    if(selname == "abdrumlist" || selname == "absfxlist"){
        if(nodeselected.getNumChildren() == 0){
            return canAdd;
        }else{
            return canDel;
        }
    }
    return 0;
}
String BankFile::getNodePath(ValueTree node){
    if(!node.isValid()) return "Error!";
    String pathname = "/", desc;
    ValueTree temp = node;
    while(true){
        desc = getNodeDesc(temp);
        temp = getNodeParent(temp);
        if(!temp.isValid()) return pathname;
        pathname = "/" + desc + pathname;
    }
}
ValueTree BankFile::getNodeChild(ValueTree node, int childidx){
    if(!node.isValid()) return ValueTree();
    ValueTree ret = node.getChild(childidx);
    if(!ret.isValid()) return ValueTree();
    if(ret.getNumChildren() == 1 && ret.getChild(0).getType().toString() == "struct"){
        ret = ret.getChild(0);
    }
    return ret;
}
ValueTree BankFile::getNodeParent(ValueTree node){
    if(!node.isValid()) return ValueTree();
    if(!node.getParent().isValid()) return ValueTree();
    ValueTree ret = node;
    if(node.getParent().getNumChildren() == 1 && node.getType().toString() == "struct"){
        ret = ret.getParent();
    }
    ret = ret.getParent();
    return ret;
}
bool BankFile::addNode(ValueTree parent){
    //TODO
    SEQ64::say("BankFile::addNode() not yet implemented! Use Dupl if you can.");
    return false;
}
bool BankFile::duplicateNode(ValueTree parent, ValueTree child){
    if(!parent.isValid()) return false;
    if(!child.isValid()) return false;
    int childidx = parent.indexOf(child);
    if(childidx < 0 || childidx >= parent.getNumChildren()) return false;
    int nodeListFlags = getNodeListFlags(parent, child);
    if((nodeListFlags & BankFile::canDupl) == 0) return false;
    if(child.getType().toString() == "item"){
        ValueTree stru = child.getChild(0);
        if(!stru.isValid()){
            SEQ64::say("Item with no child struct!");
            return false;
        }
        String ptrtype = stru.getProperty("name", "Error");
        insertReferences(d, ptrtype, childidx+1);
    }
    ValueTree newChild = child.createCopy();
    parent.addChild(newChild, childidx+1, nullptr);
    return true;
}
bool BankFile::deleteNode(ValueTree parent, ValueTree child){
    if(!parent.isValid()) return false;
    if(!child.isValid()) return false;
    int childidx = parent.indexOf(child);
    if(childidx < 0 || childidx >= parent.getNumChildren()) return false;
    int nodeListFlags = getNodeListFlags(parent, child);
    if((nodeListFlags & BankFile::canDel) == 0) return false;
    if(child.getType().toString() == "item"){
        ValueTree stru = child.getChild(0);
        if(!stru.isValid()){
            SEQ64::say("Item with no child struct!");
            return false;
        }
        String ptrtype = stru.getProperty("name", "Error");
        deleteReferences(d, ptrtype, childidx);
    }
    parent.removeChild(child, nullptr);
    return true;
}
bool BankFile::moveNodeUp(ValueTree parent, ValueTree child){
    if(!parent.isValid()) return false;
    if(!child.isValid()) return false;
    int childidx = parent.indexOf(child);
    if(childidx < 1 || childidx >= parent.getNumChildren()) return false;
    int nodeListFlags = getNodeListFlags(parent, child);
    if((nodeListFlags & BankFile::canMove) == 0) return false;
    parent.moveChild(childidx, childidx-1, nullptr);
    if(child.getType().toString() == "item"){
        ValueTree stru = child.getChild(0);
        if(!stru.isValid()){
            SEQ64::say("Item with no child struct!");
            return false;
        }
        String ptrtype = stru.getProperty("name", "Error");
        swapReferences(d, ptrtype, childidx, childidx-1);
    }
    return true;
}
bool BankFile::moveNodeDown(ValueTree parent, ValueTree child){
    if(!parent.isValid()) return false;
    if(!child.isValid()) return false;
    int childidx = parent.indexOf(child);
    if(childidx < 0 || childidx >= parent.getNumChildren() - 1) return false;
    int nodeListFlags = getNodeListFlags(parent, child);
    if((nodeListFlags & BankFile::canMove) == 0) return false;
    parent.moveChild(childidx, childidx+1, nullptr);
    if(child.getType().toString() == "item"){
        ValueTree stru = child.getChild(0);
        if(!stru.isValid()){
            SEQ64::say("Item with no child struct!");
            return false;
        }
        String ptrtype = stru.getProperty("name", "Error");
        swapReferences(d, ptrtype, childidx, childidx+1);
    }
    return true;
}
/*
 * Recursively swap all references in parent and its children, that are pointers to
 * type pointername, between swapFrom and swapTo. Will not swap null references (< 0) 
 * to valid ones: i.e. swapReferences(p, "t", -1, 5) will change all 5s to -1s but 
 * leave all -1s alone; and swapReferences(p, "t", 5, -1) will do exactly the same thing.
 */
void BankFile::swapReferences(ValueTree parent, String pointername, int swapFrom, int swapTo){
    if(!parent.isValid()) return;
    ValueTree child;
    for(int i=0; i<parent.getNumChildren(); i++){
        child = parent.getChild(i);
        if((bool)child.getProperty("ispointer", false) && child.getProperty("ptrto").toString() == pointername){
            if((int)child.getProperty("index", -1) == swapFrom && swapFrom >= 0){
                child.setProperty("index", swapTo, nullptr);
            }else if((int)child.getProperty("index", -1) == swapTo && swapTo >= 0){
                child.setProperty("index", swapFrom, nullptr);
            }
        }
        swapReferences(child, pointername, swapFrom, swapTo);
    }
}
/*
 * Recursively increment all references greater than or equal to index (because a new
 * item appeared at index).
 */
void BankFile::insertReferences(ValueTree parent, String pointername, int index){
    if(!parent.isValid()) return;
    ValueTree child;
    int childindex;
    for(int i=0; i<parent.getNumChildren(); i++){
        child = parent.getChild(i);
        if((bool)child.getProperty("ispointer", false) && child.getProperty("ptrto").toString() == pointername){
            childindex = (int)child.getProperty("index", -1);
            if(childindex >= index){
                child.setProperty("index", childindex+1, nullptr);
            }
        }
        insertReferences(child, pointername, index);
    }
}
/*
 * Recursively decrement all references greater than index, and set all references
 * to index to nullptr (-1).
 */
void BankFile::deleteReferences(ValueTree parent, String pointername, int index){
    if(!parent.isValid()) return;
    ValueTree child;
    int childindex;
    for(int i=0; i<parent.getNumChildren(); i++){
        child = parent.getChild(i);
        if((bool)child.getProperty("ispointer", false) && child.getProperty("ptrto").toString() == pointername){
            childindex = (int)child.getProperty("index", -1);
            if(childindex == index){
                child.setProperty("index", -1, nullptr);
            }else if(childindex > index){
                child.setProperty("index", childindex-1, nullptr);
            }
        }
        deleteReferences(child, pointername, index);
    }
}

/*
 * Are the two items, and all the other items they reference, equal?
 */
bool BankFile::deepCompareItems(String itemtype, BankFile& banka, int itemindexa, 
        BankFile& bankb, int itemindexb){
    ValueTree lista = banka.getListForPointer(itemtype);
    ValueTree listb = bankb.getListForPointer(itemtype);
    if(!lista.isValid() || !listb.isValid()){
        SEQ64::say("deepCompareItems() invalid item type " + itemtype);
        return false;
    }
    ValueTree itema = lista.getChild(itemindexa);
    ValueTree itemb = listb.getChild(itemindexb);
    if(!itema.isValid() || !itemb.isValid()){
        SEQ64::say("deepCompareItems() invalid item indices");
        return false;
    }
    return deepCompareNodes(banka, itema, bankb, itemb);
}
/*
 * Are the two nodes, and all the items they reference, equal?
 */
bool BankFile::deepCompareNodes(BankFile& banka, ValueTree nodea, 
        BankFile& bankb, ValueTree nodeb){
    if(nodea.getType() != nodeb.getType()) return false;
    if(nodea.getNumChildren() != nodeb.getNumChildren()) return false;
    if(!compareProperty(nodea, nodeb, "name")) return false;
    if(!compareProperty(nodea, nodeb, "datatype")) return false;
    if(!compareProperty(nodea, nodeb, "ispointer")) return false;
    if(!compareProperty(nodea, nodeb, "ptrto")) return false;
    if(!compareProperty(nodea, nodeb, "isarray")) return false;
    if(!compareProperty(nodea, nodeb, "arraylenvar")) return false;
    if(!compareProperty(nodea, nodeb, "arraylenfixed")) return false;
    if(!compareProperty(nodea, nodeb, "meaning")) return false;
    if(!compareProperty(nodea, nodeb, "NUM_PRED")) return false;
    if(!compareProperty(nodea, nodeb, "HAS_TAIL")) return false;
    if(!(bool)nodea.getProperty("isarray")){
        if((bool)nodea.getProperty("ispointer")){
            if(!deepCompareItems(nodea.getProperty("ptrto"),
                    banka, nodea.getProperty("index"),
                    bankb, nodeb.getProperty("index"))) return false;
        }else{
            if(!compareProperty(nodea, nodeb, "value")) return false;
        }
    }
    for(int i=0; i<nodea.getNumChildren(); i++){
        if(!deepCompareNodes(banka, nodea.getChild(i),
                             bankb, nodeb.getChild(i))) return false;
    }
    return true;
}
bool BankFile::compareProperty(ValueTree nodea, ValueTree nodeb, String name){
    if(nodea.hasProperty(name) != nodeb.hasProperty(name)) return false;
    if(nodea.getProperty(name, "") != nodeb.getProperty(name, "")) return false;
    return true;
}
/*
 * Import a node with the given type and index (e.g. "ABInstrument", 5) from 
 * sourcebank into this bank. If merge, and an identical node already exists,
 * use that node instead. Return the imported or existing node.
 */
ValueTree BankFile::importNode(ROM& rom, BankFile& sourcebank, String itemtype, int itemindex, 
        bool merge, bool fixsampleaddr){
    SEQ64::say("Importing node " + itemtype + " index " + String(itemindex));
    //Get item
    ValueTree sourcelist = sourcebank.getListForPointer(itemtype);
    ValueTree destlist   = getListForPointer(itemtype);
    if(!sourcelist.isValid() || !destlist.isValid()){
        SEQ64::say("importNode() invalid item type " + itemtype);
        return ValueTree();
    }
    ValueTree sourceitem = sourcelist.getChild(itemindex);
    if(!sourceitem.isValid()){
        SEQ64::say("importNode() invalid item index");
        return ValueTree();
    }
    //Check if identical item exists
    if(merge){
        ValueTree noded;
        for(int di=0; di<destlist.getNumChildren(); di++){
            noded = destlist.getChild(di);
            if(deepCompareNodes(*this, noded, sourcebank, sourceitem)){
                return noded;
            }
        }
    }
    //Otherwise, import
    return importNodeRecurse(rom, sourcebank, merge, fixsampleaddr, sourceitem, destlist);
}
ValueTree BankFile::importNodeRecurse(ROM& rom, BankFile& sourcebank, bool merge, bool fixsampleaddr,
        ValueTree sourcenode, ValueTree destparent){
    //SEQ64::say("Importing sourcenode " + sourcenode.getType().toString() 
    //      + " into destparent " + destparent.getType().toString());
    //Copy type
    ValueTree destnode = ValueTree(sourcenode.getType());
    //Copy all properties
    Identifier propname;
    for(int p=0; p<sourcenode.getNumProperties(); p++){
        propname = sourcenode.getPropertyName(p);
        destnode.setProperty(propname, sourcenode.getProperty(propname), nullptr);
    }
    //Check for sample address to fix
    while(fixsampleaddr && destnode.getProperty("meaning", "None").toString() 
                == "Sample Address (in Sample Table)"){
        uint32 origaddr = (uint32)(int)destnode.getProperty("value", 0);
        int src_ATnum = (int)sourcebank.d.getProperty("ATnum", -1);
        int dest_ATnum = (int)d.getProperty("ATnum", -1);
        SEQ64::say("Trying to fix sample address: src_ATnum=" + String(src_ATnum) 
                + ", dest_ATnum=" + String(dest_ATnum));
        if(src_ATnum < 0 || dest_ATnum < 0){
            SEQ64::say("--Source or dest bank don't have Sample Table number!");
            break;
        }
        //Read table number
        ValueTree atinode = romdesc.getOrCreateChildWithName("knownfilelist", nullptr)
                .getChildWithProperty("type", "Audiotable Index");
        uint32 atiaddr = 0x7FFFFFFF;
        if(atinode.isValid()){
            atiaddr = (uint32)(int)atinode.getProperty("address", 0x7FFFFFFF);
        }
        if(atiaddr >= rom.getSize()){
            SEQ64::say("--Nonexistent or invalid Audiotable Index in romdesc!");
            break;
        }
        uint16 count;
        if((int)romdesc.getProperty("indextype", 1) == 2){
            count = rom.readHalfWord(atiaddr);
        }else{
            count = rom.readHalfWord(atiaddr+2);
        }
        if(count > 1000 || count <= 0){
            SEQ64::say("--" + String(count) + " entries in Audiotable Index, probably wrong!");
            break;
        }
        if(src_ATnum >= (int)count || dest_ATnum >= (int)count){
            SEQ64::say("--Source or dest bank have Sample Table number larger than Audiotable Index count!");
            break;
        }
        uint32 src_tbladdr, dest_tbladdr;
        if((int)romdesc.getProperty("indextype", 1) == 2){
            src_tbladdr = rom.readWord(atiaddr + (16*src_ATnum) + 16);
            dest_tbladdr = rom.readWord(atiaddr + (16*dest_ATnum) + 16);
        }else{
            src_tbladdr = rom.readWord(atiaddr + (8*src_ATnum) + 4);
            dest_tbladdr = rom.readWord(atiaddr + (8*dest_ATnum) + 4);
        }
        SEQ64::say("--src_tbladdr=0x" + ROM::hex(src_tbladdr) 
                + ", dest_tbladdr=0x" + ROM::hex(dest_tbladdr));
        uint32 newaddr = origaddr + src_tbladdr - dest_tbladdr;
        SEQ64::say("--Moving sample addr from 0x" + ROM::hex(origaddr) + " to 0x" + ROM::hex(newaddr));
        destnode.setProperty("value", (int)newaddr, nullptr);
        break;
    }
    //Add newly created child to parent in this
    destparent.addChild(destnode, -1, nullptr);
    //If this is a pointer, import the node it's pointing to
    if(!(bool)destnode.getProperty("isarray") && (bool)destnode.getProperty("ispointer")){
        String itemtype = destnode.getProperty("ptrto", "Error").toString();
        int itemindex = (int)destnode.getProperty("index", -1);
        if(itemindex >= 0){
            //SEQ64::say("Going to import new node " + itemtype + " index " + String(itemindex));
            ValueTree reftarget = importNode(rom, sourcebank, itemtype, itemindex, merge, fixsampleaddr);
            if(reftarget.isValid()){
                destnode.setProperty("index", reftarget.getParent().indexOf(reftarget), nullptr);
                destnode.setProperty("value", "1337", nullptr);
            }else{
                SEQ64::say("Could not import node " + itemtype + " " + String(itemindex) + "!");
                destnode.setProperty("index", -1, nullptr);
                destnode.setProperty("value", "6969", nullptr);
            }
        }
    }
    //Import children
    for(int c=0; c<sourcenode.getNumChildren(); c++){
        importNodeRecurse(rom, sourcebank, merge, fixsampleaddr, sourcenode.getChild(c), destnode);
    }
    return destnode;
}
