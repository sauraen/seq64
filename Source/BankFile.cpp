/*
  ==============================================================================

    BankFile.cpp
    Created: 2 Jan 2015 9:03:51pm
    Author: Sauraen

  ==============================================================================
*/

#include "BankFile.h"
#include "ROM.h"


BankFile::BankFile(ValueTree romdesc){
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
 * given address. If it doens't exist, create it. In either case, write back the
 * index within that list of the found/created item to the given node.
 */
void BankFile::checkAddListItem(String listname, int addressval, ValueTree node){
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
}

/**
 * For any of the elements of d which are lists: for the existing contents of
 * the list (with addresses already saved to them), go through each element 
 * and load its struct as a new child of that element.
 */
void BankFile::loadElementList(ROM& rom, uint32 baseaddr, int bank_length, String listname, String elementname){
    DBG("Loading element list " + listname + "...");
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
            DBG("In " + listname + " list, item " + String(i) + ": ptr outside bank @" + ROM::hex(a) + "!"); 
            continue; 
        }
        item = getCopyOfTemplate(elementname);
        temp.addChild(item, -1, nullptr);
        ret = readStruct(rom, a + baseaddr, item);
        if(ret < 0){
            DBG("Reading " + elementname + " index " + String(i) + " from " + listname + " failed");
            return;
        }
    }
}

/**
 * Load a complete Audiobank file, given the addresses of the index entry and 
 * the file itself.
 */
bool BankFile::load(ROM& rom, uint32 abientryaddr, uint32 abfaddr){
    DBG("Loading bank file from index entry @" + ROM::hex(abientryaddr) + ", file @" + ROM::hex(abfaddr));
    //Check inputs
    if(abientryaddr >= rom.getSize() || abfaddr >= rom.getSize()){
        DBG("Invalid addresses to BankFile::load!");
        return false;
    }
    //Init
    uint32 a, baseaddr;
    int strsize, i, count;
    ValueTree temp, stru, item;
    reset();
    //========================================================================
    //Load index entry
    //========================================================================
    DBG("Reading index entry...");
    stru = getCopyOfTemplate("ABIndexEntry");
    d.getChildWithName("abindexentry").addChild(stru, -1, nullptr);
    readStruct(rom, abientryaddr, stru);
    //Copy relevant data from index entry into C++ class
    temp = stru.getChildWithProperty("meaning", "Ptr Bank (in Audiobank)");
    if(!temp.isValid()){
        DBG("ABIndexEntry must include a field with meaning Ptr Bank (in Audiobank)!");
        return false;
    }
    uint32 ptr_bank = (int)temp.getProperty("value", 0x8000000);
    if(ptr_bank + abfaddr >= rom.getSize()){
        DBG("Ptr Bank " + ROM::hex(ptr_bank) + " + base " + ROM::hex(abfaddr) + " goes off end of ROM!");
        return false;
    }
    //
    temp = stru.getChildWithProperty("meaning", "Bank Length");
    if(!temp.isValid()){
        DBG("ABIndexEntry must include a field with meaning Bank Length!");
        return false;
    }
    uint32 bank_length = (int)temp.getProperty("value", 0x8000000);
    if(bank_length >= 0x20000){
        DBG("Bank Length " + ROM::hex(bank_length) + ", probably wrong!");
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
    DBG("Reading bank header...");
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
        DBG("NUM_INST not defined in either ABIndexEntry or ABHeader!");
        return false;
    }
    //========================================================================
    //Load bank (main)
    //========================================================================
    DBG("Reading bank main...");
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
        DBG("Reading ABDrumList from @" + ROM::hex(a));
        stru = getCopyOfTemplate("ABDrumList");
        d.getChildWithName("abdrumlist").addChild(stru, -1, nullptr);
        readStruct(rom, a, stru);
    }else{
        DBG("No ABDrumList found");
    }
    temp = d.getChildWithName("absfxlist");
    if((int)temp.getProperty("address", -1) > 0){
        a = baseaddr + (int)temp.getProperty("address");
        DBG("Reading ABSFXList from @" + ROM::hex(a));
        stru = getCopyOfTemplate("ABSFXList");
        d.getChildWithName("absfxlist").addChild(stru, -1, nullptr);
        readStruct(rom, a, stru);
    }else{
        DBG("No ABSFXList found");
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
    DBG("Done loading bank!");
}
bool BankFile::save(ROM& rom, uint32 abientryaddr, uint32 abfaddr){
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
                    DBG("Invalid array length variable " + arraylenvar + "!");
                    return -1;
                }
                if(arraymax < 0){
                    DBG("Array length using not-yet-set variable " + arraylenvar + "!");
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
                DBG("Invalid data type " + datatype + "!");
                return -1;
            }
            //Length, address, data
            fieldlen += fieldelementlen;
            a += fieldelementlen;
            fieldelement.setProperty("value", val, nullptr);
            //Meaning
            if(ispointer){
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
                    DBG("Invalid pointer type " + ptrto + "!");
                    return -1;
                }
            }
            if(meaning == "NUM_INST" || meaning == "NUM_DRUM" || meaning == "NUM_SFX"){
                if(isarray){
                    DBG("Array cannot have meaning " + meaning + "!");
                }else{
                    if((int)d.getProperty(meaning) >= 0){
                        DBG("Overwriting global property " + meaning + " with value " + String(val));
                    }
                    d.setProperty(meaning, val, nullptr);
                }
            }else if(meaning == "NUM_PRED" || meaning == "HAS_TAIL" || meaning == "Loop Start"){
                if(isarray){
                    DBG("Array cannot have meaning " + meaning + "!");
                }else{
                    if(meaning == "Loop Start"){
                        int ht = (val > 0) ? 1 : 0;
                        DBG("Loop Start " + String(val) + ", setting HAS_TAIL to " + String(ht));
                        stru.setProperty("HAS_TAIL", ht, nullptr);
                    }else{
                        if((int)stru.getProperty(meaning) >= 0){
                            DBG("Overwriting local property " + meaning + " with value " + String(val));
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
                DBG("Could not find struct named " + datatype + "!");
                baselen = 4;
            }else{
                baselen = getLength(fieldstruct);
            }
        }
        //TODO variable array lengths
    }
}

