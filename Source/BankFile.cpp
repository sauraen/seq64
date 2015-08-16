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
    }
    node.setProperty("index", listindex, nullptr);
    //Get item name from rdnamesnode
    ValueTree nnlist = rdnamesnode.getOrCreateChildWithName(list.getType().toString(), nullptr);
    ValueTree nnitem = nnlist.getChildWithProperty("index", listindex);
    if(!nnitem.isValid()){
        nnitem = ValueTree("item");
        nnitem.setProperty("index", listindex, nullptr);
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

ValueTree BankFile::getListForPointer(String pointertype){
    if(pointertype == "ABDrumList"){
        return d.getChildWithName("abdrumlist");
    }else if(pointertype == "ABSFXList"){
        return d.getChildWithName("absfxlist");
    }else if(pointertype == "ABInstrument"){
        return d.getChildWithName("instruments");
    }else if(pointertype == "ABDrum"){
        return d.getChildWithName("drums");
    }else if(pointertype == "ABPatchProps"){
        return d.getChildWithName("patchprops");
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
    int strsize;
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
                fieldelement.setProperty("ispointer", ispointer, nullptr);
                if(ispointer) fieldelement.setProperty("ptrto", ptrto, nullptr);
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
                dstru = getListForPointer(ptrto);
                if(dstru.isValid()){
                    if(ptrto == "ABDrumList" || ptrto == "ABSFXList"){
                        if(dstru.hasProperty("address")){
                            SEQ64::say("Multiple pointers to " + ptrto + ", changing address from " 
                                    + dstru.getProperty("address", "Error").toString() + " to "
                                    + String(val) + "!");
                        }
                        dstru.setProperty("address", val, nullptr);
                    }else{
                        checkAddListItem(dstru, val, fieldelement);
                    }
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
            if(parenttype == "instruments" || parenttype == "drums" || parenttype == "sfx" || parenttype == "patchprops"
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
                type = node.getProperty("datatype", "uint32");
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
    return ret;
}
bool BankFile::setNodeValue(ValueTree node, String input, bool hex){
    if(!node.isValid()) return false;
    String type = node.getType().toString();
    String meaning = node.getProperty("meaning", "None");
    int val = 0;
    if(hex) val = input.getHexValue32();
        else val = input.getIntValue();
    String datatype = node.getProperty("datatype", "Error");
    if(datatype == "int8"){
        if(val < -0x80 || val > 0x7F) return false;
    }else if(datatype == "uint8"){
        if(val < 0 || val > 0xFF) return false;
    }else if(datatype == "int16"){
        if(val < -0x8000 || val > 0x7FFF) return false;
    }else if(datatype == "uint16"){
        if(val < 0 || val > 0xFFFF) return false;
    }else if(datatype != "int32" && datatype != "uint32"){
        SEQ64::say("BankFile::setNodeValue() error: datatype == " + datatype);
        return false;
    }
    if(type == "field" || type == "element"){
        if(isMeaningDeterminedAtImport(meaning)){
            return false;
        }else if((bool)node.getProperty("isarray", false)){
            return false;
        }else if(node.getNumChildren() != 0){
            return false;
        }else{
            if((bool)node.getProperty("ispointer", false)){
                node.setProperty("index", val, nullptr);
            }else{
                node.setProperty("value", val, nullptr);
            }
            return true;
        }
    }
    return false;
}
int BankFile::getNodeListFlags(ValueTree nodein, ValueTree nodeselected){
    if(!nodein.isValid()) return 0;
    String inname = nodein.getType().toString();
    if(inname == "instruments" || inname == "drums" || inname == "sfx" || inname == "patchprops"
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
ValueTree BankFile::importNode(BankFile& sourcebank, String itemtype, int itemindex, bool merge){
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
    return importNodeRecurse(sourcebank, merge, sourceitem, destlist);
}
ValueTree BankFile::importNodeRecurse(BankFile& sourcebank, bool merge, 
        ValueTree sourcenode, ValueTree destparent){
    //SEQ64::say("Importing sourcenode " + sourcenode.getType().toString() + " into destparent " + destparent.getType().toString());
    //Copy type
    ValueTree destnode = ValueTree(sourcenode.getType());
    //Copy all properties
    Identifier propname;
    for(int p=0; p<sourcenode.getNumProperties(); p++){
        propname = sourcenode.getPropertyName(p);
        destnode.setProperty(propname, sourcenode.getProperty(propname), nullptr);
    }
    //Add newly created child to parent in this
    destparent.addChild(destnode, -1, nullptr);
    //If this is a pointer, import the node it's pointing to
    if(!(bool)destnode.getProperty("isarray") && (bool)destnode.getProperty("ispointer")){
        String itemtype = destnode.getProperty("ptrto", "Error").toString();
        int itemindex = (int)destnode.getProperty("index", -1);
        if(itemindex >= 0){
            //SEQ64::say("Going to import new node " + itemtype + " index " + String(itemindex));
            ValueTree reftarget = importNode(sourcebank, itemtype, itemindex, merge);
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
        importNodeRecurse(sourcebank, merge, sourcenode.getChild(c), destnode);
    }
    return destnode;
}

/*
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
*/
