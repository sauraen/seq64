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
    NUM_INST = NUM_DRUM = NUM_SFX = NUM_BANK = SSIindex = -1;
}


ValueTree BankFile::getCopyOfTemplate(String name){
    ValueTree stru = abfstructsnode.getChildWithProperty("name", name);
    if(!stru.isValid()){
        stru = ValueTree("struct");
        stru.setProperty("name", name, nullptr);
        abfstructsnode.addChild(stru, -1, nullptr);
    }
    return stru.createCopy();
}

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


void BankFile::loadElementList(ROM& rom, uint32 baseaddr, int bank_length, String listname, String elementname){
    uint32 a;
    ValueTree stru = d.getChildWithName(listname);
    ValueTree temp, item;
    int count = stru.getNumChildren();
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
        readStruct(rom, a + baseaddr, item);
    }
}


void BankFile::load(ROM& rom, uint32 abientryaddr, uint32 abfaddr){
    //Check inputs
    if(abientryaddr >= rom.getSize() || abfaddr >= rom.getSize()){
        DBG("Invalid addresses to BankFile::load!");
        return;
    }
    //Init
    uint32 a, baseaddr;
    int strsize, i, count;
    ValueTree temp, stru, item;
    reset();
    //========================================================================
    //Load index entry
    //========================================================================
    stru = getCopyOfTemplate("ABIndexEntry");
    d.getChildWithName("abindexentry").addChild(stru, -1, nullptr);
    readStruct(rom, abientryaddr, stru);
    //Read relevant data from index entry
    temp = stru.getChildWithProperty("meaning", "Ptr Bank (in Audiobank)");
    if(!temp.isValid()){
        DBG("ABIndexEntry must include a field with meaning Ptr Bank (in Audiobank)!");
        return;
    }
    uint32 ptr_bank = (int)temp.getProperty("value", 0x8000000);
    if(ptr_bank + abfaddr >= rom.getSize()){
        DBG("Ptr Bank " + ROM::hex(ptr_bank) + " + base " + ROM::hex(abfaddr) + " goes off end of ROM!");
        return;
    }
    //
    temp = stru.getChildWithProperty("meaning", "Bank Length");
    if(!temp.isValid()){
        DBG("ABIndexEntry must include a field with meaning Bank Length!");
        return;
    }
    uint32 bank_length = (int)temp.getProperty("value", 0x8000000);
    if(bank_length >= 0x20000){
        DBG("Bank Length " + ROM::hex(bank_length) + ", probably wrong!");
        return;
    }
    //
    temp = stru.getChildWithProperty("meaning", "Sample Set Index number");
    if(temp.isValid()){
        SSIindex = temp.getProperty("value", 0);
    }
    //
    temp = stru.getChildWithProperty("meaning", "NUM_INST");
    if(temp.isValid()){
        NUM_INST = temp.getProperty("value", 0);
    }
    //
    temp = stru.getChildWithProperty("meaning", "NUM_DRUM");
    if(temp.isValid()){
        NUM_DRUM = temp.getProperty("value", 0);
    }
    //
    temp = stru.getChildWithProperty("meaning", "NUM_SFX");
    if(temp.isValid()){
        NUM_SFX = temp.getProperty("value", 0);
    }
    //========================================================================
    //Load bank header
    //========================================================================
    stru = getCopyOfTemplate("ABHeader");
    d.getChildWithName("abheader").addChild(stru, -1, nullptr);
    a = abfaddr + ptr_bank;
    strsize = readStruct(rom, a, stru);
    a += strsize;
    baseaddr = a;
    //Read relevant data from header
    temp = stru.getChildWithProperty("meaning", "NUM_INST");
    if(temp.isValid()){
        NUM_INST = temp.getProperty("value", 0);
    }
    if(NUM_INST < 0){
        DBG("NUM_INST not defined in either ABIndexEntry or ABHeader!");
        return;
    }
    //========================================================================
    //Load bank (main)
    //========================================================================
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
        stru = getCopyOfTemplate("ABDrumList");
        d.getChildWithName("abdrumlist").addChild(stru, -1, nullptr);
        readStruct(rom, a, stru);
    }
    temp = d.getChildWithName("absfxlist");
    if((int)temp.getProperty("address", -1) > 0){
        a = baseaddr + (int)temp.getProperty("address");
        stru = getCopyOfTemplate("ABSFXList");
        d.getChildWithName("absfxlist").addChild(stru, -1, nullptr);
        readStruct(rom, a, stru);
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
    
}
void BankFile::save(ROM& rom, uint32 abientryaddr, uint32 abfaddr){
    
}

int BankFile::readStruct(ROM& rom, uint32 addr, ValueTree stru){
    if(!stru.isValid()) return 0;
    int len = 0, fieldlen;
    int count = stru.getNumChildren();
    String struname = stru.getProperty("name", "Error");
    ValueTree field, sub, dstru;
    String datatype, ptrto, arraylenvar, meaning;
    bool ispointer, isarray;
    int arraylenfixed;
    uint32 a = addr;
    int val;
    int dstruindex;
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
            }else{
                arraylenfixed = -1;
                arraylenvar = field.getProperty("arraylenvar", 0).toString();
            }
        }
        meaning = field.getProperty("meaning", "None").toString();
        //Read data from ROM
        //TODO arrays
        if(datatype == "uint32" || datatype == "int32"){
            val = rom.readWord(a);
            fieldlen = 4;
        }else if(datatype == "uint16"){
            val = rom.readHalfWord(a);
            fieldlen = 2;
        }else if(datatype == "int16"){
            val = (int16)rom.readHalfWord(a);
            fieldlen = 2;
        }else if(datatype == "uint8"){
            val = rom.readByte(a);
            fieldlen = 1;
        }else if(datatype == "int16"){
            val = (int8)rom.readByte(a);
            fieldlen = 1;
        }else if(datatype == "ABSound" || datatype == "ALADPCMPredictor" || datatype == "ALADPCMTail"){
            sub = getCopyOfTemplate(datatype);
            field.addChild(sub, -1, nullptr);
            fieldlen = readStruct(rom, a, sub);
            val = 0;
        }else{
            DBG("Invalid data type " + datatype + "!")
            return 0;
        }
        field.setProperty("value", val, nullptr);
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
                DBG("Invalid pointer type " + ptrto + "!")
                return 0;
            }
        }
    }
}
int BankFile::writeStruct(ROM& rom, uint32 addr, ValueTree stru){
    
}

int BankFile::getLength(){
    //TODO
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

