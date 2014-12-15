/*
  ==============================================================================

    SeqFile.cpp
    Created: 1 Nov 2014 12:01:52pm
    Author:  Sauraen

  ==============================================================================
*/

#include "SeqFile.h"
#include "ROM.h"

Identifier SeqFile::idName("name");
Identifier SeqFile::idLength("length");
Identifier SeqFile::idAction("action");
Identifier SeqFile::idCmd("cmd");
Identifier SeqFile::idCmdEnd("cmdend");
Identifier SeqFile::idMeaning("meaning");
Identifier SeqFile::idValue("value");
Identifier SeqFile::idAdd("add");
Identifier SeqFile::idMultiply("multiply");
Identifier SeqFile::idDataSrc("datasrc");
Identifier SeqFile::idDataLen("datalen");
Identifier SeqFile::idDataAddr("dataaddr");
Identifier SeqFile::idDataActualLen("dataactuallen");
Identifier SeqFile::idValidInSeq("validinseq");
Identifier SeqFile::idValidInChn("validinchn");
Identifier SeqFile::idValidInTrk("validintrk");

Identifier SeqFile::idSType("stype");
Identifier SeqFile::idChannel("channel");
Identifier SeqFile::idLayer("layer");
Identifier SeqFile::idTSection("tsection");
Identifier SeqFile::idSection("section");
Identifier SeqFile::idAddress("address");
Identifier SeqFile::idAddressEnd("address_end");
Identifier SeqFile::idHash("hash");
Identifier SeqFile::idTargetSection("targetsection");
Identifier SeqFile::idTargetHash("targethash");
Identifier SeqFile::idWillDrop("willdrop");

SeqTSection::SeqTSection(){
	time = 0;
	address = 0;
	address_end = 0;
}

SeqData::SeqData(){
	address = 0;
	address_end = 0;
	stype = 0;
	channel = 0;
	layer = 0;
	calldepth = 0;
	finished = 0;
	tsection = 0;
}

CCTracker::CCTracker(){
    action= "";
    q_time = 0;
    lasttime = 0;
    q_amp = 0;
    lastvalue = 0;
}

SeqFile::SeqFile(ROM& rom, ValueTree romdesc, uint32 seqaddr, uint32 length){
    debug = false;
    cmdlist = romdesc.getOrCreateChildWithName("cmdlist", nullptr);
    midiopts = romdesc.getOrCreateChildWithName("midiopts", nullptr);
    if(rom.isByteSwapped && ((seqaddr & 0x00000003) || (length & 0x00000003))){
        DBG("Byte-swapped ROM with non-word-aligned data... this will end poorly!");
    }
    if(length >= 10000000){
        DBG("Trying to load sequence more than 10MB! Crashing to protect your computer!");
        int* crash = nullptr;
        *crash = 0; //Dereference null pointer
        return;
    }
    data.ensureStorageAllocated(length);
    for(int i=0; i<length; i++){
        data.add(rom.readByte(i+seqaddr));
    }
    DBG("Copied ROM data to sequence, size == " + ROM::hex((uint32)data.size()));
    trim();
}
SeqFile::SeqFile(ValueTree romdesc){
    debug = false;
    cmdlist = romdesc.getOrCreateChildWithName("cmdlist", nullptr);
    midiopts = romdesc.getOrCreateChildWithName("midiopts", nullptr);
    data.clearQuick();
    data.ensureStorageAllocated(0x8000); //Should be enough
}

SeqFile::~SeqFile(){
    
}
uint8 SeqFile::readByte(uint32 address){
    return data[address];
}
void SeqFile::writeByte(uint32 address, uint8 d){
    data.set(address, d);
}


uint32 SeqFile::getLength(){
    return data.size();
}

void SeqFile::saveToROM(ROM& rom, uint32 start_addr){
    DBG("Saving " + ROM::hex((uint32)data.size(), 4) + " bytes to sequence @" + ROM::hex(start_addr));
    for(int i=0; i<data.size(); i++){
        rom.writeByte(i+start_addr, data[i]);
    }
}

void SeqFile::trim(){
    int lastbyte = data.size() - 1;
    for(; lastbyte >= 0; lastbyte--){
        if(data[lastbyte] != 0){
            break;
        }
    }
    lastbyte = (lastbyte & 0xFFFFFFFC) + 4;
    if(lastbyte >= data.size()){
        DBG("SeqFile::trim(): no trim required");
        return;
    }
    DBG("Trimming SeqFile from " + ROM::hex((uint32)data.size(), 4) + " to " + ROM::hex((uint32)lastbyte, 4) + " bytes");
    data.removeRange(lastbyte, data.size() - lastbyte);
}

//Stype: 0 seq hdr, 1 chn hdr, 2 track data
ValueTree SeqFile::getDescription(uint8 firstbyte, int stype){
    ValueTree test;
    for(int i=0; i<cmdlist.getNumChildren(); i++){
        test = cmdlist.getChild(i);
        if(       (stype == 0 && (bool)test.getProperty(idValidInSeq, false))
                ||(stype == 1 && (bool)test.getProperty(idValidInChn, false))
                ||(stype == 2 && (bool)test.getProperty(idValidInTrk, false))){
            if(test.hasProperty(idCmdEnd)){
                if(firstbyte >= (int)test.getProperty(idCmd)
                        && firstbyte <= (int)test.getProperty(idCmdEnd)){
                    return test;
                }
            }else{
                if(firstbyte == (int)test.getProperty(idCmd)){
                    return test;
                }
            }
        }
    }
    test = ValueTree();
    return test;
}

ValueTree SeqFile::getCommand(uint32 address, int stype){
    ValueTree ret("command");
    ValueTree param, desc;
    String action, meaning, datasrc;
    int i, len, paramlen, paramindex, cmdoffset, paramvalue, datalen;
    uint8 c, d;
    uint32 a = address;
    //
    len = 1;
    c = data[address];
    a++;
    desc = getDescription(c, stype);
    if(desc.isValid()){
        ret = desc.createCopy();
        cmdoffset = c - (int)ret.getProperty(idCmd, 0);
        action = desc.getProperty(idAction, "No Action");
        //DBG(ROM::hex((uint32)address, 6) + ": " + ROM::hex(c) + " " + action);
        for(paramindex=0; paramindex<ret.getNumChildren(); paramindex++){
            param = ret.getChild(paramindex);
            meaning = param.getProperty(idMeaning, "None");
            //Get the value of this parameter
            paramvalue = 0;
            paramlen = 0;
            datasrc = param.getProperty(idDataSrc, "fixed");
            datalen = param.getProperty(idDataLen, 0);
            if(datasrc == "offset"){
                paramvalue = cmdoffset;
                param.setProperty(idDataAddr, 0, nullptr);
                param.setProperty(idDataActualLen, 1, nullptr);
            }else if(datasrc == "fixed"){
                for(i=0; i<datalen; i++){
                    len++;
                    paramlen++;
                    paramvalue <<= 8;
                    paramvalue += (uint8)data[a+i];
                }
                param.setProperty(idDataAddr, (int)(a-address), nullptr);
                param.setProperty(idDataActualLen, paramlen, nullptr);
            }else if(datasrc == "variable"){
                if(datalen == 1){
                    d = (uint8)data[a];
                    if(d <= 0x7F){
                        paramvalue = d;
                        len++;
                        paramlen++;
                    }
                }else if(datalen == 2){
                    d = 0;
                    len++;
                    paramlen++;
                    paramvalue = (uint8)data[a];
                    if(paramvalue & 0x80){
                        paramvalue &= 0x7F;
                        paramvalue <<= 8;
                        paramvalue += (uint8)data[a+1];
                        len++;
                        paramlen++;
                    }
                }else{
                    DBG("Due to SeqFile variable length format, length > 2 not defined!");
                    paramvalue = 0;
                    len += datalen;
                    paramlen += datalen;
                    /*
                    while(true){
                        d = (uint8)data[a+i];
                        paramvalue <<= 7;
                        if(i >= datalen){
                            //Last byte
                            paramvalue += (uint8)d;
                            break;
                        }else{
                            //Intermediate byte
                            paramvalue += (uint8)(d & 0x7F);
                            if(!(d & 0x80)) break;
                        }
                        i++;
                        len++;
                        paramlen++;
                    }
                    */
                }
                param.setProperty(idDataAddr, (int)(a-address), nullptr);
                param.setProperty(idDataActualLen, paramlen, nullptr);
            }else{
                DBG("Invalid command description! datasrc == " + datasrc + ", action == " + action);
            }
            //Store info about parameter
            param.setProperty(idValue, paramvalue, nullptr);
            a += paramlen;
        }
        //Store info about command
        ret.setProperty(idCmd, (int)c, nullptr);
        if(ret.hasProperty(idCmdEnd)){
            ret.removeProperty(idCmdEnd, nullptr);
        }
    }else{
        //Command not found
        ret.setProperty(idCmd, (int)c, nullptr);
    }
    ret.setProperty(idLength, len, nullptr);
    return ret;
}

int SeqFile::getAdjustedValue(const ValueTree& param){
    if(!param.hasProperty(idValue)) return 0;
    int origvalue = (int)param.getProperty(idValue);
    //Add first
    origvalue += (int)param.getProperty(idAdd, 0);
    origvalue = (int)((double)origvalue * (double)param.getProperty(idMultiply, 1.0f));
    return origvalue;
}

int SeqFile::getPtrAddress(ValueTree command, uint32 currentAddr){
    ValueTree param = command.getChildWithProperty(idMeaning, "Absolute Address");
    int address;
    if(param.isValid()){
        address = getAdjustedValue(param);
    }else{
        param = command.getChildWithProperty(idMeaning, "Relative Address");
        if(param.isValid()){
            address = (int)getAdjustedValue(param) + (int)currentAddr;
        }else{
            DBG("@" + ROM::hex(currentAddr,4) + ": Pointer with no address value!");
            return -1;
        }
    }
    if(address >= data.size()){
        DBG("@" + ROM::hex(currentAddr,4) + ": Pointer off end of sequence to " 
                + ROM::hex((uint32)address,4) + ", skipping!");
        return -1;
    }
    return address;
}

int SeqFile::getCommandRange(ValueTree command, String meaning){
    if(!command.isValid()) return 0;
    ValueTree param = command.getChildWithProperty(idMeaning, meaning);
    if(!param.isValid()) return 0;
    String datasrc = param.getProperty(idDataSrc, "fixed");
    int datalen = param.getProperty(idDataLen, 0);
    if(datasrc == "fixed"){
        return 1 << (datalen << 3); //2^number of bytes
    }else if(datasrc == "variable"){
        if(datalen == 1){
            return 0x80;
        }else if(datalen == 2){
            return 0x8000;
        }else{
            return 0;
        }
    }else if(datasrc == "offset"){
        return (int)command.getProperty(idCmdEnd) - (int)command.getProperty(idCmd) + 1;
    }
    return 0;
}

SeqData* SeqFile::getOrMakeSectionAt(uint32 a){
    for(int s=0; s<sections.size(); s++){
        if(sections[s]->address == a){
            return sections[s];
        }
    }
    SeqData* newsection = new SeqData();
    newsection->address = a;
	newsection->address_end = a;
	newsection->channel = 0;
	newsection->layer = 0;
	newsection->stype = 0;
	newsection->tsection = 0;
	newsection->calldepth = 0;
    newsection->finished = 0;
    sections.add(newsection);
    return newsection;
}
bool SeqFile::isSectionAt(uint32 a, int stype){
    for(int s=0; s<sections.size(); s++){
        if(sections[s]->address != a) continue;
        if(sections[s]->stype != stype){
            DBG("Pointer to section @" + ROM::hex(a,4) + " from stype " 
                    + String(stype) + " to stype " + String(sections[s]->stype) + "!");
        }
        return true;
    }
    return false;
}
int SeqFile::getNumSections(){
    return sections.size();
}
SeqData* SeqFile::getSection(int s){
    if(s < 0 || s >= sections.size()) return nullptr;
    return sections[s];
}
String SeqFile::getSectionDescription(int s){
    if(s < 0 || s >= sections.size()) return "";
    SeqData* sec = sections[s];
    String ret = "@" + ROM::hex(sec->address, 4) + ": ";
    if(sec->stype == 0){
        ret += "Seq -- --";
    }else if(sec->stype == 1){
        ret += "Chn " + String(sec->channel).paddedLeft(' ', 2) + " --";
    }else{
        ret += "Trk " + String(sec->channel).paddedLeft(' ', 2) + " " + String(sec->layer).paddedLeft(' ', 2);
    }
    ret += " " + String(sec->cmdoffsets.size());
    return ret;
}

String SeqFile::getCommandDescription(int s, int c){
    if(s < 0 || s >= sections.size()) return "";
    String ret = "";
    SeqData* section = sections[s];
    if(c < 0 || c >= section->cmdoffsets.size()) return "";
    uint32 a = section->cmdoffsets[c];
    ValueTree cmd = getCommand(a, section->stype);
    int len = cmd.getProperty(idLength, 1);
    for(int i=0; i<len; i++){
        ret += ROM::hex(data[a+i]) + " ";
    }
    ret = ret.paddedRight(' ', 15);
    ret = "@" + ROM::hex(a, 4) + ": " + ret;
    ret += cmd.getProperty(idName, "[Unknown Cmd]").toString();
    return ret;
}

void SeqFile::insertSpaceAt(uint32 address, int size, int enlargeSection){
    //Fix pointers
    SeqData* sec;
    ValueTree command, param;
    String action;
    int c;
    uint32 a;
    int addrOfChangeSection = -1;
    if(enlargeSection >= 0 && enlargeSection < sections.size()){
        addrOfChangeSection = sections[enlargeSection]->address;
    }
    for(int s=0; s<sections.size(); s++){
        sec = sections[s];
        if(s == enlargeSection){
            if(sec->address > address){
                sec->address += size;
            }
            if(sec->address_end >= address){
                sec->address_end += size;
            }
        }else{
            if(sec->address >= address){
                sec->address += size;
            }
            if(sec->address_end > address){
                sec->address_end += size;
            }
        }
        for(c=0; c<sec->cmdoffsets.size(); c++){
            a = sec->cmdoffsets[c];
            editCmdPointer(a, sec->stype, address, size, addrOfChangeSection);
            if(a >= address){
                sec->cmdoffsets.set(c, a + size);
            }
        }
    }
    //Actually insert space
    data.insertMultiple(address, 0, size);
}
void SeqFile::removeData(uint32 address, int size, int shrinkSection){
    if(size <= 0){
        DBG("Asked to remove data with invalid size " + String(size) + "!");
        return;
    }
    //Fix pointers
    SeqData* sec;
    ValueTree command, param;
    int c;
    uint32 a;
    int addrOfChangeSection = -1;
    if(shrinkSection >= 0 && shrinkSection < sections.size()){
        addrOfChangeSection = sections[shrinkSection]->address;
    }
    for(int s=0; s<sections.size(); s++){
        sec = sections[s];
        if(sec->address >= address){
            sec->address -= size;
            if(sec->address < address) sec->address = address;
        }
        for(c=0; c<sec->cmdoffsets.size(); c++){
            a = sec->cmdoffsets[c];
            editCmdPointer(a, sec->stype, address, 0-size, addrOfChangeSection);
            if(a >= address){
                a -= size;
                if(a < address) a = address;
                sec->cmdoffsets.set(c, a);
            }
        }
        if(sec->address_end >= address){
            sec->address_end -= size;
            if(sec->address_end < address) sec->address_end = address;
        }
    }
    //Actually delete data
    data.removeRange(address, size);
}

void SeqFile::editCmdPointer(uint32 cmdaddr, int stype, uint32 daddr, int dsize, int addrOfChangeSection){
    ValueTree command = getCommand(cmdaddr, stype);
    String action = command.getProperty(idAction);
    //Fix absolute pointers
    ValueTree param = command.getChildWithProperty(idMeaning, "Absolute Address");
    if(param.isValid()){
        if(param.getProperty(idDataSrc, "fixed").toString() != "fixed"){
            DBG("Address command parameters must be fixed-length! (in " + action + ")");
            return;
        }
        int oldvalue = (int)param.getProperty(idValue, 0);
        //if(debug) DBG("Editing ptr @" + ROM::hex(cmdaddr,4) + " to @" + ROM::hex((uint32)oldvalue,4));
        if(oldvalue >= daddr){
            if(oldvalue == daddr && addrOfChangeSection == daddr){
                return; //Leave pointer
            }
            int newvalue = oldvalue + dsize;
            //if(debug) DBG("----Updating to " + ROM::hex((uint32)newvalue,4));
            int datalen = (int)param.getProperty(idDataLen, 1);
            //Check out-of-range
            if(newvalue < 0 || newvalue >= (1 << (datalen << 3))){ //8-bit for one, 16-bit for two...
                DBG("Absolute address pointer going out-of-range @" + ROM::hex(cmdaddr,4) 
                        + " in " + action + ", now " + String(newvalue) + "!");
                return;
            }
            int a = cmdaddr + (int)param.getProperty(idDataAddr, 1);
            for(int i=a+datalen-1; i>=a; i--){
                data.set(i, (newvalue & 0xFF));
                newvalue >>= 8;
            }
        }
        return;
    }
    //Fix relative pointers
    param = command.getChildWithProperty(idMeaning, "Relative Address");
    if(param.isValid()){
        if(param.getProperty(idDataSrc, "fixed").toString() != "fixed"){
            DBG("Address command parameters must be fixed-length! (in " + action + ")");
            return;
        }
        int oldvalue = (int)param.getProperty(idValue, 0);
        //DBG("Relative address value @" + ROM::hex(cmdaddr,4) + " parsed to " + String(oldvalue));
        int newvalue = 0;
        int datalen = (int)param.getProperty(idDataLen, 1);
        if(cmdaddr >= daddr && (int)cmdaddr + oldvalue < daddr){
            newvalue = oldvalue - dsize;
        }else if(cmdaddr < daddr && (int)cmdaddr + oldvalue >= daddr){
            newvalue = oldvalue + dsize;
        }else{
            return;
        }
        //Check out-of-range
        int max_value = (1 << ((datalen << 3) - 1)) - 1; //7-bit for one, 15-bit for two...
        if(newvalue < 0 - max_value || newvalue > max_value){
            DBG("Relative address pointer going out-of-range @" + ROM::hex(cmdaddr,4) 
                    + " in " + action + ", now " + String(newvalue) + "!");
            return;
        }
        int a = cmdaddr + (int)param.getProperty(idDataAddr, 1);
        for(int i=a+datalen-1; i>=a; i--){
            data.set(i, (newvalue & 0xFF));
            newvalue >>= 8;
        }
    }
}

int SeqFile::editCmdParam(int section, uint32 address, int stype, String meaning, int newvalue){
    DBG("Editing command parameter @" + ROM::hex(address,4) + " stype " + String(stype) + " " + meaning + " to " + ROM::hex((uint32)newvalue));
    int ret = 0;
    ValueTree command = getCommand(address, stype);
    ValueTree param = command.getChildWithProperty(idMeaning, meaning);
    if(!param.isValid()){
        DBG("Error: asked to edit command parameter with meaning " + meaning + ", does not exist!");
        return -1;
    }
    int value = param.getProperty(idValue, 0);
    if(newvalue == value) return 0;
    uint32 a = address + (int)param.getProperty(idDataAddr, 1);
    String datasrc = param.getProperty(idDataSrc, "fixed");
    int datalen = param.getProperty(idDataLen, 1);
    //int dataactuallen = param.getProperty(idDataActualLen, 1);
    if(datasrc == "offset"){
        int cmdbegin = command.getProperty(idCmd, 0);
        int cmdend = command.getProperty(idCmdEnd, 0);
        if(newvalue > (cmdend - cmdbegin) || newvalue < 0) return -1;
        data.set(a, cmdbegin + newvalue);
    }else if(datasrc == "fixed"){
        for(int i=a+datalen-1; i>=a; i--){
            data.set(i, (newvalue & 0xFF));
            newvalue >>= 8;
        }
    }else if(datasrc == "variable"){
        if(newvalue < 0) newvalue = 0;
        if(datalen == 1){
            if(newvalue > 0x7F) newvalue = 0x7F;
            if(value == 0){
                //Make room for value
                insertSpaceAt(a, 1, section);
                ret = 1;
                data.set(a, newvalue);
            }else{
                if(newvalue == 0){
                    removeData(a, 1, section);
                    ret = 1;
                }else{
                    data.set(a, newvalue);
                }
            }
        }else if(datalen == 2){
            if(newvalue >= 0x8000) newvalue = 0x8000;
            if(value <= 0x7F && newvalue >= 0x80){
                insertSpaceAt(a+1, 1, section);
                ret = 1;
            }else if(value >= 0x80 && newvalue <= 0x7F){
                removeData(a+1, 1, section);
                ret = 1;
            }
            if(newvalue <= 0x7F){
                data.set(a, newvalue);
            }else{
                data.set(a, 0x80 + (newvalue >> 8));
                data.set(a+1, (newvalue & 0xFF));
            }
        }else{
            DBG("Due to SeqFile variable length format, length > 2 not defined!");
            return -1;
        }
    }else{
         DBG("Invalid command description! datasrc == " + datasrc);
         return -1;
    }
    return ret;
}

ValueTree SeqFile::wantAction(String action, int stype){
    ValueTree ret("wantedcmd");
    ret.setProperty(idAction, action, nullptr);
    ret.setProperty(idSType, stype, nullptr);
    return ret;
}
void SeqFile::wantProperty(ValueTree want, String meaning, int value){
    ValueTree sub("wantedproperty");
    sub.setProperty(idMeaning, meaning, nullptr);
    sub.setProperty(idValue, value, nullptr);
    want.addChild(sub, -1, nullptr);
}
ValueTree SeqFile::createCommand(ValueTree want){
    if(!want.isValid()) return want;
    int stype = want.getProperty(idSType);
    String action = want.getProperty(idAction);
    String meaning;
    ValueTree test, param, param2;
    ValueTree possibleCmdsList("possiblecmdslist");
    bool flag;
    int i, j, range, value;
    for(i=0; i<cmdlist.getNumChildren(); i++){
        test = cmdlist.getChild(i);
        if((      (stype == 0 && (bool)test.getProperty(idValidInSeq, false))
                ||(stype == 1 && (bool)test.getProperty(idValidInChn, false))
                ||(stype == 2 && (bool)test.getProperty(idValidInTrk, false)))
                && test.getProperty(idAction).toString() == action){
            //See if it has ways to set all the meanings we want
            flag = true;
            for(j=0; j<want.getNumChildren(); j++){
                meaning = want.getChild(j).getProperty(idMeaning);
                param = test.getChildWithProperty(idMeaning, meaning);
                if(!param.isValid()){
                    flag = false;
                    break;
                }
                //Check range
                value = want.getChild(j).getProperty(idValue);
                range = getCommandRange(test, meaning);
                if(value >= range){
                    //DBG("--Looking for " + action + " command, meaning " + meaning 
                    //        + ", throwing out due to range " + String(range) + " vs. value " + String(value));
                    flag = false;
                    break;
                }
            }
            if(flag){
                //This might be the command we're looking for
                test = test.createCopy();
                possibleCmdsList.addChild(test, -1, nullptr);
            }
        }
    }
    if(possibleCmdsList.getNumChildren() == 0){
        DBG("No " + action + " command defined in stype " + String(stype) + " with all the needed parameters!");
        for(j=0; j<want.getNumChildren(); j++){
            DBG("----Want: " + want.getChild(j).getProperty(idMeaning).toString()
                    + " value " + want.getChild(j).getProperty(idValue).toString());
        }
        test = ValueTree();
        return test;
    }
    //Figure out which one would be shortest
    int lowestCmdLen = 100000;
    int lowestCmdIndex = 0;
    int cmdlen, datalen;
    String datasrc;
    for(i=0; i<possibleCmdsList.getNumChildren(); i++){
        test = possibleCmdsList.getChild(i);
        //Determine length of this command with the given data
        cmdlen = 1;
        for(j=0; j<test.getNumChildren(); j++){
            param = test.getChild(j);
            datasrc = param.getProperty(idDataSrc, "fixed");
            datalen = param.getProperty(idDataLen, 1);
            param2 = want.getChildWithProperty(idMeaning, param.getProperty(idMeaning));
            if(param.isValid()){
                value = param2.getProperty(idValue);
            }else{
                value = 0;
            }
            if(datasrc == "offset"){
                //do nothing
            }else if(datasrc == "fixed"){
                cmdlen += datalen;
            }else if(datasrc == "variable"){
                if(datalen == 1 && value > 0){
                    cmdlen++;
                }else if(datalen == 2){
                    cmdlen++;
                    if(value >= 0x80) cmdlen++;
                }
            }
        }
        if(cmdlen < lowestCmdLen){
            lowestCmdLen = cmdlen;
            lowestCmdIndex = i;
        }
    }
    //Get best one
    test = possibleCmdsList.getChild(lowestCmdIndex);
    //Set all values
    for(j=0; j<test.getNumChildren(); j++){
        param2 = test.getChild(j);
        param = want.getChildWithProperty(idMeaning, param2.getProperty(idMeaning));
        if(param.isValid()){
            param2.setProperty(idValue, param.getProperty(idValue), nullptr);
        }else{
            param2.setProperty(idValue, 0, nullptr);
        }
    }
    //Hash
    test.setProperty(idHash, Random::getSystemRandom().nextInt(), nullptr);
    return test;
}

ValueTree SeqFile::createMarker(){
    ValueTree ret("marker");
    ret.setProperty(idAction, "Marker", nullptr);
    ret.setProperty(idHash, Random::getSystemRandom().nextInt(), nullptr);
    return ret;
}

int SeqFile::getNewCommandLength(ValueTree command){
    if(!command.isValid()) return 0;
    if(command.getProperty(idAction, "No Action").toString() == "Marker") return 0;
    int cmdlen = 1;
    ValueTree param;
    int p, datalen, value;
    String datasrc;
    for(p=0; p<command.getNumChildren(); p++){
        param = command.getChild(p);
        datasrc = param.getProperty(idDataSrc, "fixed");
        datalen = param.getProperty(idDataLen, 1);
        value = param.getProperty(idValue, 0);
        if(datasrc == "offset"){
            //do nothing
        }else if(datasrc == "fixed"){
            cmdlen += datalen;
        }else if(datasrc == "variable"){
            if(datalen == 1 && value > 0){
                cmdlen++;
            }else if(datalen == 2){
                cmdlen++;
                if(value >= 0x80) cmdlen++;
            }
        }
    }
    return cmdlen;
}

void SeqFile::writeCommand(uint32 address, ValueTree command){
    if(!command.isValid()) return;
    if(command.getProperty(idAction, "No Action").toString() == "Marker") return;
    ValueTree param;
    int i, p, datalen, value;
    String datasrc;
    //Write command byte
    uint8 d = (int)command.getProperty(idCmd);
    param = command.getChildWithProperty(idDataSrc, "offset");
    if(param.isValid()){
        d += (int)param.getProperty(idValue);
    }
    data.set(address, d);
    address++;
    //Write parameters
    for(p=0; p<command.getNumChildren(); p++){
        param = command.getChild(p);
        datasrc = param.getProperty(idDataSrc, "fixed");
        datalen = param.getProperty(idDataLen, 1);
        value = param.getProperty(idValue, 0);
        if(datasrc == "offset"){
            //do nothing
        }else if(datasrc == "fixed"){
            for(i=datalen-1; i>=0; i--){
                d = (value & 0x000000FF);
                data.set(address+i, d);
                value >>= 8;
            }
            address += datalen;
        }else if(datasrc == "variable"){
            if(value < 0) value = 0;
            if(datalen == 1){
                if(value > 0){
                    if(value > 0x7F) value = 0x7F;
                    d = (value & 0x0000007F);
                    data.set(address, d);
                    address++;
                }
            }else if(datalen == 2){
                if(value <= 0x7F){
                    d = value;
                    data.set(address, d);
                    address++;
                }else{
                    d = (value & 0x000000FF);
                    data.set(address+1, d);
                    value >>= 8;
                    d = (value & 0x0000007F) | 0x80;
                    data.set(address, d);
                    address += 2;
                }
            }else{
                DBG("Variable datalen only supported with length 1 or 2!");
            }
        }else{
            DBG("Unknown datasrc: " + datasrc);
        }
    }
}

void SeqFile::insertCommand(int section, int cmdidx, ValueTree command){
    if(!command.isValid()) return;
    //DBG("Writing command " + command.getProperty(idAction).toString() + " section " 
    //        + String(section) + " index " + String(cmdidx));
    if(section >= sections.size() || section < 0){
        DBG("Invalid section " + String(section));
        return;
    }
    SeqData* sec = sections[section];
    int address_start = sec->address;
    ValueTree param;
    String datasrc;
    int datalen, value, p, i;
    //Get address to insert command at
    uint32 address;
    bool insertAtEnd = false;
    if(cmdidx < sec->cmdoffsets.size() && cmdidx >= 0){
        address = sec->cmdoffsets[cmdidx];
    }else{
        cmdidx = sec->cmdoffsets.size();
        address = sec->address_end;
        insertAtEnd = true;
    }
    //Figure out how many bytes to insert
    int cmdlen = getNewCommandLength(command);
    //See if an absolute address in the command itself will be affected by its own insertion
    param = command.getChildWithProperty(idMeaning, "Absolute Address");
    if(param.isValid()){
        int oldvalue = (int)param.getProperty(idValue, 0);
        if(oldvalue >= address){
            int newvalue = oldvalue + cmdlen;
            param.setProperty(idValue, newvalue, 0);
        }
    }
    //Insert the room for the bytes into the data
    insertSpaceAt(address, cmdlen, section);
    //Set up cmdoffset for new command
    sec->cmdoffsets.insert(cmdidx, address);
    //Write command
    writeCommand(address, command);
}

void SeqFile::deleteCommand(int section, int cmdidx){
    if(section >= sections.size() || section < 0){
        DBG("Invalid section " + String(section));
        return;
    }
    SeqData* sec = sections[section];
    if(cmdidx >= sec->cmdoffsets.size() || cmdidx < 0){
        DBG("Invalid command " + String(section));
        return;
    }
    int address_start = sec->address;
    uint32 address = sec->cmdoffsets[cmdidx];
    ValueTree command = getCommand(address, sec->stype);
    int cmdlen = command.getProperty(idLength, 1);
    //Delete the cmdoffset
    sec->cmdoffsets.remove(cmdidx);
    //Delete the data
    removeData(address, cmdlen, section);
}

void SeqFile::parse(){
    sections.clear();
    DBG("Sequence starts with " 
            + ROM::hex(data[0]) + ROM::hex(data[1]) + ROM::hex(data[2]) + ROM::hex(data[3])
            + ROM::hex(data[4]) + ROM::hex(data[5]) + ROM::hex(data[6]) + ROM::hex(data[7]));
    ValueTree command, param;
    String action, meaning;
    int cmdlen = 1, channel, notelayer, value;
    uint32 a = 0;
    const int stack_size = 8;
    uint32 addrstack[stack_size];
    int stypestack[stack_size];
    SeqData* sectionstack[stack_size];
    uint32 address;
    int stackptr = 0;
    int stype = 0;
    SeqData* sec;
    SeqData* tmpsec;
    //Initial section
    sec = getOrMakeSectionAt(0);
    sec->stype = 0;
    //
    DBG("Parsing Sequence");
    while(a < data.size()){
        //See if we just ran into any existing section
        for(value=0; value<sections.size(); value++){
            tmpsec = sections[value];
            if(tmpsec == sec) continue;
            if(tmpsec->address > a || tmpsec->address < (a - cmdlen + 1)) continue;
            //Ran over existing section's start
            if(tmpsec->address == a){
                //At least we landed right on it
                if(!tmpsec->finished){
                    //Unfinished, that's good
                    if(tmpsec->stype == stype){
                        DBG("@" + ROM::hex(a,4) + ": ran into branch destination (normal)");
                    }else{
                        DBG("@" + ROM::hex(a,4) + ": reading section ran into start of previously-jumped-to section of DIFFERENT type!");
                    }
                    sections.remove(value);
                    value--;
                }else{
                    DBG("@" + ROM::hex(a,4) + ": reading section ran into start of already-read data!");
                }
            }else{
                DBG("@" + ROM::hex(a,4) + ": reading section lawnmowed across start of existing section!");
            }
        }
        sec->cmdoffsets.add(a);
        command = getCommand(a, stype);
        cmdlen = (int)command.getProperty(idLength, 1);
        a += cmdlen;
        action = command.getProperty(idAction, "Unknown");
        //Normal actions
        if(action == "Unknown"){
            //do nothing
        }else if(action == "No Action"){
            //do nothing
        }else if(action == "Timestamp"){
            //do nothing
        }else if(action == "End of Data"){
            //Mark current section as finished
            sec->finished = 1;
            if(stackptr == 0){
                //Was parent section
                //Look for non-finished sections
                for(value=0; value<sections.size(); value++){
                    if(!sections[value]->finished){
                        break;
                    }
                }
                if(value >= sections.size()){
                    //No non-finished sections
                    DBG("Finished parsing sequence");
                    return;
                }
                //Finish this section
                sec = sections[value];
                a = sec->address;
                stype = sec->stype;
                channel = sec->channel;
                notelayer = sec->layer;
                DBG("Finishing unfinished section @" + ROM::hex(a,4));
            }else{
                //Go back to parent section
                stackptr--;
                //Restore values
                a = addrstack[stackptr];
                stype = stypestack[stackptr];
                sec = sectionstack[stackptr];
            }
        }else if(action == "Jump Same Level"){
            value = getPtrAddress(command, a);
            if(value < 0) continue;
            address = value;
            DBG("Jump Same Level @" + ROM::hex(a,4) + " to @" + ROM::hex(address,4));
            if(address <= a && address >= sec->address){
                //Pointer is to earlier in the current section
                DBG("...earlier in same section");
                continue;
            }
            //Make a new section, but don't jump to it
            DBG("...making new section for later");
            tmpsec = getOrMakeSectionAt(address);
            tmpsec->stype = stype;
            tmpsec->channel = channel;
            tmpsec->layer = notelayer;
        }else if(action == "Call Same Level"){
            value = getPtrAddress(command, a);
            if(value < 0) continue;
            address = value;
            if(isSectionAt(address, stype)){
                //Already have gone there, skip
                continue;
            }
            //Jump to new address
            sec->address_end = a;
            addrstack[stackptr] = a;
            stypestack[stackptr] = stype;
            sectionstack[stackptr] = sec;
            stackptr++;
            if(stackptr >= stack_size){
                DBG("FATAL: Stack Overflow SeqFile::parse()!");
                break;
            }
            a = address;
            sec = getOrMakeSectionAt(a);
            sec->stype = stype;
            sec->channel = channel;
            sec->layer = notelayer;
        }else if(action == "Loop Start"){
            //do nothing
        }else if(action == "Loop End"){
            //do nothing
        }else if(action == "Ptr Channel Header"){
            if(stype != 0){
                DBG("@" + ROM::hex(a,4) + ": Ptr Channel Header from something other than seq header!");
                continue;
            }
            value = getPtrAddress(command, a);
            if(value < 0) continue;
            address = value;
            if(isSectionAt(address, stype)){
                //Already have gone there, skip
                continue;
            }
            param = command.getChildWithProperty(idMeaning, "Channel");
            if(param.isValid()){
                channel = getAdjustedValue(param);
            }
            if(channel >= 16){
                DBG("Ptr Channel Header with channel >= 16!");
                continue;
            }
            //Jump to new address
            sec->address_end = a;
            addrstack[stackptr] = a;
            stypestack[stackptr] = stype;
            sectionstack[stackptr] = sec;
            stackptr++;
            if(stackptr >= stack_size){
                DBG("FATAL: Stack Overflow SeqFile::parse()!");
                break;
            }
            a = address;
            stype = 1;
            sec = getOrMakeSectionAt(a);
            sec->stype = 1;
            sec->channel = channel;
        }else if(action == "Ptr Track Data"){
            if(stype != 1){
                DBG("@" + ROM::hex(a,4) + ": Ptr Track Data from something other than a channel!");
                continue;
            }
            value = getPtrAddress(command, a);
            if(value < 0) continue;
            address = value;
            if(isSectionAt(address, stype)){
                //Already have gone there, skip
                continue;
            }
            param = command.getChildWithProperty(idMeaning, "Note Layer");
            if(!param.isValid()){
                DBG("Ptr Track Data with no note layer value!");
                continue;
            }
            notelayer = getAdjustedValue(param);
            //Jump to new address
            sec->address_end = a;
            addrstack[stackptr] = a;
            stypestack[stackptr] = stype;
            sectionstack[stackptr] = sec;
            stackptr++;
            if(stackptr >= stack_size){
                DBG("FATAL: Stack Overflow SeqFile::parse()!");
                break;
            }
            a = address;
            stype = 2;
            sec = getOrMakeSectionAt(a);
            sec->stype = 2;
            sec->channel = channel;
            sec->layer = notelayer;
        }else if(action == "Sequence Format"){
            //do nothing
        }else if(action == "Sequence Type"){
            //do nothing
        }else if(action == "Channel Enable"){
            //do nothing
        }else if(action == "Channel Disable"){
            //do nothing
        }else if(action == "Master Volume"){
            //do nothing
        }else if(action == "Tempo"){
            //do nothing
        }else if(action == "Chn Reset"){
            //do nothing
        }else if(action == "Chn Priority"){
            //do nothing
        }else if(action == "Chn Volume"){
            //do nothing
        }else if(action == "Chn Pan"){
            //do nothing
        }else if(action == "Chn Effects"){
            //do nothing
        }else if(action == "Chn Vibrato"){
            //do nothing
        }else if(action == "Chn Pitch Bend"){
            //do nothing
        }else if(action == "Chn Instrument"){
            //do nothing
        }else if(action == "Chn Transpose"){
            //do nothing
        }else if(action == "Layer Transpose"){
            //do nothing
        }else if(action == "Track Note"){
            //do nothing
        }else{
            DBG("Unknown command action " + action + "!");
        }
    }
    DBG("Parsing sequence ran off end! a==" + ROM::hex(a) + ", length==" + ROM::hex((uint32)data.size()));
}


MidiFile* SeqFile::toMIDIFile(){
    ValueTree command, param;
    String action, meaning;
    int channel, notelayer, value, transpose, delay, note, velocity, gate;
    bool qDelay, qVelocity, qGate;
    uint32 address, t, a;
    int stype = 0;
    int cmdlen;
    //Stacks
    const int stack_size = 8;
    uint32 addrstack[stack_size];
    uint32 timestack[stack_size];
    int stypestack[stack_size];
    int stackptr = 0;
    //TSections
    OwnedArray<SeqTSection> tsections;
    SeqTSection* curtsec;
    bool willBeNewTSec = false;
    curtsec = new SeqTSection();
    curtsec->address = 0;
    curtsec->time = 0;
    tsections.add(curtsec);
    //Transpose
    int max_layers = 4;
	Array<int> transposes;
	transposes.resize(16 * max_layers);
    //CC Setup
    int ticks_multiplier = midiopts.getProperty("ppqnmultiplier", 1);
    if(ticks_multiplier <= 0) ticks_multiplier = 1;
    int bend_range = midiopts.getProperty("bendrange", 6);
    if(bend_range <= 0) bend_range = 1;
    String chnvol = midiopts.getProperty("chnvol", "CC7 (Volume)").toString();
    String mtrvol = midiopts.getProperty("mtrvol", "CC24 (None)").toString();
    String chnpriority = midiopts.getProperty("chnpriority", "CC25 (None)").toString();
    const int midi_basenote = 21;
    //MIDI file/tracks setup
    MidiMessage msg;
    MidiFile* ret = new MidiFile();
    ret->setTicksPerQuarterNote(48 * ticks_multiplier);
    MidiMessageSequence mastertrack;
    OwnedArray<MidiMessageSequence> mtracks;
    for(channel=0; channel<16; channel++){
        mtracks.add(new MidiMessageSequence());
        //Pitch bend range RPN
        msg = MidiMessage::controllerEvent(channel+1, 101, 0);
        msg.setTimeStamp(0);
        mtracks[channel]->addEvent(msg);
        msg = MidiMessage::controllerEvent(channel+1, 100, 0);
        msg.setTimeStamp(0);
        mtracks[channel]->addEvent(msg);
        msg = MidiMessage::controllerEvent(channel+1, 6, bend_range);
        msg.setTimeStamp(0);
        mtracks[channel]->addEvent(msg);
        msg = MidiMessage::controllerEvent(channel+1, 38, 0);
        msg.setTimeStamp(0);
        mtracks[channel]->addEvent(msg);
    }
    msg = MidiMessage::textMetaEvent(0x06, "Section 0");
    msg.setTimeStamp(0);
    mastertrack.addEvent(msg);
    //BEGIN
    DBG("EXPORTING MIDI FILE");
    t = 0;
    a = 0;
	channel = notelayer = 0;
	delay = 0;
    bool ended_naturally = false;
    while(a < data.size()){
        command = getCommand(a, stype);
        cmdlen = (int)command.getProperty(idLength, 1);
        a += cmdlen;
        action = command.getProperty(idAction, "Unknown");
        //Normal actions
        if(action == "Unknown"){
            //do nothing
            DBG("Unknown Action " + ROM::hex((uint8)(int)command.getProperty(idCmd)) 
                    + " in stype " + String(stype) + " @" + ROM::hex(a, 6));
        }else if(action == "No Action"){
            //do nothing
        }else if(action == "Sequence Format"){
            //do nothing
        }else if(action == "Sequence Type"){
            //do nothing
        }else if(action == "Channel Enable"){
            //do nothing
        }else if(action == "Channel Disable"){
            //do nothing
        }else if(action == "Timestamp"){
            //Time difference taken care of by delay
            if(stype == 0){
                willBeNewTSec = true; //Next Ptr Chan Hdr will be a new section
            }
        }else if(action == "End of Data"){
            if(stackptr == 0){
                ended_naturally = true;
                break; //Done with header
            }
            //Pop return address
            stackptr--;
            //Restore values
            a = addrstack[stackptr];
            if(stypestack[stackptr] != stype){
                //Return from chn or track, not call
                t = timestack[stackptr];
                stype = stypestack[stackptr];
            }
        }else if(action == "Jump Same Level"){
            DBG("Ignoring Jump Same Level @" + ROM::hex(a,4));
        }else if(action == "Call Same Level"){
            value = getPtrAddress(command, a);
            if(value < 0) continue;
            address = value;
            addrstack[stackptr] = a;
            timestack[stackptr] = 100000; //This value should never be popped!
            stypestack[stackptr] = stype;
            stackptr++;
            if(stackptr >= stack_size){
                DBG("FATAL: Stack Overflow SeqFile::toMIDIFile()!");
                break;
            }
            a = address;
        }else if(action == "Ptr Channel Header"){
            value = getPtrAddress(command, a);
            if(value < 0) continue;
            address = value;
            param = command.getChildWithProperty(idMeaning, "Channel");
            if(param.isValid()){
                channel = getAdjustedValue(param);
            }
            if(channel >= 16){
                DBG("Ptr Channel Header with channel >= 16!");
                continue;
            }
            //Valid pointer
            //MIDI file section
            if(willBeNewTSec){
                DBG("New section @" + ROM::hex(a,4) + ", t=" + ROM::hex(t,4));
                //Finish current section
                curtsec->address_end = a - cmdlen;
                //Make new section
                curtsec = new SeqTSection();
                curtsec->address = a - cmdlen;
                curtsec->time = t;
                tsections.add(curtsec);
                //Put marker in MIDI
                msg = MidiMessage::textMetaEvent(0x06, "Section " + String(tsections.size() - 1));
                msg.setTimeStamp(t*ticks_multiplier);
                mastertrack.addEvent(msg);
                //Done
                willBeNewTSec = false;
            }
            //Jump to channel data
            addrstack[stackptr] = a;
            timestack[stackptr] = t;
            stypestack[stackptr] = stype;
            stackptr++;
            if(stackptr >= stack_size){
                DBG("FATAL: Stack Overflow SeqFile::toMIDIFile()!");
                break;
            }
            a = address;
            stype = 1;
            velocity = 127;
            gate = 0xFF;
            //DBG("----T" + ROM::hex(t, 6) + ": Entering Chan " + String(channel) + " Hdr");
        }else if(action == "Ptr Track Data"){
            value = getPtrAddress(command, a);
            if(value < 0) continue;
            address = value;
            param = command.getChildWithProperty(idMeaning, "Note Layer");
            if(!param.isValid()){
                DBG("Ptr Track Data with no note layer value!");
                continue;
            }
            notelayer = getAdjustedValue(param);
            addrstack[stackptr] = a;
            timestack[stackptr] = t;
            stypestack[stackptr] = stype;
            stackptr++;
            if(stackptr >= stack_size){
                DBG("FATAL: Stack Overflow SeqFile::toMIDIFile()!");
                break;
            }
            a = address;
            stype = 2;
            //DBG("----====T" + ROM::hex(t, 6) + ": Entering Track layer " + String(notelayer));
            //DBG("@" + ROM::hex(a, 6) + ": Track Data " + String(notelayer));
        }else if(action == "Master Volume"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                DBG("Master Volume event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            if(value > 0x7F) value = 0x7F;
            if(value < 0) value = 0;
            int cc = -1;
            if(mtrvol == "CC7 (Volume)"){
                cc = 7;
            }else if(mtrvol == "CC11 (Expr)"){
                cc = 11;
            }else if(mtrvol == "CC16 (GPC1)"){
                cc = 16;
            }else if(mtrvol == "CC24 (None)"){
                cc = 24;
            }else if(mtrvol == "SysEx MstrVol"){
                char sysexdata[6];
                sysexdata[0] = 0x7F;
                sysexdata[1] = 0x7F;
                sysexdata[2] = 0x04;
                sysexdata[3] = 0x01;
                sysexdata[4] = 0x7F;
                sysexdata[5] = value;
                msg = MidiMessage::createSysExMessage(sysexdata, 6);
                msg.setTimeStamp(t*ticks_multiplier);
                mastertrack.addEvent(msg);
                continue;
            }else{
                DBG("Master Volume event, unknown mapping: " + mtrvol + ", ignoring");
                continue;
            }
            if(stype == 0){
                for(channel=0; channel<16; channel++){
                    msg = MidiMessage::controllerEvent(channel+1, cc, value);
                    msg.setTimeStamp(t*ticks_multiplier);
                    mtracks[channel]->addEvent(msg);
                }
                channel = 0;
            }else{
                msg = MidiMessage::controllerEvent(channel+1, cc, value);
                msg.setTimeStamp(t*ticks_multiplier);
                mtracks[channel]->addEvent(msg);
            }
        }else if(action == "Tempo"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                DBG("Tempo event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            uint32 tempovalue = 60000000 / value;
            msg = MidiMessage::tempoMetaEvent(tempovalue);
            msg.setTimeStamp(t*ticks_multiplier);
            mastertrack.addEvent(msg);
        }else if(action == "Chn Reset"){
            //TODO actually reset some CCs?
        }else if(action == "Chn Priority"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                DBG("Chn Priority event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            int cc = 25;
            if(chnpriority == "CC17 (GPC2)"){
                cc = 17;
            }else if(chnpriority == "CC25 (None)"){
                cc = 25;
            }else if(chnpriority == "CC79 (SC10)"){
                cc = 79;
            }else{
                DBG("Channel Priority event, unknown mapping: " + chnpriority + ", ignoring");
                continue;
            }
            msg = MidiMessage::controllerEvent(channel+1, cc, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Volume"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                DBG("Chn Volume event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            int cc = 7;
            if(chnvol == "CC7 (Volume)"){
                cc = 7;
            }else if(chnvol == "CC11 (Expr)"){
                cc = 11;
            }else{
                DBG("Channel Volume event, unknown mapping: " + chnvol + ", ignoring");
                continue;
            }
            msg = MidiMessage::controllerEvent(channel+1, cc, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Pan"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                DBG("Chn Pan event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            msg = MidiMessage::controllerEvent(channel+1, 10, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Effects"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                DBG("Chn Effects event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            msg = MidiMessage::controllerEvent(channel+1, 91, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Vibrato"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                DBG("Chn Vibrato event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            msg = MidiMessage::controllerEvent(channel+1, 77, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Pitch Bend"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                DBG("Chn Pitch Bend event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            if(value >= 0x80) value -= 0x100;
            value = (1<<13) + (value << 7);
            if(value < 0) value = 0;
            if(value >= (1<<14)) value = (1<<14) - 1;
            //DBG("Pitch Bend original value " + String(value) + " or " + ROM::hex((uint32)value));
            msg = MidiMessage::pitchWheel(channel+1, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Transpose"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                DBG("Chn Transpose event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            if(value >= 0x80) value -= 0x100;
            for(int i = 0; i < max_layers; i++){
                transposes.set((channel*max_layers)+i, value);
            }
        }else if(action == "Layer Transpose"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                DBG("Layer Transpose event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            if(value >= 0x80) value -= 0x100;
            transposes.set((channel*max_layers)+notelayer, value);
        }else if(action == "Chn Instrument"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                DBG("Chn Instrument event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            //DBG("Chn Instrument " + String(value) + " channel " + String(channel));
            msg = MidiMessage::programChange(channel+1, value); //TODO original instrument number
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Track Note"){
            qDelay = qVelocity = qGate = false;
            //Delay already taken care of
            //Note
            param = command.getChildWithProperty(idMeaning, "Note");
            if(!param.isValid()){
                DBG("Track Note event with no note!");
                continue;
            }
            value = getAdjustedValue(param);
            transpose = transposes[(channel*max_layers)+notelayer];
            note = value + transpose + midi_basenote;
            if(note < 0 || note >= 128){
                DBG("Bad (transposed?) note @" + ROM::hex(a, 4)
                        + ": c " + String(channel) + ", l " + String(notelayer)
                        + ": note " + String(value)
                        + ", transpose " + String(transpose)
                        + ", base " + String(midi_basenote)
                        + ": result " + String(note));
                continue;
            }
            //Velocity
            param = command.getChildWithProperty(idMeaning, "Velocity");
            if(param.isValid()){
                velocity = getAdjustedValue(param);
                qVelocity = true;
			}else{
				velocity = 0x7F;
			}
            //Gate time
            param = command.getChildWithProperty(idMeaning, "Gate Time");
            if(param.isValid()){
                gate = getAdjustedValue(param);
                qGate = true;
            }else{
                gate = 0;
            }
            //Fetch delay to get gate time proportion
            param = command.getChildWithProperty(idMeaning, "Delay");
            if(param.isValid()){
                delay = getAdjustedValue(param);
                qDelay = true;
            }else{
                //DBG("@" + ROM::hex(a, 6) + ": No delay value given, using current " + ROM::hex((uint32)delay, 4));
                //Add it so we actually do the delay!
                param = ValueTree("parameter");
                param.setProperty(idMeaning, "Delay", nullptr);
                param.setProperty(idValue, delay, nullptr);
                command.addChild(param, command.getNumChildren(), nullptr);
            }
            /*
            DBG("@" + ROM::hex(a, 4) + " c " + ROM::hex((uint8)channel, 1) + " l " + ROM::hex((uint8)notelayer, 1)
                    + " n " + ROM::hex((uint8)note)       + " v " +  ROM::hex((uint8)velocity) 
                    + " g " +  ROM::hex((uint32)gate, 4)  + " d " + ROM::hex((uint32)delay, 4)
                    + " r " + String((float)((gate*delay) / 256.0))
                    + (qDelay ? ("") : (" (using old delay)"))
                    + (qGate ? ("") : (" (no gate)"))
                    + (qVelocity ? ("") : (" (using old velocity)"))  );
            */
            msg = MidiMessage::noteOn(channel+1, note, (uint8)velocity);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
            msg = MidiMessage::noteOff(channel+1, note, 0);
            msg.setTimeStamp((t + delay - ((gate*delay) >> 8))*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else{
            DBG("Unknown command action " + action + "!");
        }
        //Execute delay
        param = command.getChildWithProperty(idMeaning, "Delay");
        if(param.isValid()){
            delay = getAdjustedValue(param);
            t += delay;
        }
    }
    if(!ended_naturally){
        DBG("Converting sequence ran off end! a==" + ROM::hex(a) + ", length==" + ROM::hex((uint32)data.size()));
    }
    DBG("====== DONE ======");
    ret->addTrack(mastertrack);
    for(channel=0; channel<16; channel++){
        mtracks[channel]->updateMatchedPairs();
        ret->addTrack(*mtracks[channel]);
    }
    return ret;
}


void SeqFile::fromMidiFile(MidiFile& mfile){
    DBG("IMPORTING MIDI FILE");
    String chnvol = midiopts.getProperty("chnvol", "CC7 (Volume)").toString();
    String mtrvol = midiopts.getProperty("mtrvol", "CC24 (None)").toString();
    String chnpriority = midiopts.getProperty("chnpriority", "CC25 (None)").toString();
    const int midi_basenote = 21;
    bool useRelative = false; //TODO support relative, optimize each
    MidiMessage msg;
    MidiMessage* msgptr;
    int channel, track, layer, m, i;
    int timestamp;
    //Reorganize
    DBG("Reorganizing MIDI file into master track and tracks for each channel...");
    int master_ppqn = mfile.getTimeFormat();
    if(master_ppqn <= 0){
        DBG("MIDI files with SMPTE time format are not supported, only PPQN format!");
        return;
    }else{
        DBG("Converting " + String(master_ppqn) + " to 48 ppqn");
    }
    double ticks_multiplier = 48.0 / (double)master_ppqn;
    double last_timestamp = mfile.getLastTimestamp();
    //Put all events into master track
    MidiMessageSequence mastertrack;
    for(track=0; track<mfile.getNumTracks(); track++){
        mastertrack.addSequence(*mfile.getTrack(track), 0, 0, last_timestamp);
        mastertrack.updateMatchedPairs();
    }
    //Scale all events to N64 PPQN
    for(m=mastertrack.getNumEvents()-1; m>=0; m--){
        msgptr = &mastertrack.getEventPointer(m)->message;
        msgptr->setTimeStamp(msgptr->getTimeStamp() * ticks_multiplier);
    }
    mastertrack.sort();
    //Get new last timestamp
    last_timestamp *= ticks_multiplier;
    int last_timestamp64 = (int)(last_timestamp);
    DBG("Last timestamp t" + String(last_timestamp64) + ", i.e. " + String(last_timestamp64 / 48)
            + " beats or " + String(last_timestamp64 / 192) + " measures 4/4");
    //Put channel events into chantracks
    OwnedArray<MidiMessageSequence> chantracks;
    for(channel=0; channel<16; channel++){
        chantracks.add(new MidiMessageSequence());
        mastertrack.extractMidiChannelMessages(channel+1, *chantracks[channel], false);
        mastertrack.deleteMidiChannelMessages(channel+1);
        mastertrack.updateMatchedPairs();
        chantracks[channel]->updateMatchedPairs();
    }
    //Find sections
    DBG("Finding sections...");
    Array<int> sectiontimes;
    sectiontimes.add(0);
    String metatext; 
    int metatype;
    for(m=0; m<mastertrack.getNumEvents(); m++){
        msg = mastertrack.getEventPointer(m)->message;
        if(msg.isTextMetaEvent()){
            metatext = msg.getTextFromTextMetaEvent();
            metatype = msg.getMetaEventType();
            if(metatype == 0x06 && (metatext.startsWithIgnoreCase("Section") ||
                    metatext.startsWithIgnoreCase("loop"))){
                timestamp = msg.getTimeStamp();
                for(i=0; i<sectiontimes.size(); i++){
                    if(sectiontimes[i] == timestamp){
                        timestamp = -1;
                        break;
                    }
                }
                if(timestamp > 0){
                    sectiontimes.add(msg.getTimeStamp());
                }
            }
        }
    }
    if(sectiontimes.size() <= 1){
        DBG("MIDI file had no sections specified. (If you meant to do this, no problem.)");
        DBG("Use Marker meta events (text event type 6) with text 'Section <n>' (no quotes)");
        DBG("in your master track to define sections.");
    }
    //See if there are any empty channels (i.e. with no note ons)
    DBG("Checking for empty channels...");
    Array<int> channelsused;
    uint16 chanBitfield = 0;
    for(channel=0; channel<16; channel++){
        channelsused.add(-1);
        for(m=0; m<chantracks[channel]->getNumEvents(); m++){
            msg = chantracks[channel]->getEventPointer(m)->message;
            if(msg.isNoteOn()){
                channelsused.set(channel, channel);
                break;
            }
        }
        chanBitfield >>= 1;
        if(channelsused[channel] < 0){
            DBG("Channel " + String(channel) + " not used");
        }else{
            chanBitfield |= 0x8000;
        }
    }
    //Figure out notelayers
    MidiMessageSequence* trk;
    MidiMessageSequence* layertrk;
    DBG("Assigning notes to notelayers...");
    int max_layers = 4;
    OwnedArray<MidiMessageSequence> layertracks;
    for(channel=0; channel<16; channel++){
        for(layer=0; layer<max_layers; layer++){
            layertracks.add(new MidiMessageSequence());
        }
    }
    int other_channel = -1;
    bool too_many_notes;
    Array<int> layerstates;
    for(layer=0; layer<max_layers; layer++){
        layerstates.add(-1);
    }
    for(channel=0; channel<16; channel++){
        trk = chantracks[channel];
        if(channelsused[channel] < 0) continue;
        //Clear initial state
        for(layer=0; layer<max_layers; layer++){
            layerstates.set(layer, -1);
        }
        too_many_notes = false;
        //Assign each note on/off pair to note layer
        for(m=0; m<trk->getNumEvents(); m++){
            msg = trk->getEventPointer(m)->message;
            if(msg.isNoteOn()){
                //Check for duplicate
                for(layer=0; layer<max_layers; layer++){
                    if(layerstates[layer] == msg.getNoteNumber()){
                        DBG("Duplicate note on in chan " + String(channel) + ", ignoring");
                        layer = -2;
                        break;
                    }
                }
                if(layer < 0) continue;
                //Check for empty spot
                for(layer=0; layer<max_layers; layer++){
                    if(layerstates[layer] < 0){
                        layertracks[(max_layers*channel)+layer]->addEvent(msg);
                        layerstates.set(layer, msg.getNoteNumber());
                        layer = -2;
                        break;
                    }
                }
                if(layer < 0) continue;
                if(!too_many_notes){
                    DBG("Channel " + String(channel) + " has more than " + String(max_layers) + " notes on at a time!");
                    DBG("Putting the extra notes on an unused channel is not yet supported.");
                    too_many_notes = true;
                }
            }else if(msg.isNoteOff()){
                //Check for existing note
                for(layer=0; layer<max_layers; layer++){
                    if(layerstates[layer] == msg.getNoteNumber()){
                        layertracks[(max_layers*channel)+layer]->addEvent(msg);
                        layerstates.set(layer, -1);
                        layer = -2;
                        break;
                    }
                }
                if(layer < 0) continue;
                if(!too_many_notes){
                    DBG("Note off received for note that is not on!");
                    too_many_notes = true;
                }
            }
        }
        //Check final state
        for(layer=0; layer<max_layers; layer++){
            if(layerstates[layer] >= 0){
                DBG("Chan " + String(channel) + " layer " + String(layer) + " left hanging! Fixing...");
                msg = MidiMessage::noteOff(channel+1, layerstates[layer]);
                msg.setTimeStamp(last_timestamp64);
                layertracks[(max_layers*channel)+layer]->addEvent(msg);
            }
        }
        //Update matched pairs
        for(layer=0; layer<max_layers; layer++){
            layertrk = layertracks[(max_layers*channel)+layer];
            layertrk->updateMatchedPairs();
            if(layertrk->getNumEvents() & 1){
                DBG("Chan " + String(channel) + " lyr " + String(layer) + " track has " 
                        + String(layertrk->getNumEvents()) + " events!");
            }
        }
    }
    //Generate Audioseq data
    data.clearQuick();
    sections.clear();
    structure = ValueTree("structure");
    ValueTree want, want2, section, newsec;
    Random::getSystemRandom().setSeedRandomly();
    //=======================================================================
    //Sequence header
    //=======================================================================
    DBG("Creating sequence header...");
    int num_tsections = sectiontimes.size();
    sectiontimes.add(last_timestamp64 + 1);
    int sectimeidx = 0;
    double newtempo;
    int tempolasttime = -100000, tempolastval = -100000;
    int t = 0;
    //Create section for header
    int sec = 0, cmd = 0, value;
    section = ValueTree("seqhdr");
    section.setProperty(idSType, 0, nullptr);
    structure.addChild(section, -1, nullptr);
    //End of Data
    want = wantAction("End of Data", 0);
    section.addChild(createCommand(want), 0, nullptr);
    //Sequence Format (D3 20)
    if((bool)midiopts.getProperty("writeseqformat", false)){
        value = (int)midiopts.getProperty("formatbytedefault", 0x20);
        want = wantAction("Sequence Format", 0);
        wantProperty(want, "Value", value);
        section.addChild(createCommand(want), cmd, nullptr);
        cmd++;
    }
    //Sequence Type (D5 32)
    if((bool)midiopts.getProperty("writeseqtype", false)){
        value = (int)midiopts.getProperty("typebytedefault", 0x32);
        want = wantAction("Sequence Type", 0);
        wantProperty(want, "Value", value);
        section.addChild(createCommand(want), cmd, nullptr);
        cmd++;
    }
    //Jump commands: TODO
    //Channel Enable (D7 XXXX)
    if((bool)midiopts.getProperty("writechanbits", false)){
        want = wantAction("Channel Enable", 0);
        wantProperty(want, "Bitfield", chanBitfield);
        section.addChild(createCommand(want), cmd, nullptr);
        cmd++;
    }
    //Beginning of track (for pointer later)
    want = createMarker();
    int ptrBeginData = want.getProperty(idHash);
    section.addChild(want, cmd, nullptr);
    cmd++;
    m=0;
    bool done = false;
    while(true){
        if(m >= mastertrack.getNumEvents()){
            done = true;
        }else{
            msg = mastertrack.getEventPointer(m)->message;
            timestamp = msg.getTimeStamp();
        }
        for(; (!done && (timestamp >= sectiontimes[sectimeidx])) 
              || (done && (sectimeidx < num_tsections)); sectimeidx++){
            DBG("Section " + String(sectimeidx) + " starting at " + String(sectiontimes[sectimeidx]));
            //Get up to the time
            if(t < sectiontimes[sectimeidx]){
                want = wantAction("Timestamp", 0);
                wantProperty(want, "Delay", sectiontimes[sectimeidx] - t);
                section.addChild(createCommand(want), cmd, nullptr);
                cmd++;
                t = sectiontimes[sectimeidx];
            }
            //Channel pointers for new section
            for(channel=0; channel<16; channel++){
                if(channelsused[channel] < 0) continue;
                //Create section for channel
                newsec = ValueTree("chanhdr");
                newsec.setProperty(idSType, 1, nullptr);
                newsec.setProperty(idChannel, channel, nullptr);
                newsec.setProperty(idTSection, sectimeidx, nullptr);
                structure.addChild(newsec, -1, nullptr);
                //Add End of Data command to channel
                want = wantAction("End of Data", 1);
                newsec.addChild(createCommand(want), -1, nullptr);
                //Add Ptr Channel Header to seq hdr
                want = wantAction("Ptr Channel Header", 0);
                wantProperty(want, "Channel", channel);
                wantProperty(want, "Absolute Address", 0);
                want = createCommand(want);
                want.setProperty(idTargetSection, structure.getNumChildren() - 1, nullptr);
                section.addChild(want, cmd, nullptr);
                cmd++;
            }
        }
        if(done) break;
        //Determine command to execute
        want = ValueTree(); //Invalidate
        if(msg.isTempoMetaEvent()){
            newtempo = msg.getTempoSecondsPerQuarterNote();
            newtempo = 60 / newtempo;
            if((int)newtempo != tempolastval && timestamp != tempolasttime){
                tempolastval = (int)newtempo;
                tempolasttime = timestamp;
                want = wantAction("Tempo", 0);
                wantProperty(want, "Value", (int)newtempo);
            }
        }else if(msg.isSysEx()){
            //TODO master volume
        }
        if(want.isValid()){
            if(t < timestamp){
                want2 = wantAction("Timestamp", 0);
                wantProperty(want2, "Delay", timestamp - t);
                section.addChild(createCommand(want2), cmd, nullptr);
                cmd++;
                t = timestamp;
            }
            //Write command
            section.addChild(createCommand(want), cmd, nullptr);
            cmd++;
        }
        //Done
        m++;
    }
    //Get the time to the end
    if(t < last_timestamp64){
        want = wantAction("Timestamp", 0);
        wantProperty(want, "Delay", last_timestamp64 - t);
        section.addChild(createCommand(want), cmd, nullptr);
        cmd++;
    }
    //Loop to start
    if((bool)midiopts.getProperty("writeloopall", false)){
        want = wantAction("Jump Same Level", 0);
        wantProperty(want, "Absolute Address", 1337);
        want = createCommand(want);
        want.setProperty(idTargetSection, 0, nullptr);
        want.setProperty(idTargetHash, ptrBeginData, nullptr);
        section.addChild(want, cmd, nullptr);
        cmd++;
    }
    //Channel Disable (D6 XXXX)
    if((bool)midiopts.getProperty("writechanbits", false)){
        want = wantAction("Channel Disable", 0);
        wantProperty(want, "Bitfield", chanBitfield);
        section.addChild(createCommand(want), cmd, nullptr);
        cmd++;
    }
    //=======================================================================
    //Channels
    //=======================================================================
    DBG("Creating channel headers...");
    int starttime, endtime;
    int cc;
    //CC Bandwidth Reduction setup
    OwnedArray<CCTracker> ccstates;
    int qt, qa;
    qt = midiopts.getProperty("q_other_time", 1);
    qa = midiopts.getProperty("q_other_amp", 1);
    for(cc=0; cc<130; cc++){ //128 is pitch, 129 is program
        ccstates.add(new CCTracker());
        ccstates[cc]->q_time = qt;
        ccstates[cc]->q_amp = qa;
    }
    ccstates[128]->q_time = midiopts.getProperty("q_pitch_time", 1);
    ccstates[128]->q_amp = midiopts.getProperty("q_pitch_amp", 1);
    qt = midiopts.getProperty("q_vol_time", 3);
    qa = midiopts.getProperty("q_vol_amp", 2);
    ccstates[7]->q_time = qt;
    ccstates[7]->q_amp = qa;
    ccstates[11]->q_time = qt;
    ccstates[11]->q_amp = qa;
    qt = midiopts.getProperty("q_pan_time", 3);
    qa = midiopts.getProperty("q_pan_amp", 2);
    ccstates[10]->q_time = qt;
    ccstates[10]->q_amp = qa;
    ccstates[91]->q_time = qt;
    ccstates[91]->q_amp = qa;
    //CC actions setup
    if(chnpriority == "CC17 (GPC2)"){
        cc = 17;
    }else if(chnpriority == "CC79 (SC10))"){
        cc = 79;
    }else{
        cc = 25;
    }
    ccstates[cc]->action = "Chn Priority";
    if(chnvol == "CC11 (Expr)"){
        cc = 11;
    }else{
        cc = 7;
    }
    ccstates[cc]->action = "Chn Volume";
    ccstates[10]->action = "Chn Pan";
    ccstates[91]->action = "Chn Effects";
    ccstates[77]->action = "Chn Vibrato";
    ccstates[128]->action = "Chn Pitch Bend";
    ccstates[129]->action = "Chn Instrument";
    //Channel data
    for(channel=0; channel<16; channel++){
        if(channelsused[channel] < 0) continue;
        trk = chantracks[channel];
        for(sectimeidx=0; sectimeidx<num_tsections; sectimeidx++){
            starttime = sectiontimes[sectimeidx];
            endtime = sectiontimes[sectimeidx+1];
            DBG("Chn " + String(channel) + " sec " + String(sectimeidx) + " starting at t" + String(starttime));
            //Find channel header
            for(sec=0; sec<structure.getNumChildren(); sec++){
                section = structure.getChild(sec);
                if((int)section.getProperty(idSType, -1) == 1 
                        && (int)section.getProperty(idChannel, -1) == channel 
                        && (int)section.getProperty(idTSection, -1) == sectimeidx){
                    break;
                }
            }
            if(sec >= structure.getNumChildren()){
                DBG("Could not find channel header for ch " + String(channel) + ", section " + String(sectimeidx) + "!");
                break;
            }
            cmd = 0;
            //Channel Reset (C4)
            if(sectimeidx == 0 && (bool)midiopts.getProperty("writechanreset", false)){
                want = wantAction("Chn Reset", 1);
                section.addChild(createCommand(want), cmd, nullptr);
                cmd++;
            }
            //Create track headers
            for(layer=0; layer<max_layers; layer++){
                layertrk = layertracks[(max_layers*channel)+layer];
                if(layertrk->getNumEvents() == 0) continue;
                //Create SeqData for layer
                newsec = ValueTree("trackdata");
                newsec.setProperty(idSType, 2, nullptr);
                newsec.setProperty(idChannel, channel, nullptr);
                newsec.setProperty(idLayer, layer, nullptr);
                newsec.setProperty(idTSection, sectimeidx, nullptr);
                structure.addChild(newsec, -1, nullptr);
                //Add End of Data command to layer
                want = wantAction("End of Data", 2);
                newsec.addChild(createCommand(want), -1, nullptr);
                //Add Ptr Track Data command to channel
                want = wantAction("Ptr Track Data", 1);
                wantProperty(want, "Note Layer", layer);
                wantProperty(want, "Absolute Address", 0);
                want = createCommand(want);
                want.setProperty(idTargetSection, structure.getNumChildren() - 1, nullptr);
                section.addChild(want, cmd, nullptr);
                cmd++;
            }
            //Clear CC states
            for(cc=0; cc<130; cc++){ //128 is pitch, 129 is program
                ccstates[cc]->lasttime = -10000000;
                ccstates[cc]->lastvalue = -10000000;
            }
            //Parse all commands
            t = starttime;
            for(m=0; m<trk->getNumEvents(); m++){
                msg = trk->getEventPointer(m)->message;
                timestamp = msg.getTimeStamp();
                if(timestamp < starttime) continue;
                if(timestamp >= endtime) continue;
                //Determine command to execute
                want = ValueTree(); //Invalidate
                cc = -1;
                if(msg.isController()){
                    cc = msg.getControllerNumber();
                    value = msg.getControllerValue();
                }else if(msg.isProgramChange()){
                    cc = 129;
                    value = msg.getProgramChangeNumber();
                }else if(msg.isPitchWheel()){
                    cc = 128;
                    value = msg.getPitchWheelValue();
                    value -= 0x2000;
                    value >>= 6;
                    value &= 0x000000FF;
                }
                if(cc < 0 || cc >= 130) continue;
                if(abs(value - ccstates[cc]->lastvalue) < ccstates[cc]->q_amp) continue;
                if(timestamp - ccstates[cc]->lasttime < ccstates[cc]->q_time) continue;
                ccstates[cc]->lastvalue = value;
                ccstates[cc]->lasttime = timestamp;
                if(ccstates[cc]->action != ""){
                    want = wantAction(ccstates[cc]->action, 1);
                    wantProperty(want, "Value", value);
                    if(t < timestamp){
                        want2 = wantAction("Timestamp", 1);
                        wantProperty(want2, "Delay", timestamp - t);
                        section.addChild(createCommand(want2), cmd, nullptr);
                        cmd++;
                        t = timestamp;
                    }
                    //Write command
                    section.addChild(createCommand(want), cmd, nullptr);
                    cmd++;
                }
            }
            //Get the time to the end
            if(t < endtime){
                want = wantAction("Timestamp", 1);
                wantProperty(want, "Delay", endtime - t);
                section.addChild(createCommand(want), cmd, nullptr);
                cmd++;
            }
        }
    }
    //=======================================================================
    //Note Layers / Tracks
    //=======================================================================
    DBG("Creating tracks...");
    MidiMessage msg2, msg3;
    int timestamp2, timestamp3;
    int note, delay, transpose;
    bool skippedDelay;
    trk = nullptr;
    for(channel=0; channel<16; channel++){
        if(channelsused[channel] < 0) continue;
        for(layer=0; layer<max_layers; layer++){
            layertrk = layertracks[(max_layers*channel)+layer];
            if(layertrk->getNumEvents() == 0) continue;
            DBG("Layer " + String(layer) + " chn " + String(channel) + " with " + String(layertrk->getNumEvents()) + " events");
            for(sectimeidx=0; sectimeidx<num_tsections; sectimeidx++){
                starttime = sectiontimes[sectimeidx];
                endtime = sectiontimes[sectimeidx+1];
                DBG("Sec " + String(sectimeidx) + " starting at t" + String(starttime));
                //Find track
                for(sec=0; sec<structure.getNumChildren(); sec++){
                    section = structure.getChild(sec);
                    if((int)section.getProperty(idSType, -1) == 2 
                            && (int)section.getProperty(idChannel, -1) == channel 
                            && (int)section.getProperty(idLayer, -1) == layer 
                            && (int)section.getProperty(idTSection, -1) == sectimeidx){
                        break;
                    }
                }
                if(sec >= structure.getNumChildren()){
                    DBG("Could not find track data for layer " + String(layer) + " ch " + String(channel) + ", section " + String(sectimeidx) + "!");
                    break;
                }
                cmd = 0;
                //Parse all commands
                t = starttime;
                m = 0;
                delay = -1;
                transpose = 0;
                //Init transpose
                want = wantAction("Layer Transpose", 2);
                wantProperty(want, "Value", transpose);
                section.addChild(createCommand(want), cmd, nullptr);
                cmd++;
                //Get first note on
                for(m=0; m<layertrk->getNumEvents(); m++){
                    msg3 = layertrk->getEventPointer(m)->message;
                    timestamp3 = msg3.getTimeStamp();
                    if(timestamp3 < starttime) continue;
                    if(timestamp3 >= endtime){
                        m = layertrk->getNumEvents() + 1;
                        break;
                    }
                    if(msg3.isNoteOn()){
                        break;
                    }
                }
                if(m >= layertrk->getNumEvents()){
                    DBG("No notes played in section " + String(sectimeidx) + "!");
                    continue;
                }
                //Seek to timestamp
                if(t < timestamp3){
                    want2 = wantAction("Timestamp", 2);
                    wantProperty(want2, "Delay", timestamp3 - t);
                    section.addChild(createCommand(want2), cmd, nullptr);
                    cmd++;
                    t = timestamp3;
                }
                bool done = false;
                while(!done){
                    msg = msg3;
                    timestamp = timestamp3;
                    //Get next thing, which should be corresponding note off
                    m++;
                    if(m >= layertrk->getNumEvents()){
                        DBG("Ran off end of track looking for note off!");
                        break;
                    }
                    msg2 = layertrk->getEventPointer(m)->message;
                    if(!msg2.isNoteOff()){
                        DBG("Note Off out of order!");
                        break;
                    }
                    timestamp2 = msg2.getTimeStamp();
                    //Get note on after that
                    m++;
                    if(m >= layertrk->getNumEvents()){
                        timestamp3 = endtime;
                        done = true;
                    }else{
                        msg3 = layertrk->getEventPointer(m)->message;
                        if(!msg3.isNoteOn()){
                            DBG("Note On out of order!");
                            break;
                        }
                        timestamp3 = msg3.getTimeStamp();
                    }
                    //Create note command
                    want = wantAction("Track Note", 2);
                    wantProperty(want, "Velocity", msg.getVelocity());
                    //Note
                    note = msg.getNoteNumber() - transpose - midi_basenote;
                    if(note < 0 || note >= 0x40){
                        if(note < 0){
                            transpose -= 12 * (((0 - note) / 12) + 1);
                        }else{
                            transpose += 12 * (((note - 0x40) / 12) + 1);
                        }
                        note = msg.getNoteNumber() - transpose - midi_basenote;
                        want2 = wantAction("Layer Transpose", 2);
                        wantProperty(want2, "Value", transpose);
                        insertCommand(sec, cmd, createCommand(want2));
                        cmd++;
                    }
                    wantProperty(want, "Note", note);
                    //Delay
                    delay = timestamp3 - timestamp;
                    wantProperty(want, "Delay", delay);
                    //Gate
                    if(delay == 0){
                        value = 0;
                    }else{
                        value = (timestamp3-timestamp2) * 0x100 / delay;
                    }
                    wantProperty(want, "Gate Time", value);
                    //Write note
                    section.addChild(createCommand(want), cmd, nullptr);
                    cmd++;
                    //Count time
                    t += delay;
                }
                //Get the time to the end
                if(t < endtime){
                    want = wantAction("Timestamp", 2);
                    wantProperty(want, "Delay", endtime - t);
                    section.addChild(createCommand(want), cmd, nullptr);
                    cmd++;
                }
            }
        }
    }
    //=======================================================================
    //Optimization
    //=======================================================================
    optimize();
    reduceTrackNotes();
    render();
    parse();
    //Done
    DBG("Done!!!");
}

bool SeqFile::isCloseEnough(ValueTree command1, ValueTree command2){
    String action = command1.getProperty(idAction, "No Action1");
    if(action != command2.getProperty(idAction, "No Action2").toString()) return false;
    ValueTree param1, param2;
    if(action == "Timestamp"){
        param1 = command1.getChildWithProperty(idMeaning, "Delay");
        param2 = command2.getChildWithProperty(idMeaning, "Delay");
        if(!param1.isValid() || !param2.isValid()) return false;
        return ((int)param1.getProperty(idValue, -1234) == (int)param2.getProperty(idValue, -8971));
    }else if(action == "Jump Same Level"){
        return false; //Don't loop jumps
    }else if(action == "Call Same Level"){
        //TODO this implementation will allow calls to arbitrary depth, not limited by stack!
        /*
        param1 = command1.getChildWithProperty(idMeaning, "Absolute Address");
        if(param1.isValid()){
            param2 = command2.getChildWithProperty(idMeaning, "Absolute Address");
        }else{
            param1 = command1.getChildWithProperty(idMeaning, "Relative Address");
            param2 = command2.getChildWithProperty(idMeaning, "Relative Address");
        }
        if(!param1.isValid() || !param2.isValid()) return false;
        return ((int)param1.getProperty(idValue, -1234) == (int)param2.getProperty(idValue, -8971));
        */
        return false; //No looping/calling calls
    }else if(action == "Loop Start"){
        return false;
        /*
        param1 = command1.getChildWithProperty(idMeaning, "Loop Count");
        param2 = command2.getChildWithProperty(idMeaning, "Loop Count");
        if(!param1.isValid() || !param2.isValid()) return false;
        return ((int)param1.getProperty(idValue, -1234) == (int)param2.getProperty(idValue, -8971));
        */
    }else if(action == "Loop End"){
        //return true;
        return false;
    }else if(action == "Track Note"){
        //Compare notes
        param1 = command1.getChildWithProperty(idMeaning, "Note");
        param2 = command2.getChildWithProperty(idMeaning, "Note");
        if(!param1.isValid() || !param2.isValid()) return false;
        if((int)param1.getProperty(idValue, -1234) != (int)param2.getProperty(idValue, -8971)) return false;
        //Compare velocities
        int delta = midiopts.getProperty("delta_vel", 5);
        param1 = command1.getChildWithProperty(idMeaning, "Velocity");
        param2 = command2.getChildWithProperty(idMeaning, "Velocity");
        if(!param1.isValid() || !param2.isValid()) return false;
        if(abs((int)param1.getProperty(idValue, -1234) 
                - (int)param2.getProperty(idValue, -8971)) > delta) return false;
        //Compare note lengths / delays
        param1 = command1.getChildWithProperty(idMeaning, "Delay");
        param2 = command2.getChildWithProperty(idMeaning, "Delay");
        if(!param1.isValid() || !param2.isValid()) return false;
        if(abs((int)param1.getProperty(idValue, -1234) 
                - (int)param2.getProperty(idValue, -8971)) > delta) return false;
        //Compare gate lengths
        int v1, v2;
        delta = midiopts.getProperty("delta_gate", 3);
        param1 = command1.getChildWithProperty(idMeaning, "Gate Time");
        param2 = command2.getChildWithProperty(idMeaning, "Gate Time");
        if(param1.isValid()){ v1 = (int)param1.getProperty(idValue, 0);
            }else{ v1 = 0; }
        if(param2.isValid()){ v2 = (int)param2.getProperty(idValue, 0);
            }else{ v2 = 0; }
        if(abs(v2 - v1) > delta) return false;
        //Finally
        return true;
    }else{
        //CCs, etc.
        int delta = midiopts.getProperty("delta_cc", 3);
        param1 = command1.getChildWithProperty(idMeaning, "Value");
        param2 = command2.getChildWithProperty(idMeaning, "Value");
        if(!param1.isValid() || !param2.isValid()) return false;
        return (abs((int)param1.getProperty(idValue, -1234) 
                - (int)param2.getProperty(idValue, -8971)) <= delta);
    }
}

void SeqFile::optimize(){
    int stacksize = midiopts.getProperty("stacksize", 4);
    bool useCalls = midiopts.getProperty("usecalls", true);
    bool useLoops = midiopts.getProperty("useloops", true);
    if(!useCalls && !useLoops){
        DBG("No optimization selected.");
        return;
    }
    //
    int sec1, sec2;
    int stype1, stype2;
    int numcmds1, numcmds2;
    ValueTree section1, section2;
    int cmd1, cmd2, cmd3, cmd4;
    ValueTree command1, command2, command3, command4;
    String action1, action2, action3, action4;
    //
    int cmdafter;
    bool flag;
    int loopCount;
    int numCmdsDelete;
    //
    ValueTree want, want2;
    int i;
    if(useLoops){
        DBG("Looking for data to loop...");
        for(sec1=0; sec1<structure.getNumChildren(); sec1++){
            section1 = structure.getChild(sec1);
            stype1 = section1.getProperty(idSType, -1);
            numcmds1 = section1.getNumChildren();
            DBG("Examining section " + String(sec1) + " (stype == " + String(stype1) + "), " + String(numcmds1) + " commands");
            //Pick a command
            for(cmd1=0; cmd1<numcmds1-1; cmd1++){
                command1 = section1.getChild(cmd1);
                action1 = command1.getProperty(idAction, "No Action");
                //DBG("----Command " + String(cmd1) + "(" + action1 + ")");
                //Don't loop pointers or no actions
                if(action1 == "No Action" || action1 == "End of Data" || action1 == "Jump Same Level"
                        || action1 == "Ptr Channel Header" || action1 == "Ptr Track Data"){
                    continue;
                }
                //See if this command repeats later in the track, for loops
                //Start 2 commands later (don't loop one command)
                for(cmd2=cmd1+2; cmd2<numcmds1-1; cmd2++){
                    command2 = section1.getChild(cmd2);
                    if(isCloseEnough(command1, command2)){
                        //See if everything is the same in between
                        flag = true;
                        cmd3 = cmd1+1;
                        cmd4 = cmd2+1;
                        while(cmd3 < cmd2){
                            if(cmd4 >= numcmds1){
                                flag = false;
                                break;
                            }
                            if(!isCloseEnough(section1.getChild(cmd3), section1.getChild(cmd4))){
                                flag = false;
                                break;
                            }
                            cmd3++;
                            cmd4++;
                        }
                        if(!flag) continue;
                        //We have a loop!
                        DBG("Sec " + String(sec1) + ": found loopable data from cmds " + String(cmd1) + " to " + String(cmd2));
                        //See if it's repeated some more afterwards
                        loopCount = 2;
                        cmd3 = cmd1;
                        cmdafter = cmd4;
                        while(cmd4 < numcmds1){
                            if(cmd3 == cmd2){
                                loopCount++;
                                cmd3 = cmd1;
                                cmdafter = cmd4;
                            }
                            if(!isCloseEnough(section1.getChild(cmd3), section1.getChild(cmd4))){
                                break;
                            }
                            cmd3++;
                            cmd4++;
                        }
                        //How much data to delete?
                        numCmdsDelete = cmdafter - cmd2;
                        DBG("Loop repeats " + String(loopCount) + " times; deleting " 
                                + String(numCmdsDelete) + " commands");
                        for(i=0; i<numCmdsDelete; i++){
                            section1.removeChild(cmd2, nullptr);
                        }
                        //Put in Loop Start command
                        want = wantAction("Loop Start", stype1);
                        wantProperty(want, "Loop Count", loopCount);
                        section1.addChild(createCommand(want), cmd1, nullptr);
                        cmd2++; //This increments the position of cmd2!
                        //Put in Loop End command
                        want = wantAction("Loop End", stype1);
                        section1.addChild(createCommand(want), cmd2, nullptr);
                        //Move to end of loop to keep parsing
                        cmd1 = cmd2;
                        break;
                    }
                }
            }
        }
    }
    if(useCalls){
        DBG("Looking for hooks...");
        ValueTree list("list");
        ValueTree item;
        ValueTree sectionN;
        int secN;
        int i, j;
        int hooklength, drops;
        for(sec1=0; sec1<structure.getNumChildren(); sec1++){
            section1 = structure.getChild(sec1);
            stype1 = section1.getProperty(idSType, -1);
            numcmds1 = section1.getNumChildren();
            DBG("Examining section " + String(sec1) + " (stype == " + String(stype1) + "), " + String(numcmds1) + " commands");
            //Pick a command
            for(cmd1=0; cmd1<numcmds1-1; cmd1++){
                command1 = section1.getChild(cmd1);
                action1 = command1.getProperty(idAction, "No Action");
                //DBG("----Command " + String(cmd1) + "(" + action1 + ")");
                if(action1 == "No Action" || action1 == "End of Data" || action1 == "Jump Same Level"
                        || action1 == "Ptr Channel Header" || action1 == "Ptr Track Data"){
                    continue;
                }
                //Consider next command too, there's no point in calling a section for 1 command
                command3 = section1.getChild(cmd1+1);
                action3 = command3.getProperty(idAction, "No Action");
                if(action3 == "No Action" || action3 == "End of Data" || action3 == "Jump Same Level"
                        || action3 == "Ptr Channel Header" || action3 == "Ptr Track Data"){
                    continue;
                }
                //Find all the places, in any section of the same stype, where this string of two commands appears
                list.removeAllChildren(nullptr);
                for(sec2=sec1; sec2<structure.getNumChildren(); sec2++){
                    section2 = structure.getChild(sec2);
                    stype2 = section2.getProperty(idSType, -1);
                    numcmds2 = section2.getNumChildren();
                    if(stype2 != stype1) continue;
                    for(cmd2 = (sec2 == sec1 ? cmd1 + 2 : 0); cmd2<numcmds2-1; cmd2++){
                        command2 = section2.getChild(cmd2);
                        action2 = command2.getProperty(idAction, "No Action");
                        if(action2 != action1) continue;
                        command4 = section2.getChild(cmd2+1);
                        action4 = command4.getProperty(idAction, "No Action");
                        if(action4 != action3) continue;
                        if(!isCloseEnough(command1, command2)) continue;
                        if(!isCloseEnough(command3, command4)) continue;
                        item = ValueTree("item");
                        item.setProperty(idSection, sec2, nullptr);
                        item.setProperty(idCmd, cmd2, nullptr);
                        list.addChild(item, -1, nullptr);
                    }
                }
                //Found anything?
                if(list.getNumChildren() == 0) continue;
                DBG("Got hook, found elsewhere " + String(list.getNumChildren()) + " times");
                //Grow the hook until items start dropping too much
                for(hooklength = 2; ; hooklength++){
                    drops = 0;
                    //Move cmd3 to the next one in the first section
                    cmd3 = cmd1 + hooklength;
                    if(cmd3 >= numcmds1){
                        break;
                    }
                    command3 = section1.getChild(cmd3);
                    action3 = command3.getProperty(idAction);
                    if(action3 == "No Action" || action3 == "End of Data" || action3 == "Jump Same Level"
                            || action3 == "Ptr Channel Header" || action3 == "Ptr Track Data"){
                        break;
                    }
                    //See if we can move all the others
                    for(i=0; i<list.getNumChildren(); i++){
                        item = list.getChild(i);
                        sec2 = item.getProperty(idSection);
                        cmd2 = item.getProperty(idCmd);
                        section2 = structure.getChild(sec2);
                        numcmds2 = section2.getNumChildren();
                        cmd4 = cmd2 + hooklength;
                        if(cmd4 < numcmds2){
                            //Make sure it's not overlapping with any other!
                            flag = false;
                            for(j=i; j<list.getNumChildren(); j++){
                                if((int)list.getChild(j).getProperty(idSection) == sec2 
                                        && cmd4 >= (int)list.getChild(j).getProperty(idCmd)){
                                    flag = true;
                                    break;
                                }
                            }
                            if(!flag){
                                command4 = section2.getChild(cmd4);
                                action4 = command4.getProperty(idAction);
                                if(action4 == action3){
                                    if(isCloseEnough(command3, command4)){
                                        continue;
                                    }
                                }
                            }
                        }
                        drops++;
                        item.setProperty(idWillDrop, true, nullptr);
                    }
                    //If the number of commands lost by continuing
                    //is greater than the number of commands gained by continuing
                    if((drops * hooklength) > (list.getNumChildren() - drops)){
                        //Stop
                        break;
                    }
                    //Drop all to be dropped
                    for(i=0; i<list.getNumChildren(); i++){
                        item = list.getChild(i);
                        if(item.hasProperty(idWillDrop)){
                            list.removeChild(i, nullptr);
                            i--;
                        }
                    }
                }
                DBG("Grew hook to " + String(hooklength) + ", now used " + String(list.getNumChildren()) + " times");
                //Create new section 
                secN = structure.getNumChildren();
                sectionN = ValueTree(section1.getType());
                sectionN.setProperty(idSType, stype1, nullptr);
                structure.addChild(sectionN, secN, nullptr);
                //Copy all data to new section
                for(i=0; i<hooklength; i++){
                    sectionN.addChild(section1.getChild(cmd1+i).createCopy(), -1, nullptr);
                }
                //Add End of Data command to new section
                want = wantAction("End of Data", stype1);
                sectionN.addChild(createCommand(want), -1, nullptr);
                //Replace all instances of data with pointer to new section
                want = wantAction("Call Same Level", stype1);
                wantProperty(want, "Absolute Address", 1337);
                want = createCommand(want);
                want.setProperty(idTargetSection, secN, nullptr);
                for(i=list.getNumChildren() - 1; i>=0; i--){ //Go in reverse order so the cmd numbers are never changed
                    item = list.getChild(i);
                    sec2 = item.getProperty(idSection);
                    cmd2 = item.getProperty(idCmd);
                    section2 = structure.getChild(sec2);
                    for(cmd4=0; cmd4<hooklength; cmd4++){
                        section2.removeChild(cmd2, nullptr);
                    }
                    section2.addChild(want.createCopy(), cmd2, nullptr);
                }
                //Replace current instance
                for(cmd3=0; cmd3<hooklength; cmd3++){
                    section1.removeChild(cmd1, nullptr);
                }
                section1.addChild(want.createCopy(), cmd1, nullptr);
            }
        }
        //Replace all 2-loops of 1-calls, 2-loops of 2-calls, or 3-loops of 1-calls with individual calls
        DBG("Fixing short-looped calls...");
        for(sec1=0; sec1<structure.getNumChildren(); sec1++){
            section1 = structure.getChild(sec1);
            stype1 = section1.getProperty(idSType, -1);
            numcmds1 = section1.getNumChildren();
            for(cmd1=0; cmd1<numcmds1-3; cmd1++){
                command1 = section1.getChild(cmd1);
                action1 = command1.getProperty(idAction, "No Action");
                if(action1 != "Loop Start") continue;
                loopCount = command1.getChildWithProperty(idMeaning, "Loop Count").getProperty(idValue);
                if(loopCount > 3) continue;
                if(loopCount == 3){
                    command3 = section1.getChild(cmd1+2);
                    if(command3.getProperty(idAction, "No Action").toString() != "Loop End") continue;
                    command2 = section1.getChild(cmd1+1);
                    if(command2.getProperty(idAction, "No Action").toString() != "Call Same Level") continue;
                    DBG("----Converting 3-loop of 1-call to 3 calls in sec " + String(sec1) + " cmd " + String(cmd1));
                    //Remove loop start, replace with call
                    section1.removeChild(cmd1, nullptr);
                    section1.addChild(command2.createCopy(), cmd1, nullptr);
                    //Remove loop end, replace with call
                    cmd1 += 2;
                    section1.removeChild(cmd1, nullptr);
                    section1.addChild(command2.createCopy(), cmd1, nullptr);
                }else if(loopCount == 2){
                    command2 = section1.getChild(cmd1+1);
                    if(command2.getProperty(idAction, "No Action").toString() != "Call Same Level") continue;
                    command3 = section1.getChild(cmd1+2);
                    command4 = section1.getChild(cmd1+3);
                    if(command3.getProperty(idAction, "No Action").toString() == "Loop End"){
                        DBG("----Converting 2-loop of 1-call to 2 calls in sec " + String(sec1) + " cmd " + String(cmd1));
                        //Remove loop start, replace with call
                        section1.removeChild(cmd1, nullptr);
                        section1.addChild(command2.createCopy(), cmd1, nullptr);
                        //Remove loop end
                        cmd1 += 2;
                        section1.removeChild(cmd1, nullptr);
                        cmd1--; //Go back so we hit the next command
                    }else if(command4.getProperty(idAction, "No Action").toString() == "Loop End"){
                        if(command3.getProperty(idAction, "No Action").toString() != "Call Same Level") continue;
                        DBG("----Converting 2-loop of 2-calls to 4 calls in sec " + String(sec1) + " cmd " + String(cmd1));
                        //Remove loop start
                        section1.removeChild(cmd1, nullptr);
                        //Remove loop end
                        cmd1 += 2;
                        section1.removeChild(cmd1, nullptr);
                        //Add two calls
                        section1.addChild(command2.createCopy(), cmd1, nullptr);
                        cmd1++;
                        section1.addChild(command3.createCopy(), cmd1, nullptr);
                    }
                }
            }
        }
    }
}

void SeqFile::reduceTrackNotes(){
    DBG("Reducing track notes to shortest types...");
    int sec, lastdelay, delay, gate, value, cmd;
    ValueTree section;
    ValueTree command, newcommand, paramd, paramg;
    String action;
    //Reduce
    for(sec=0; sec<structure.getNumChildren(); sec++){
        section = structure.getChild(sec);
        if((int)section.getProperty(idSType, -1) != 2) continue;
        //DBG("--Section " + String(sec));
        lastdelay = -1234;
        for(cmd=0; cmd<section.getNumChildren(); cmd++){
            command = section.getChild(cmd);
            action = command.getProperty(idAction, "No Action");
            if(action != "Track Note") continue;
            newcommand = wantAction("Track Note", 2);
            //Note
            paramd = command.getChildWithProperty(idMeaning, "Note");
            wantProperty(newcommand, "Note", paramd.getProperty(idValue));
            //Velocity
            paramd = command.getChildWithProperty(idMeaning, "Velocity");
            wantProperty(newcommand, "Velocity", paramd.getProperty(idValue));
            //Delay and Gate
            paramd = command.getChildWithProperty(idMeaning, "Delay");
            paramg = command.getChildWithProperty(idMeaning, "Gate Time");
            if(!paramd.isValid() || !paramg.isValid()) continue;
            delay = paramd.getProperty(idValue, -8937);
            gate  = paramg.getProperty(idValue, -1237);
            if(delay != lastdelay){
                lastdelay = delay;
                if(gate != 0){
                    continue; //Don't replace the command, we didn't make a change
                }
                wantProperty(newcommand, "Delay", delay);
            }else{
                wantProperty(newcommand, "Gate Time", gate);
            }
            //Replace command
            newcommand = createCommand(newcommand);
            section.removeChild(cmd, nullptr);
            section.addChild(newcommand, cmd, nullptr);
        }
    }
}

void SeqFile::render(){
    DBG("Rendering sequence structure to binary data...");
    data.clearQuick();
    int datasize = 0x8000;
    data.ensureStorageAllocated(datasize); //Should be enough
    data.insertMultiple(0, 0, datasize);
    //Find lengths and addresses of everything
    uint32 address = 0;
    int sec, cmd, len;
    ValueTree section, command;
    String action;
    for(sec=0; sec<structure.getNumChildren(); sec++){
        section = structure.getChild(sec);
        section.setProperty(idAddress, (int)address, nullptr);
        for(cmd=0; cmd<section.getNumChildren(); cmd++){
            command = section.getChild(cmd);
            command.setProperty(idAddress, (int)address, nullptr);
            len = getNewCommandLength(command);
            command.setProperty(idLength, len, nullptr);
            address += len;
        }
    }
    //Write data
    address = 0;
    int ptraddr, ptrsec, ptrhash, cmd2;
    ValueTree section2, command2, param;
    for(sec=0; sec<structure.getNumChildren(); sec++){
        //DBG("----Section " + String(sec));
        section = structure.getChild(sec);
        for(cmd=0; cmd<section.getNumChildren(); cmd++){
            command = section.getChild(cmd);
            action = command.getProperty(idAction, "No Action");
            len = command.getProperty(idLength, 1);
            //Get addresses of pointers
            if(command.hasProperty(idTargetSection)){
                ptrsec = command.getProperty(idTargetSection);
                if(ptrsec >= structure.getNumChildren()){
                    DBG("Pointer to undefined section!");
                }else{
                    section2 = structure.getChild(ptrsec);
                    if(command.hasProperty(idTargetHash)){
                        //Search for command with that hash
                        ptrhash = command.getProperty(idTargetHash);
                        ptraddr = -1;
                        for(cmd2=0; cmd2<section2.getNumChildren(); cmd2++){
                            command2 = section2.getChild(cmd2);
                            if((int)command2.getProperty(idHash) == ptrhash){
                                ptraddr = command2.getProperty(idAddress);
                                break;
                            }
                        }
                        if(ptraddr < 0){
                            DBG("Could not find command with correct hash!");
                            ptraddr = 0;
                        }
                    }else{
                        ptraddr = section2.getProperty(idAddress);
                    }
                }
                //Put in relative/absolute address
                param = command.getChildWithProperty(idMeaning, "Absolute Address");
                if(param.isValid()){
                    param.setProperty(idValue, ptraddr, nullptr);
                }else{
                    param = command.getChildWithProperty(idMeaning, "Relative Address");
                    if(param.isValid()){
                        param.setProperty(idValue, (int)(ptraddr - (address + len)), nullptr);
                    }else{
                        DBG("Command had idTargetSection but no parameters with absolute or relative address!");
                    }
                }
            }
            writeCommand(address, command);
            address += len;
            //Enlarge data if necessary
            if(address >= (datasize - 0x100)){
                data.ensureStorageAllocated(datasize * 2);
                data.insertMultiple(datasize, 0, datasize);
                datasize *= 2;
            }
        }
    }
    //Shrink data
    data.removeRange(address, data.size() - address);
}


