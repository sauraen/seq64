/*
 * ============================================================================
 *
 * SeqFile.cpp
 * Class to hold/import/export a Nintendo Music Macro Language (Audioseq) 
 * format sequence file
 * 
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2020 Sauraen
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

#include "SeqFile.hpp"

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

//TODO reladdr

//TODO
SeqFile::SeqFile(ValueTree abi_) : abi(abi_){
    //data.clearQuick();
    //data.ensureStorageAllocated(0x8000); //Should be enough
}

//TODO
SeqFile::~SeqFile(){
    
}

String SeqFile::getInternalString(){
    if(structure.isValid()){
        XmlElement::TextFormat fmt;
        fmt.addDefaultHeader = false;
        fmt.lineWrapLength = 80;
        return structure.toXmlString(fmt);
    }
    return "(No sequence loaded)";
}

StringArray SeqFile::getAvailABIs(){
    StringArray ret;
    File abifolder = findFile("abi/");
    if(!abifolder.isDirectory()){
        ret.add("Could not find abi folder!");
        return ret;
    }
    Array<File> xmlfiles = abifolder.findChildFiles(File::findFiles, false, "*.xml");
    if(xmlfiles.size() == 0){
        ret.add("No abi XML files in abi folder!");
    }
    for(int i=0; i<xmlfiles.size(); ++i){
        ret.add(xmlfiles[i].getFileNameWithoutExtension());
    }
    return ret;
}
ValueTree SeqFile::loadABI(String name){
    File abi = findFile("abi/" + name + ".xml");
    if(!abi.existsAsFile()){
        std::cout << "Could not find file " + abi.getFullPathName() + "!";
        return ValueTree();
    }
    std::unique_ptr<XmlElement> xml = parseXML(abi);
    if(xml == nullptr){
        std::cout << "Error parsing XML of " + abi.getFullPathName() + "!";
        return ValueTree();
    }
    return ValueTree::fromXml(*xml);
}

void SeqFile::dbgmsg(String s, bool newline){
    const ScopedLock lock(debug_mutex);
    if(newline) s += "\n";
    debug_messages += s;
    std::cout << s;
}
String SeqFile::getDebugOutput(){
    const ScopedLock lock(debug_mutex);
    String ret(debug_messages);
    debug_messages.clear();
    return ret;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// importMIDI functions /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//Probably OK
MidiMessageSequence* SeqFile::ensureSimulMsgsInOrder(MidiMessageSequence &in){
    in.updateMatchedPairs();
    in.sort();
    MidiMessageSequence* out = new MidiMessageSequence();
    MidiMessage* msg;
    //In any group of commands happening at the same time, the events should be
    //in this order: Note Offs, other messages (CCs, etc.), program changes, Note Ons
    while(in.getNumEvents() > 0){
        double ts = in.getEventPointer(0)->message.getTimeStamp();
        bool addme;
        for(int phase=0; phase<=3; ++phase){
            for(int i=0; i<in.getNumEvents(); ++i){
                msg = &(in.getEventPointer(i)->message);
                if(msg->getTimeStamp() > ts) break;
                else if(msg->getTimeStamp() < ts){
                    dbgmsg("Consistency error: messages out of order after sorting!");
                    return out;
                }
                switch(phase){
                    case 0: addme = msg->isNoteOff(); break;
                    case 1: addme = (!msg->isNoteOnOrOff() && !msg->isProgramChange()); break;
                    case 2: addme = msg->isProgramChange(); break;
                    case 3: addme = true; break;
                    default: dbgmsg("Bad phase in sorting!"); return out;
                }
                if(addme){
                    out->addEvent(*msg, 0.0);
                    in.deleteEvent(i, false);
                    --i;
                }
            }
        }
    }
    return out;
}

//Probably OK
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

//Probably OK
int SeqFile::getLargestCommandRange(int stype, String action, String meaning){
    ValueTree test, param, param2;
    ValueTree possibleCmdsList("possiblecmdslist");
    bool flag;
    int i, range, maxrange = 0;
    for(i=0; i<abi.getNumChildren(); i++){
        test = abi.getChild(i);
        if(!isCommandValidIn(test, stype)) continue;
        if(test.getProperty(idAction).toString() != action) continue;
        param = test.getChildWithProperty(idMeaning, meaning);
        if(!param.isValid()) continue;
        range = getCommandRange(test, meaning);
        if(range > maxrange) maxrange = range;
    }
    return maxrange;
}

//Probably OK
bool SeqFile::isCommandValidIn(ValueTree command, int stype){
    if(!command.isValid()) return false;
    if(stype == 0){
        return command.getProperty(idValidInSeq, false);
    }else if(stype == 1){
        return command.getProperty(idValidInChn, false);
    }else if(stype == 2){
        return command.getProperty(idValidInTrk, false);
    }else{
        return false;
    }
}

//Probably OK
ValueTree SeqFile::wantAction(String action, int stype){
    ValueTree ret("wantedcmd");
    ret.setProperty(idAction, action, nullptr);
    ret.setProperty(idSType, stype, nullptr);
    return ret;
}

//Probably OK
void SeqFile::wantProperty(ValueTree want, String meaning, int value){
    ValueTree sub("wantedproperty");
    sub.setProperty(idMeaning, meaning, nullptr);
    sub.setProperty(idValue, value, nullptr);
    want.addChild(sub, -1, nullptr);
}

//Probably OK
ValueTree SeqFile::createCommand(ValueTree want, bool warnIfImpossible){
    if(!want.isValid()) return want;
    int stype = want.getProperty(idSType);
    String action = want.getProperty(idAction);
    String meaning;
    ValueTree test, param, param2;
    ValueTree possibleCmdsList("possiblecmdslist");
    bool flag;
    int i, j, range, value;
    for(i=0; i<abi.getNumChildren(); i++){
        test = abi.getChild(i);
        if(!isCommandValidIn(test, stype)) continue;
        if(test.getProperty(idAction).toString() != action) continue;
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
                //dbgmsg("--Looking for " + action + " command, meaning " + meaning 
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
    if(possibleCmdsList.getNumChildren() == 0){
        if(warnIfImpossible){
            dbgmsg("No " + action + " command defined in stype " + String(stype) + " with all the needed parameters!");
            for(j=0; j<want.getNumChildren(); j++){
                dbgmsg("----Want: " + want.getChild(j).getProperty(idMeaning).toString()
                        + " value " + want.getChild(j).getProperty(idValue).toString());
            }
        }
        return ValueTree();
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

//Probably OK
void SeqFile::advanceToTimestamp(ValueTree section, int stype, int &cmd, int &t, int newt){
    int maxdelay = getLargestCommandRange(stype, "Timestamp", "Delay") - 1;
    while(t < newt){
        int dt = std::min(newt - t, maxdelay);
    	ValueTree want = wantAction("Timestamp", stype);
    	wantProperty(want, "Delay", dt);
    	section.addChild(createCommand(want), cmd, nullptr);
        ++cmd;
        t += dt;
    }
}

//Probably OK
ValueTree SeqFile::createMarker(){
    ValueTree ret("marker");
    ret.setProperty(idAction, "Marker", nullptr);
    ret.setProperty(idHash, Random::getSystemRandom().nextInt(), nullptr);
    return ret;
}

//Probably OK
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

//Probably OK
bool SeqFile::isCloseEnough(ValueTree command1, ValueTree command2, bool allowCCMerge, ValueTree midiopts){
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
        //Compare note lengths / delays
        param1 = command1.getChildWithProperty(idMeaning, "Delay");
        param2 = command2.getChildWithProperty(idMeaning, "Delay");
        if(!param1.isValid() || !param2.isValid()) return false;
        if((int)param1.getProperty(idValue, -1234) != (int)param2.getProperty(idValue, -8971)) return false;
        //Compare velocities
        int delta = midiopts.getProperty("delta_vel", 5);
        param1 = command1.getChildWithProperty(idMeaning, "Velocity");
        param2 = command2.getChildWithProperty(idMeaning, "Velocity");
        if(!param1.isValid() || !param2.isValid()) return false;
        if(abs((int)param1.getProperty(idValue, -1234) 
                - (int)param2.getProperty(idValue, -8971)) > delta) return false;
        //Compare gate lengths
        int v1, v2;
        delta = midiopts.getProperty("delta_gate", 3);
        param1 = command1.getChildWithProperty(idMeaning, "Gate Time");
        param2 = command2.getChildWithProperty(idMeaning, "Gate Time");
        v1 = (param1.isValid()) ? ((int)param1.getProperty(idValue, 0)) : 0;
        v2 = (param2.isValid()) ? ((int)param2.getProperty(idValue, 0)) : 0;
        if(abs(v2 - v1) > delta) return false;
        //Finally
        return true;
    }else{
        //CCs, etc.
        int delta;
        if(action == "Chn Volume" || action == "Chn Pan" || action == "Chn Effects" || action == "Chn Pitch Bend"){
            delta = midiopts.getProperty("delta_cc", 3);
        }else{
            delta = 0;
        }
        if(!allowCCMerge) delta = 0;
        param1 = command1.getChildWithProperty(idMeaning, "Value");
        param2 = command2.getChildWithProperty(idMeaning, "Value");
        if(!param1.isValid() || !param2.isValid()) return false;
        return (abs((int)param1.getProperty(idValue, -1234) 
                - (int)param2.getProperty(idValue, -8971)) <= delta);
    }
}

//Probably OK
int SeqFile::getTotalSectionTime(ValueTree section){
    int totaltime = 0, t, loopmult = 1;
    for(int cmd=0; cmd<section.getNumChildren(); ++cmd){
        ValueTree command = section.getChild(cmd);
        String action = command.getProperty(idAction, "No Action");
        t = 0;
        if(action == "Call Same Level"){
            int s = command.getProperty(idTargetSection, -1);
            if(s < 0 || s >= structure.getNumChildren()){
                dbgmsg("getTotalSectionTime: Call Same Level to invalid target section!");
                importresult |= 2;
                continue;
            }
            t = getTotalSectionTime(structure.getChild(s));
        }else if(action == "Loop Start"){
            ValueTree param = command.getChildWithProperty(idMeaning, "Loop Count");
            if(!param.isValid()){
                loopmult = 0;
            }else{
                loopmult = param.getProperty(idValue, 0);
            }
            if(loopmult < 2){
                dbgmsg("Loop Start with count < 2!");
                importresult |= 2;
            }
        }else if(action == "Loop End"){
            loopmult = 1;
        }else if(action == "Timestamp"){
            ValueTree param = command.getChildWithProperty(idMeaning, "Delay");
            if(param.isValid()){
                t = param.getProperty(idValue, 0);
            }
            if(t == 0){
                dbgmsg("Timestamp without delay!");
                importresult |= 2;
            }
        }
        totaltime += t * loopmult;
    }
    return totaltime;
}

//Probably OK
void SeqFile::deleteSection(int sectodelete){
    ValueTree dsection = structure.getChild(sectodelete);
    /*
    dbgmsg("Deleting empty section " + String(sectodelete) 
        + " stype=" + dsection.getProperty(idSType, -1).toString()
        + " channel=" + dsection.getProperty(idChannel, -1).toString()
        + " layer=" + dsection.getProperty(idLayer, -1).toString()
        + " tsection=" + dsection.getProperty(idTSection, -1).toString());
    */
    dbgmsg("*", false);
    int s, c, t;
    ValueTree section, command;
    for(s=0; s<structure.getNumChildren(); ++s){
        section = structure.getChild(s);
        for(c=0; c<section.getNumChildren(); ++c){
            command = section.getChild(c);
            t = command.getProperty(idTargetSection, -1);
            if(t == sectodelete){
                //dbgmsg("--Removing command " + command.getProperty(idAction, "No Action").toString()
                //    + " from section " + String(s) + " stype " + section.getProperty(idSType, -1).toString());
                section.removeChild(command, nullptr);
                --c;
            }else if(t > sectodelete){
                command.setProperty(idTargetSection, t-1, nullptr);
            }
        }
    }
    structure.removeChild(sectodelete, nullptr);
}


////////////////////////////////////////////////////////////////////////////////
///////////////////////////// importMIDI objects ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//Probably OK
class LayerState{
public:
    LayerState(int historylen) : histl(historylen) { clear(); }
    ~LayerState() {}
    bool isInUse(){ return data[0] >= 0; }
    int curNote(){ return data[0]; }
    void writeNote(int newnote){
        if(data[0] < 0){
            data.set(0, newnote);
        }else{
            data.remove(data.size() - 1);
            data.insert(0, newnote);
        }
    }
    void clear(){
        data.clear();
        for(int i=0; i<histl; ++i){
            data.add(-1);
        }
    }
    float mse(int newnote){
        if(data[0] >= 0) return 10000000000.0f;
        float m = 0.0f;
        int deltasq;
        const int unusedpenalty = 40000;
        for(int i=1; i<histl; ++i){
            deltasq = (data[i] < 0) ? unusedpenalty : ((data[i] - newnote) * (data[i] - newnote));
            if(deltasq == 0) return m;
            m += (float)deltasq / (float)(i);
        }
        return m;
    }
private:
    Array<int> data;
    int histl;
};

//Probably OK
struct CCTracker{
    CCTracker(){
        action = "";
        q_time = lasttime = q_amp = lastvalue = 0;
    }
    String action;
    int q_time, lasttime, q_amp, lastvalue;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// importMIDI //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int SeqFile::importMIDI(File midifile, ValueTree midiopts){
    if(!midifile.existsAsFile()){
        dbgmsg("File " + midifile.getFullPathName() + " does not exist!");
        return -1;
    }
    FileInputStream fis(midifile);
    MidiFile mfile;
    mfile.readFrom(fis);
    name = midifile.getFileNameWithoutExtension();
    dbgmsg("IMPORTING MIDI FILE");
    importresult = 0;
    //Changing these is no longer supported--I never heard of anyone using them
    String chnvol = "CC7 (Volume)"; //midiopts.getProperty("chnvol", "CC7 (Volume)").toString();
    String mtrvol = "SysEx MstrVol"; //midiopts.getProperty("mtrvol", "CC24 (None)").toString();
    String chnpriority = "CC25 (None)"; //midiopts.getProperty("chnpriority", ).toString();
    const int midi_basenote = 21;
    MidiMessage msg;
    MidiMessage* msgptr;
    int channel, track, layer, m, i;
    int timestamp = 0;
    //Reorganize
    dbgmsg("Reorganizing MIDI file into master track and tracks for each channel...");
    int master_ppqn = mfile.getTimeFormat();
    if(master_ppqn <= 0){
        dbgmsg("MIDI files with SMPTE time format are not supported, only PPQN format!");
        importresult = 2;
        return importresult;
    }else{
        dbgmsg("Converting " + String(master_ppqn) + " to 48 ppqn");
    }
    double ticks_multiplier = 48.0 / (double)master_ppqn;
    double last_timestampd = mfile.getLastTimestamp();
    //Put all events into master track
    std::unique_ptr<MidiMessageSequence> mastertrack;
    mastertrack.reset(new MidiMessageSequence());
    for(track=0; track<mfile.getNumTracks(); track++){
        mastertrack->addSequence(*mfile.getTrack(track), 0.0, 0.0, last_timestampd + 1.0);
        mastertrack->updateMatchedPairs();
    }
    //Scale all events to N64 PPQN
    //TODO check for extremely short notes
    for(m=mastertrack->getNumEvents()-1; m>=0; m--){
        msgptr = &mastertrack->getEventPointer(m)->message;
        msgptr->setTimeStamp(msgptr->getTimeStamp() * ticks_multiplier);
    }
    //Ensure events are propertly in order
    mastertrack.reset(ensureSimulMsgsInOrder(*mastertrack));
    //Get new last timestamp
    last_timestampd *= ticks_multiplier;
    int last_timestamp = (int)(last_timestampd);
    dbgmsg("Last timestamp t" + String(last_timestamp) + ", i.e. " + String(last_timestamp / 48)
            + " beats or " + String(last_timestamp / 192) + " measures 4/4");
    //Put channel events into chantracks
    OwnedArray<MidiMessageSequence> chantracks;
    for(channel=0; channel<16; channel++){
        chantracks.add(new MidiMessageSequence());
        mastertrack->extractMidiChannelMessages(channel+1, *chantracks[channel], false);
        mastertrack->deleteMidiChannelMessages(channel+1);
        mastertrack->updateMatchedPairs();
        chantracks[channel]->updateMatchedPairs();
    }
    //Find sections
    dbgmsg("Finding sections...");
    Array<int> sectiontimes;
    sectiontimes.add(0);
    String metatext; 
    int metatype;
    for(m=0; m<mastertrack->getNumEvents(); m++){
        msg = mastertrack->getEventPointer(m)->message;
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
        dbgmsg("MIDI file had no sections specified. (If you meant to do this, no problem.)");
        dbgmsg("Use Marker meta events (text event type 6) with text 'Section <n>' (no quotes)");
        dbgmsg("in your master track to define sections.");
    }
    //See if there are any empty channels (i.e. with no note ons)
    dbgmsg("Empty channels: ", false);
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
            dbgmsg(String(channel) + ", ", false);
        }else{
            chanBitfield |= 0x8000;
        }
    }
    dbgmsg("[end]");
    //Figure out notelayers
    MidiMessageSequence* trk;
    MidiMessageSequence* layertrk;
    dbgmsg("Assigning notes to notelayers...");
    int max_layers = 4; //TODO investigate
    OwnedArray<MidiMessageSequence> layertracks;
    for(channel=0; channel<16; channel++){
        for(layer=0; layer<max_layers; layer++){
            layertracks.add(new MidiMessageSequence());
        }
    }
    int other_channel = -1; //TODO put notes on another channel
    bool too_many_notes;
    OwnedArray<LayerState> ls;
    const int ls_history = 4;
    for(layer=0; layer<max_layers; layer++){
        ls.add(new LayerState(ls_history));
    }
    int sec;
    int bestlayer;
    float bestlayermse, thislayermse;
    for(channel=0; channel<16; channel++){
        trk = chantracks[channel];
        if(channelsused[channel] < 0) continue;
        too_many_notes = false;
        sec = -1;
        for(m=0; m<trk->getNumEvents(); m++){
            msg = trk->getEventPointer(m)->message;
            //See what section we're in, and clear LayerStates if it's a new section
            for(i=sec; i<sectiontimes.size()-1; ++i){
                if(sectiontimes[i+1] > msg.getTimeStamp() ||
                        (sectiontimes[i+1] == msg.getTimeStamp() && msg.isNoteOff())){
                    //We haven't moved to that section yet
                    break;
                }
            }
            if(sec != i){
                sec = i;
                //Clear layer state since we're in a new section
                for(layer=0; layer<max_layers; layer++){
                    ls[layer]->clear();
                }
            }
            //Assign each note on/off pair to note layer
            if(msg.isNoteOn()){
                //Check for duplicate
                for(layer=0; layer<max_layers; layer++){
                    if(ls[layer]->curNote() == msg.getNoteNumber()){
                        dbgmsg("Duplicate note on in chan " + String(channel) + " t= " 
                                + String(msg.getTimeStamp()) + ", ignoring");
                        importresult |= 1;
                        layer = -2;
                        break;
                    }
                }
                if(layer < 0) continue;
                //Find best spot to put note
                bestlayermse = 10000000000.0f;
                bestlayer = -1;
                for(layer=0; layer<max_layers; ++layer){
                    if(ls[layer]->isInUse()) continue;
                    //Calculate the weighted mean-squared error between the new note and the layer's history
                    thislayermse = ls[layer]->mse(msg.getNoteNumber());
                    if(thislayermse < bestlayermse){
                        bestlayer = layer;
                        bestlayermse = thislayermse;
                    }
                }
                if(bestlayer < 0){
                    //No layer was free
                    if(!too_many_notes){
                        dbgmsg("Channel " + String(channel) + " has more than " + String(max_layers) 
                                + " notes on at a time (at t=" + String(msg.getTimeStamp()) + ")!");
                        dbgmsg("Putting the extra notes on an unused channel is not yet supported.");
                        too_many_notes = true;
                        importresult |= 1;
                    }
                }else{
                    //We got a layer to assign it to
                    layertracks[(max_layers*channel)+bestlayer]->addEvent(msg);
                    ls[bestlayer]->writeNote(msg.getNoteNumber());
                }
            }else if(msg.isNoteOff()){
                //Check for existing note
                for(layer=0; layer<max_layers; layer++){
                    if(ls[layer]->curNote() == msg.getNoteNumber()){
                        layertracks[(max_layers*channel)+layer]->addEvent(msg);
                        ls[layer]->writeNote(-1);
                        layer = -2;
                        break;
                    }
                }
                if(layer < 0) continue;
                if(!too_many_notes){
                    dbgmsg("Note off (ch=" + String(channel) + " note=" + String(msg.getNoteNumber())
                            + " time=" + String(msg.getTimeStamp()) + ") received for note that is not on!");
                    too_many_notes = true;
                    importresult |= 1;
                }
            }
        }
        //Check final state
        for(layer=0; layer<max_layers; layer++){
            if(ls[layer]->isInUse()){
                dbgmsg("Chan " + String(channel) + " layer " + String(layer) + " left hanging! Fixing...");
                importresult |= 1;
                msg = MidiMessage::noteOff(channel+1, ls[layer]->curNote());
                msg.setTimeStamp(last_timestamp);
                layertracks[(max_layers*channel)+layer]->addEvent(msg);
            }
        }
        //Update matched pairs
        for(layer=0; layer<max_layers; layer++){
            layertrk = layertracks[(max_layers*channel)+layer];
            layertrk->sort();
            layertrk->updateMatchedPairs();
            if(layertrk->getNumEvents() & 1){
                dbgmsg("Chan " + String(channel) + " lyr " + String(layer) + " track has " 
                        + String(layertrk->getNumEvents()) + " (odd number of) events!");
                importresult |= 1;
            }
        }
    }
    //Generate Audioseq data
    structure = ValueTree("structure");
    ValueTree want, want2, section, newsec;
    Random::getSystemRandom().setSeedRandomly();
    //=======================================================================
    //Sequence header
    //=======================================================================
    dbgmsg("Creating sequence header", false);
    int num_tsections = sectiontimes.size();
    sectiontimes.add(last_timestamp);
    double newtempo;
    int tempolasttime = -100000, tempolastval = -100000;
    int t = 0;
    //Create section for header
    int cmd = 0, value;
    section = ValueTree("seqhdr");
    section.setProperty(idSType, 0, nullptr);
    structure.addChild(section, -1, nullptr);
    //End of Data
    want = wantAction("End of Data", 0);
    section.addChild(createCommand(want), 0, nullptr);
    //Not Sequence Format (D3 20)
    value = (int)midiopts.getProperty("d3", 0x20);
    want = wantAction("Sequence Format", 0);
    wantProperty(want, "Value", value);
    section.addChild(createCommand(want), cmd, nullptr);
    cmd++;
    //Not Sequence Type (D5 32)
    value = (int)midiopts.getProperty("d5", 0x32);
    want = wantAction("Sequence Type", 0);
    wantProperty(want, "Value", value);
    section.addChild(createCommand(want), cmd, nullptr);
    cmd++;
    //Channel Enable (D7 XXXX)
    want = wantAction("Channel Enable", 0);
    wantProperty(want, "Bitfield", chanBitfield);
    section.addChild(createCommand(want), cmd, nullptr);
    cmd++;
    int addmstrvol_cmd = cmd;
    bool hadmastervol = false;
    //Beginning of track (for pointer later)
    want = createMarker();
    int ptrBeginData = want.getProperty(idHash);
    section.addChild(want, cmd, nullptr);
    cmd++;
    //Add events from master track
    m=0;
    int sectimeidx = 0;
    bool done = false;
    while(true){
        if(m >= mastertrack->getNumEvents()){
            done = true;
        }else{
            msg = mastertrack->getEventPointer(m)->message;
            timestamp = msg.getTimeStamp();
        }
        //Insert channel pointers for each section
        //sectimeidx is the *upcoming* section boundary, not the current section time is in
        for(; sectimeidx < num_tsections; sectimeidx++){ //Don't execute this for the boundary at the end of the piece
            if(!done && timestamp < sectiontimes[sectimeidx]) break; //Still more commands before section boundary
            //dbgmsg("Section " + String(sectimeidx) + " starting at " + String(sectiontimes[sectimeidx]));
            dbgmsg(".", false);
            //Get up to the time
            advanceToTimestamp(section, 0, cmd, t, sectiontimes[sectimeidx]);
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
            if(msg.getSysExDataSize() == 6){
                const uint8* sysexdata = msg.getSysExData();
                if(sysexdata[2] == 0x04 && sysexdata[3] == 0x01){
                    //Master volume
                    want = wantAction("Master Volume", 0);
                    wantProperty(want, "Value", sysexdata[5]);
                    hadmastervol = true;
                }
            }
        }
        if(want.isValid()){
            advanceToTimestamp(section, 0, cmd, t, timestamp);
            //Write command
            section.addChild(createCommand(want), cmd, nullptr);
            cmd++;
        }
        //Done
        m++;
    }
    //Get the time to the end
    advanceToTimestamp(section, 0, cmd, t, last_timestamp);
    //Loop to start
    if((bool)midiopts.getProperty("smartloop", false)){
        want = wantAction("Jump Same Level", 0);
        wantProperty(want, "Absolute Address", 1337);
        //TODO smart loop, skip intro
        want = createCommand(want);
        want.setProperty(idTargetSection, 0, nullptr);
        want.setProperty(idTargetHash, ptrBeginData, nullptr);
        section.addChild(want, cmd, nullptr);
        cmd++;
    }
    //Channel Disable (D6 XXXX)
    want = wantAction("Channel Disable", 0);
    wantProperty(want, "Bitfield", chanBitfield);
    section.addChild(createCommand(want), cmd, nullptr);
    cmd++;
    //Master Volume
    if(!hadmastervol){
        uint8 defaultval = (int)midiopts.getProperty("addmstrvolval", 0x58);
        dbgmsg("No Master Volume sysex command in the MIDI, adding default 0x" + hex(defaultval));
        want = wantAction("Master Volume", 0);
        wantProperty(want, "Value", defaultval);
        section.addChild(createCommand(want), addmstrvol_cmd, nullptr);
        cmd++;
    }
    //=======================================================================
    //Channels
    //=======================================================================
    dbgmsg("\nCreating channel headers", false);
    int starttime, endtime;
    int cc;
    //CC Bandwidth Reduction setup
    OwnedArray<CCTracker> ccstates;
    int qt, qa;
    //TODO this is a mess
    qt = 0; //midiopts.getProperty("q_other_time", 1);
    qa = midiopts.getProperty("q_other_amp", 1);
    for(cc=0; cc<130; cc++){ //128 is pitch, 129 is program
        ccstates.add(new CCTracker());
        ccstates[cc]->q_time = qt;
        ccstates[cc]->q_amp = qa;
    }
    ccstates[128]->q_time = 0; //midiopts.getProperty("q_pitch_time", 1);
    ccstates[128]->q_amp = midiopts.getProperty("q_pitch_amp", 1);
    ccstates[129]->q_time = 0;
    ccstates[129]->q_amp = 0;
    qt = 0; //midiopts.getProperty("q_volpan_time", 3);
    qa = midiopts.getProperty("q_volpan_amp", 2);
    ccstates[7]->q_time = qt;
    ccstates[7]->q_amp = qa;
    ccstates[11]->q_time = qt;
    ccstates[11]->q_amp = qa;
    //qt = 0; //midiopts.getProperty("q_pan_time", 3);
    //qa = midiopts.getProperty("q_pan_amp", 2);
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
            //dbgmsg("Chn " + String(channel) + " sec " + String(sectimeidx) + " starting at t" + String(starttime));
            dbgmsg(".", false);
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
                dbgmsg("Could not find channel header for ch " + String(channel) + ", section " + String(sectimeidx) + "!");
                importresult |= 2;
                break;
            }
            cmd = 0;
            //Channel Reset (C4)
            if(sectimeidx == 0){
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
                //Only discard commands after section end if there's a section
                //after this one
                if(timestamp >= endtime && sectimeidx < num_tsections-1) continue;
                //Determine command to execute
                want = ValueTree(); //Invalidate
                cc = -1;
                value = 0;
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
                    advanceToTimestamp(section, 1, cmd, t, timestamp);
                    //Write command
                    section.addChild(createCommand(want), cmd, nullptr);
                    cmd++;
                }
            }
            //Get the time to the end
            advanceToTimestamp(section, 1, cmd, t, endtime);
        }
    }
    //=======================================================================
    //Note Layers / Tracks
    //=======================================================================
    dbgmsg("\nCreating tracks", false);
    MidiMessage msg2, msg3;
    int timestamp2, timestamp3;
    int note, delay, transpose;
    trk = nullptr;
    for(channel=0; channel<16; channel++){
        if(channelsused[channel] < 0) continue;
        for(layer=0; layer<max_layers; layer++){
            layertrk = layertracks[(max_layers*channel)+layer];
            if(layertrk->getNumEvents() == 0) continue;
            //dbgmsg("Layer " + String(layer) + " chn " + String(channel) + " with " + String(layertrk->getNumEvents()) + " events");
            dbgmsg(".", false);
            for(sectimeidx=0; sectimeidx<num_tsections; sectimeidx++){
                starttime = sectiontimes[sectimeidx];
                endtime = sectiontimes[sectimeidx+1];
                //dbgmsg("Sec " + String(sectimeidx) + " starting at t" + String(starttime));
                dbgmsg(".", false);
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
                    dbgmsg("Could not find track data for layer " + String(layer) + " ch " + String(channel) + ", section " + String(sectimeidx) + "!");
                    importresult |= 2;
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
                timestamp3 = 0;
                for(m=0; m<layertrk->getNumEvents(); m++){
                    msg3 = layertrk->getEventPointer(m)->message;
                    timestamp3 = msg3.getTimeStamp();
                    if(timestamp3 < starttime || (timestamp3 == starttime && msg3.isNoteOff())) continue;
                    if(timestamp3 > endtime || (timestamp3 == endtime && !msg3.isNoteOff())){
                        m = layertrk->getNumEvents() + 1;
                        break;
                    }
                    if(msg3.isNoteOn()){
                        break;
                    }
                }
                if(m >= layertrk->getNumEvents()){
                    continue;
                }
                //Seek to timestamp
                advanceToTimestamp(section, 2, cmd, t, timestamp3);
                done = false;
                while(!done){
                    msg = msg3;
                    timestamp = timestamp3;
                    //Get next thing, which should be corresponding note off
                    m++;
                    if(m >= layertrk->getNumEvents()){
                        dbgmsg("Ran off end of track looking for note off!");
                        importresult |= 2;
                        break;
                    }
                    msg2 = layertrk->getEventPointer(m)->message;
                    if(!msg2.isNoteOff()){
                        dbgmsg("Note Off out of order! Cancelling track import!");
                        importresult |= 2;
                        break;
                    }
                    timestamp2 = msg2.getTimeStamp();
                    if(timestamp2 >= endtime){
                        //Cut off note at section break
                        timestamp2 = endtime;
                        timestamp3 = endtime;
                        done = true;
                    }else{
                        //Get note on after that
                        m++;
                        if(m >= layertrk->getNumEvents()){
                            timestamp3 = endtime;
                            done = true;
                        }else{
                            msg3 = layertrk->getEventPointer(m)->message;
                            if(!msg3.isNoteOn()){
                                dbgmsg("Note On out of order! Cancelling track import!");
                                importresult |= 2;
                                break;
                            }
                            timestamp3 = msg3.getTimeStamp();
                        }
                        if(timestamp3 >= endtime){
                            //End section after this note
                            timestamp3 = endtime;
                            done = true;
                        }
                    }
                    if(timestamp2 == timestamp && timestamp3 == timestamp){
                        //The next note is at the same time, just skip to it
                        dbgmsg("Zero-length note with no delay afterwards in chn " + String(channel)
                                + " ly " + String(layer) + " at t=" + String(timestamp) + ", discarding!");
                        importresult |= 1;
                        continue;
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
                        section.addChild(createCommand(want2), cmd, nullptr);
                        cmd++;
                    }
                    wantProperty(want, "Note", note);
                    //Delay
                    delay = timestamp3 - timestamp;
                    if(delay >= 48*2 && ((timestamp2 - timestamp) * 0x100 / delay) < 0x08){
                        //Full note and then timestamp
                        wantProperty(want, "Delay", timestamp2 - timestamp);
                        wantProperty(want, "Gate Time", 0);
                        section.addChild(createCommand(want), cmd, nullptr);
                        cmd++;
                        advanceToTimestamp(section, 2, cmd, timestamp2, timestamp3);
                    }else{
                        wantProperty(want, "Delay", delay);
                        //Gate
                        if(delay == 0){
                            value = 0;
                        }else{
                            value = (timestamp3-timestamp2) * 0x100 / delay;
                            if(value > 0xFF){
                                //Zero-length note, make it a small length instead
                                dbgmsg("Zero-length note in chn " + String(channel) 
                                    + " ly " + String(layer) + " at t=" + String(timestamp)
                                    + "! Making small length instead...");
                                importresult |= 1;
                                value = 0xFF;
                            }
                        }
                        wantProperty(want, "Gate Time", value);
                        //Write note
                        section.addChild(createCommand(want), cmd, nullptr);
                        cmd++;
                    }
                    //Count time
                    t += delay;
                }
                //Get the time to the end
                advanceToTimestamp(section, 2, cmd, t, endtime);
            }
        }
    }
    //=======================================================================
    //Optimization
    //=======================================================================
    optimize(midiopts);
    reduceTrackNotes();
    //Done
    dbgmsg("\n----------------------------------------------------------\nDone!!!");
    return importresult;
}

void SeqFile::optimize(ValueTree midiopts){
    int sec1, sec2;
    int stype1, stype2;
    int numcmds1, numcmds2;
    ValueTree section1, section2;
    int cmd1, cmd2, cmd3, cmd4;
    ValueTree command1, command2, command3, command4;
    String action1, action2, action3, action4;
    //Delete mostly-empty sections (with no meaningful data)
    //Empty tracks contain a Layer Transpose command and a End of Data command
    for(sec1=0; sec1<structure.getNumChildren(); ++sec1){
        section1 = structure.getChild(sec1);
        if((int)section1.getProperty(idSType, -1) != 2) continue;
        if(section1.getNumChildren() != 2) continue;
        if(section1.getChild(0).getProperty(idAction, "No Action").toString() != "Layer Transpose") continue;
        if(section1.getChild(1).getProperty(idAction, "No Action").toString() != "End of Data") continue;
        //Found it, delete this section
        deleteSection(sec1);
        --sec1;
    }
    //Empty channels contain a Timestamp command and a End of Data command
    for(sec1=0; sec1<structure.getNumChildren(); ++sec1){
        section1 = structure.getChild(sec1);
        if((int)section1.getProperty(idSType, -1) != 1) continue;
        if(section1.getNumChildren() != 2) continue;
        if(section1.getChild(0).getProperty(idAction, "No Action").toString() != "Timestamp") continue;
        if(section1.getChild(1).getProperty(idAction, "No Action").toString() != "End of Data") continue;
        //Found it, delete this section
        deleteSection(sec1);
        --sec1;
    }
    //Check if we want loop or call optimizations
    int stacksize = 4; //TODO consider stack
    bool useCalls = midiopts.getProperty("usecalls", true);
    bool useLoops = midiopts.getProperty("useloops", true);
    if(!useCalls && !useLoops){
        dbgmsg("\nNo loop or call optimization selected.");
        return;
    }
	//Check if loops need to be limited to 255 iterations
	int maxloopcount = getLargestCommandRange(0, "Loop Start", "Loop Count") - 1;
    dbgmsg("\nMaximum of " + String(maxloopcount) + " loop iterations");
    //
    int cmdafter;
    bool flag;
    int loopCount;
    int numCmdsDelete;
    //
    ValueTree want, want2, param;
    int i;
    int cclast, ccdir, ccthis;
    if(useLoops){
        dbgmsg("\nLooking for data to loop");
        for(sec1=0; sec1<structure.getNumChildren(); sec1++){
            section1 = structure.getChild(sec1);
            stype1 = section1.getProperty(idSType, -1);
            numcmds1 = section1.getNumChildren();
            //dbgmsg("Examining section " + String(sec1) + " (stype == " + String(stype1) + "), " + String(numcmds1) + " commands");
            dbgmsg(".", false);
            //Pick a command
            for(cmd1=0; cmd1<numcmds1-1; cmd1++){
                command1 = section1.getChild(cmd1);
                action1 = command1.getProperty(idAction, "No Action");
                //dbgmsg("----Command " + String(cmd1) + "(" + action1 + ")");
                //Don't loop pointers or no actions
                if(action1 == "No Action" || action1 == "End of Data" || action1 == "Jump Same Level"
                        || action1 == "Ptr Channel Header" || action1 == "Ptr Track Data"){
                    continue;
                }
                //See if this command repeats later in the track, for loops
                for(cmd2=cmd1+1; cmd2<numcmds1-1; cmd2++){
                    command2 = section1.getChild(cmd2);
                    if(isCloseEnough(command1, command2, true, midiopts)){
                        //See if everything is the same in between
                        flag = true;
                        cmd3 = cmd1+1;
                        cmd4 = cmd2+1;
                        while(cmd3 < cmd2){
                            if(cmd4 >= numcmds1){
                                flag = false;
                                break;
                            }
                            if(!isCloseEnough(section1.getChild(cmd3), section1.getChild(cmd4), true, midiopts)){
                                flag = false;
                                break;
                            }
                            cmd3++;
                            cmd4++;
                        }
                        if(!flag) continue;
                        //We have a loop!
                        //dbgmsg("Sec " + String(sec1) + ": found loopable data from cmds " + String(cmd1) + " to " + String(cmd2));
                        //Check if the contents of the loop are solely timestamps and one kind of CC,
                        //and the CC values are monotonically going in one direction
                        flag = true;
                        action4 = "";
                        ccdir = 0;
                        cclast = -1;
                        for(cmd3=cmd1; cmd3<cmd2; ++cmd3){
                            command3 = section1.getChild(cmd3);
                            action3 = command3.getProperty(idAction, "No Action");
                            if(action3 == "Timestamp"){
                                //do nothing
                            }else if(action3 == "Chn Volume" || action3 == "Chn Pan" 
                                    || action3 == "Chn Effects" || action3 == "Chn Pitch Bend"){
                                if(action4 == ""){
                                    action4 = action3;
                                    param = command3.getChildWithProperty(idMeaning, "Value");
                                    if(!param.isValid()){
                                        dbgmsg("Error, Chn CC command without value!");
                                        importresult |= 2;
                                        flag = false;
                                        break;
                                    }
                                    cclast = param.getProperty(idValue, -1234);
                                }else if(action3 != action4){
                                    flag = false; //More than one type of CC detected
                                    break;
                                }else{
                                    param = command3.getChildWithProperty(idMeaning, "Value");
                                    if(!param.isValid()){
                                        dbgmsg("Error, Chn CC command without value!");
                                        importresult |= 2;
                                        flag = false;
                                        break;
                                    }
                                    ccthis = param.getProperty(idValue, -5678);
                                    if(ccdir == 0){
                                        if(ccthis < cclast) ccdir = -1;
                                        else if(ccthis > cclast) ccdir = 1;
                                    }else if(ccdir == 1){
                                        if(ccthis < cclast){
                                            //CCs were going up and now down, done
                                            flag = false;
                                            break;
                                        }
                                    }else if(ccdir == -1){
                                        if(ccthis > cclast){
                                            //CCs were going down and now up, done
                                            flag = false;
                                            break;
                                        }
                                    }
                                }
                            }else{
                                flag = false; //Something other than a CC detected (e.g. note)
                                break;
                            }
                        }
                        //If this looks like this might be a loop that would destroy the CCs, repeat
                        //the scan but with no margin for CCs being "close enough"
                        if(flag){
                            flag = true;
                            cmd3 = cmd1;
                            cmd4 = cmd2;
                            while(cmd3 < cmd2){
                                if(cmd4 >= numcmds1){
                                    flag = false;
                                    break;
                                }
                                if(!isCloseEnough(section1.getChild(cmd3), section1.getChild(cmd4), false, midiopts)){
                                    flag = false;
                                    break;
                                }
                                cmd3++;
                                cmd4++;
                            }
                            if(!flag) continue; //With tighter restrictions, the loop wasn't valid
                            flag = false; //Prohibit "close enough" in subsequent loop repeats
                        }else{
                            flag = true; //Allow "close enough" in subsequent loop repeats
                        }
                        //See if it's repeated some more afterwards
                        loopCount = 2;
                        cmd3 = cmd1;
                        cmdafter = cmd4;
                        while(cmd4 < numcmds1 && (loopCount+1 < maxloopcount)){
                            if(cmd3 == cmd2){
                                loopCount++;
                                cmd3 = cmd1;
                                cmdafter = cmd4;
                            }
                            if(!isCloseEnough(section1.getChild(cmd3), section1.getChild(cmd4), flag, midiopts)){
                                break;
                            }
                            cmd3++;
                            cmd4++;
                        }
                        //How much data to delete?
                        numCmdsDelete = cmdafter - cmd2;
                        //dbgmsg("Found loop at " + String(cmd1) + ", " + String(numCmdsDelete) + " commands"
                        //        + " long, which repeats " + String(loopCount) + " times" );
                        dbgmsg("*", false);
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
        dbgmsg("\nLooking for hooks");
        ValueTree origlist("list");
        ValueTree item;
        ValueTree sectionN;
        int secN;
        int j;
        int hooklength;
        int curdatalength, calleddatalength;
        for(sec1=0; sec1<structure.getNumChildren(); sec1++){
            section1 = structure.getChild(sec1);
            stype1 = section1.getProperty(idSType, -1);
            numcmds1 = section1.getNumChildren();
            int sec1time = getTotalSectionTime(section1);
            //dbgmsg("Examining section " + String(sec1) + " (stype == " + String(stype1) + "), " + String(numcmds1) + " commands");
            dbgmsg(".", false);
            //Pick a command
            for(cmd1=0; cmd1<numcmds1-1; cmd1++){
                command1 = section1.getChild(cmd1);
                action1 = command1.getProperty(idAction, "No Action");
                //dbgmsg("----Command " + String(cmd1) + "(" + action1 + ")");
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
                //Find all the places, in any section of the same stype, where this string of two commands appears (including overlapping)
                origlist.removeAllChildren(nullptr);
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
                        if(!isCloseEnough(command1, command2, true, midiopts)) continue;
                        if(!isCloseEnough(command3, command4, true, midiopts)) continue;
                        item = ValueTree("item");
                        item.setProperty(idSection, sec2, nullptr);
                        item.setProperty(idCmd, cmd2, nullptr);
                        origlist.addChild(item, -1, nullptr);
                        cmd2++;
                    }
                }
                //Found anything?
                if(origlist.getNumChildren() == 0) continue;
                //dbgmsg("Got hook, found elsewhere " + String(list.getNumChildren()) + " times");
                //Make temporary copy of original list with no overlaps and increasingly long hooks
                int bestscore = 0, curscore;
                ValueTree list, bestlist;
                for(hooklength = 1; ; hooklength++){
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
                    list = origlist.createCopy();
                    for(i=0; i<list.getNumChildren(); i++){
                        flag = false;
                        item = list.getChild(i);
                        sec2 = item.getProperty(idSection);
                        cmd2 = item.getProperty(idCmd);
                        section2 = structure.getChild(sec2);
                        numcmds2 = section2.getNumChildren();
                        if(cmd2 + hooklength >= numcmds2) flag = true;
                        if(!flag){
                            //Make sure this hook isn't overlapping with any previous one
                            for(j=0; j<i; ++j){
                                if((int)list.getChild(j).getProperty(idSection) == sec2 
                                        && cmd2 <= (int)list.getChild(j).getProperty(idCmd) + hooklength){
                                    flag = true;
                                    break;
                                }
                            }
                            //Also make sure it's not overlapping with the original one!
                            if(sec1 == sec2 && cmd2 <= cmd1 + hooklength) flag = true;
                        }
                        if(!flag){
                            //See if this is a valid copy of the original hook
                            for(j=2; j<=hooklength; ++j){ //Already know first 2 commands match
                                cmd3 = cmd1 + j;
                                cmd4 = cmd2 + j;
                                if(cmd4 >= numcmds2) break;
                                command3 = section1.getChild(cmd3);
                                action3 = command3.getProperty(idAction, "No Action");
                                command4 = section2.getChild(cmd4);
                                action4 = command4.getProperty(idAction, "No Action");
                                if(action3 != action4) break;
                                if(!isCloseEnough(command3, command4, true, midiopts)) break;
                            }
                            if(j > hooklength){
                                //Ran off end of loop, therefore it matched
                                continue;
                            }
                        }
                        //Otherwise, drop the command
                        list.removeChild(i, nullptr);
                        --i;
                    }
                    curscore = list.getNumChildren() * (hooklength + 1); //Number of commands which will be removed with call
                    if(hooklength > 1 && bestscore > curscore){
                        //We were saving more commands before: stop
                        break;
                    }
                    bestscore = curscore;
                    bestlist = list.createCopy();
                }
                //dbgmsg("Grew hook to " + String(hooklength) + ", now used " + String(bestlist.getNumChildren()) + " times");
                //Calculate data savings, ensure it's a savings
                j = 0;
                for(i=0; i<hooklength; ++i){
                    j += getNewCommandLength(section1.getChild(cmd1+i));
                }
                curdatalength = j*bestlist.getNumChildren();
                calleddatalength = j;
                want = wantAction("End of Data", stype1);
                want = createCommand(want);
                calleddatalength += getNewCommandLength(want);
                want = wantAction("Call Same Level", stype1);
                wantProperty(want, "Absolute Address", 1337);
                want = createCommand(want);
                calleddatalength += bestlist.getNumChildren() * getNewCommandLength(want);
                if(curdatalength <= calleddatalength){
                    //dbgmsg("Current data " + String(curdatalength) + " bytes, with calls " + String(calleddatalength) + " bytes, no savings, aborting call");
                    continue;
                }else{
                    //dbgmsg("Call " + String(hooklength) + " commands from " + String(bestlist.getNumChildren())
                    //        + " places saved " + String(curdatalength - calleddatalength) + " bytes");
                    dbgmsg("*", false);
                }
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
                for(i=bestlist.getNumChildren() - 1; i>=0; i--){ //Go in reverse order so the cmd numbers are never changed
                    item = bestlist.getChild(i);
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
                //Make sure we didn't screw up
                int sec1time_after = getTotalSectionTime(section1);
                if(sec1time != sec1time_after){
                    dbgmsg("CRITICAL: Bug found when creating calls! Call data contained:");
                    for(i=0; i<hooklength; ++i){
                        dbgmsg("--" + sectionN.getChild(i).getProperty(idAction).toString());
                    }
                    dbgmsg("Call was found at:");
                    dbgmsg("--Section " + String(sec1) + " cmd " + String(cmd1));
                    for(i=0; i<bestlist.getNumChildren(); ++i){
                        dbgmsg("-- Section " + bestlist.getChild(i).getProperty(idSection).toString() 
                                       + " cmd " + bestlist.getChild(i).getProperty(idCmd).toString());
                    }
                    importresult |= 2;
                    return;
                }
            }
        }
        //Replace all 2-loops of 1-calls, 2-loops of 2-calls, or 3-loops of 1-calls with individual calls
        dbgmsg("\nFixing short-looped calls...", false);
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
                    //dbgmsg("----Converting 3-loop of 1-call to 3 calls in sec " + String(sec1) + " cmd " + String(cmd1));
                    dbgmsg("*", false);
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
                        //dbgmsg("----Converting 2-loop of 1-call to 2 calls in sec " + String(sec1) + " cmd " + String(cmd1));
                        dbgmsg("*", false);
                        //Remove loop start, replace with call
                        section1.removeChild(cmd1, nullptr);
                        section1.addChild(command2.createCopy(), cmd1, nullptr);
                        //Remove loop end
                        cmd1 += 2;
                        section1.removeChild(cmd1, nullptr);
                        cmd1--; //Go back so we hit the next command
                    }else if(command4.getProperty(idAction, "No Action").toString() == "Loop End"){
                        if(command3.getProperty(idAction, "No Action").toString() != "Call Same Level") continue;
                        //dbgmsg("----Converting 2-loop of 2-calls to 4 calls in sec " + String(sec1) + " cmd " + String(cmd1));
                        dbgmsg("*", false);
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
    dbgmsg("\nReducing track notes to shortest types...");
    int sec, lastdelay, delay, gate, cmd;
    ValueTree section;
    ValueTree command, newcommand, paramd, paramg;
    String action;
    //Reduce
    for(sec=0; sec<structure.getNumChildren(); sec++){
        section = structure.getChild(sec);
        if((int)section.getProperty(idSType, -1) != 2) continue;
        //dbgmsg("--Section " + String(sec));
        lastdelay = -1234;
        for(cmd=0; cmd<section.getNumChildren(); cmd++){
            command = section.getChild(cmd);
            action = command.getProperty(idAction, "No Action");
            if(action == "Loop Start" || action == "Call Same Level"){
                lastdelay = -1234;
            }
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


////////////////////////////////////////////////////////////////////////////////
///////////////////////////// exportMIDI functions /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#if 0

//Stype: 0 seq hdr, 1 chn hdr, 2 track data
ValueTree SeqFile::getDescription(uint8 firstbyte, int stype){
    ValueTree test;
    for(int i=0; i<abi.getNumChildren(); i++){
        test = abi.getChild(i);
        if(!isCommandValidIn(test, stype)) continue;
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
        //dbgmsg(hex((uint32)address, 6) + ": " + hex(c) + " " + action);
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
                    dbgmsg("Due to SeqFile variable length format, length > 2 not defined!");
                    paramvalue = 0;
                    len += datalen;
                    paramlen += datalen;
                }
                param.setProperty(idDataAddr, (int)(a-address), nullptr);
                param.setProperty(idDataActualLen, paramlen, nullptr);
            }else{
                dbgmsg("Invalid command description! datasrc == " + datasrc + ", action == " + action);
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
            dbgmsg("@" + hex(currentAddr,4) + ": Pointer with no address value!");
            return -1;
        }
    }
    if(address >= data.size()){
        dbgmsg("@" + hex(currentAddr,4) + ": Pointer off end of sequence to " 
                + hex((uint32)address,4) + ", skipping!");
        return -1;
    }
    return address;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// exportMIDI objects //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct SeqTSection{
    SeqTSection(){
        time = address = address_end = 0;
    }
    uint32 time, address, address_end;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// exportMIDI //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void exportMIDI(File midifile, ValueTree midiopts){
    ROM& rom;
    ValueTree command, param;
    String action, meaning;
    int channel, notelayer, value, transpose, delay, note, velocity, gate;
    //bool qDelay, qVelocity, qGate;
    uint32 address, t, a;
    int stype = 0;
    int cmdlen;
    //Stacks
    const int stack_size = 16;
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
	//Program options
	ValueTree progoptions("progoptions");
	const int progoptionscc = 117, progoptionsnullcc = 116;
    //CC Setup
    int ticks_multiplier = midiopts.getProperty("ppqnmultiplier", 1);
    if(ticks_multiplier <= 0) ticks_multiplier = 1;
    int bend_range = midiopts.getProperty("bendrange", 6);
    if(bend_range <= 0) bend_range = 1;
    //Changing these is no longer supported--I never heard of anyone using them
    String chnvol = "CC7 (Volume)"; //midiopts.getProperty("chnvol", "CC7 (Volume)").toString();
    String mtrvol = "SysEx MstrVol"; //midiopts.getProperty("mtrvol", "CC24 (None)").toString();
    String chnpriority = "CC25 (None)"; //midiopts.getProperty("chnpriority", ).toString();
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
    /*
    TODO banks
    //Bank setup
    //Try to load bank number
    std::unique_ptr<BankFile> bank = nullptr;
    do{
        if(bank_num < 0){
            dbgmsg("No bank associated with this sequence at load time");
            break;
        }
        //Look up bank info
        ValueTree abinfonode = romdesc.getChildWithName("knownfilelist")
                .getChildWithProperty("type", "Audiobank");
        if(!abinfonode.isValid()){
            dbgmsg("No Audiobank Index defined in RomDesc, cannot load bank");
            break;
        }
        uint32 abaddr = (int)abinfonode.getProperty("address");
        if(abaddr >= rom.getSize()){
            dbgmsg("Invalid Audiobank Index in RomDesc " + hex(abaddr) + ", cannot load bank");
            break;
        }
        //Load bank
        dbgmsg("Loading bank " + hex((uint8)bank_num));
        bank.reset(new BankFile(romdesc));
        if(!bank->load(rom, bank_num)){
            dbgmsg("Loading bank " + String(bank_num) + " failed");
            bank = nullptr;
        }
    }while(false);
    */
    //BEGIN
    dbgmsg("EXPORTING MIDI FILE");
    t = 0;
    a = 0;
	channel = notelayer = 0;
	delay = -1;
    bool ended_naturally = false;
    while(a < data.size()){
        command = getCommand(a, stype);
        cmdlen = (int)command.getProperty(idLength, 1);
        a += cmdlen;
        action = command.getProperty(idAction, "Unknown");
        //Normal actions
        if(action == "Unknown"){
            //do nothing
            dbgmsg("Unknown Action " + hex((uint8)(int)command.getProperty(idCmd)) 
                    + " in stype " + String(stype) + " @" + hex(a, 6));
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
            while(stackptr >= 0 && stypestack[stackptr] == -4){
                dbgmsg("End of Data while in a loop (i.e. corrupt sequence)!");
                stackptr--;
            }
            if(stackptr < 0 || stypestack[stackptr] < 0){
                dbgmsg("FATAL: Hopelessly corrupted sequence structure!");
                break;
            }
            //Restore values
            a = addrstack[stackptr];
            if(stypestack[stackptr] != stype){
                //Return from chn or track, not call
                t = timestack[stackptr];
                stype = stypestack[stackptr];
            }
        }else if(action == "Jump Same Level"){
            dbgmsg("Ignoring Jump Same Level @" + hex(a,4));
        }else if(action == "Call Same Level"){
            value = getPtrAddress(command, a);
            if(value < 0) continue;
            address = value;
            addrstack[stackptr] = a;
            timestack[stackptr] = 100000; //This value should never be popped!
            stypestack[stackptr] = stype;
            stackptr++;
            if(stackptr >= stack_size){
                dbgmsg("FATAL: Stack Overflow SeqFile::toMIDIFile()!");
                break;
            }
            a = address;
        }else if(action == "Loop Start"){
            param = command.getChildWithProperty(idMeaning, "Loop Count");
            int loopcount = getAdjustedValue(param);
            if(loopcount < 2 || loopcount > 0xFF){
                dbgmsg("Likely invalid loop count = " + String(loopcount) + ", ignoring!");
                continue;
            }
            addrstack[stackptr] = a;
            timestack[stackptr] = loopcount;
            stypestack[stackptr] = -4; //means loop stack entry
            stackptr++;
            if(stackptr >= stack_size){
                dbgmsg("FATAL: Stack Overflow SeqFile::toMIDIFile()!");
                break;
            }
        }else if(action == "Loop End"){
            if(stackptr <= 0 || stypestack[stackptr-1] != -4){
                dbgmsg("Loop End command not after Loop Start, ignoring!");
                continue;
            }
            stackptr--;
            timestack[stackptr]--; //loop count
            if(timestack[stackptr] > 0){
                //Still some loops left for us, go back
                a = addrstack[stackptr];
                stackptr++;
            }//Otherwise just continue with the sequence
        }else if(action == "Ptr Channel Header"){
            value = getPtrAddress(command, a);
            if(value < 0) continue;
            address = value;
            param = command.getChildWithProperty(idMeaning, "Channel");
            if(param.isValid()){
                channel = getAdjustedValue(param);
            }
            if(channel >= 16){
                dbgmsg("Ptr Channel Header with channel >= 16!");
                continue;
            }
            //Valid pointer
            //MIDI file section
            if(willBeNewTSec){
                dbgmsg("New section @" + hex(a,4) + ", t=" + hex(t,4));
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
                dbgmsg("FATAL: Stack Overflow SeqFile::toMIDIFile()!");
                break;
            }
            a = address;
            stype = 1;
            velocity = 127;
            gate = 0xFF;
            delay = -1;
            //dbgmsg("----T" + hex(t, 6) + ": Entering Chan " + String(channel) + " Hdr");
        }else if(action == "Ptr Track Data"){
            value = getPtrAddress(command, a);
            if(value < 0) continue;
            address = value;
            param = command.getChildWithProperty(idMeaning, "Note Layer");
            if(!param.isValid()){
                dbgmsg("Ptr Track Data with no note layer value!");
                continue;
            }
            notelayer = getAdjustedValue(param);
            addrstack[stackptr] = a;
            timestack[stackptr] = t;
            stypestack[stackptr] = stype;
            stackptr++;
            if(stackptr >= stack_size){
                dbgmsg("FATAL: Stack Overflow SeqFile::toMIDIFile()!");
                break;
            }
            a = address;
            stype = 2;
            //dbgmsg("----====T" + hex(t, 6) + ": Entering Track layer " + String(notelayer));
            //dbgmsg("@" + hex(a, 6) + ": Track Data " + String(notelayer));
        }else if(action == "Master Volume"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                dbgmsg("Master Volume event with no value!");
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
                sysexdata[4] = 0x00;
                sysexdata[5] = value;
                msg = MidiMessage::createSysExMessage(sysexdata, 6);
                msg.setTimeStamp(t*ticks_multiplier);
                mastertrack.addEvent(msg);
                continue;
            }else{
                dbgmsg("Master Volume event, unknown mapping: " + mtrvol + ", ignoring");
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
                dbgmsg("Tempo event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            uint32 tempovalue = 60000000 / value;
            msg = MidiMessage::tempoMetaEvent(tempovalue);
            msg.setTimeStamp(t*ticks_multiplier);
            mastertrack.addEvent(msg);
        }else if(action == "Chn Reset"){
            //Reset transposes for this channel
            for(notelayer=0; notelayer<max_layers; notelayer++){
                transposes.set((channel*max_layers)+notelayer, 0);
            }
        }else if(action == "Chn Priority"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                dbgmsg("Chn Priority event with no value!");
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
                dbgmsg("Channel Priority event, unknown mapping: " + chnpriority + ", ignoring");
                continue;
            }
            msg = MidiMessage::controllerEvent(channel+1, cc, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Volume"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                dbgmsg("Chn Volume event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            int cc = 7;
            if(chnvol == "CC7 (Volume)"){
                cc = 7;
            }else if(chnvol == "CC11 (Expr)"){
                cc = 11;
            }else{
                dbgmsg("Channel Volume event, unknown mapping: " + chnvol + ", ignoring");
                continue;
            }
            msg = MidiMessage::controllerEvent(channel+1, cc, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Pan"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                dbgmsg("Chn Pan event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            msg = MidiMessage::controllerEvent(channel+1, 10, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Effects"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                dbgmsg("Chn Effects event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            msg = MidiMessage::controllerEvent(channel+1, 91, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Vibrato"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                dbgmsg("Chn Vibrato event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            msg = MidiMessage::controllerEvent(channel+1, 77, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Pitch Bend"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                dbgmsg("Chn Pitch Bend event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            if(value >= 0x80) value -= 0x100;
            value = (1<<13) + (value << 7);
            if(value < 0) value = 0;
            if(value >= (1<<14)) value = (1<<14) - 1;
            //dbgmsg("Pitch Bend original value " + String(value) + " or " + hex((uint32)value));
            msg = MidiMessage::pitchWheel(channel+1, value);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Chn Transpose"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                dbgmsg("Chn Transpose event with no value!");
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
                dbgmsg("Layer Transpose event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            if(value >= 0x80) value -= 0x100;
            transposes.set((channel*max_layers)+notelayer, value);
        }else if(action == "Chn Instrument"){
            param = command.getChildWithProperty(idMeaning, "Value");
            if(!param.isValid()){
                dbgmsg("Chn Instrument event with no value!");
                continue;
            }
            value = getAdjustedValue(param);
            dbgmsg("Chn Instrument " + String(value) + " channel " + String(channel));
            //Cancel previous progoptions
            msg = MidiMessage::controllerEvent(channel+1, progoptionsnullcc, 0);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
            /*
            TODO bank integration
            //Load MIDI equivalent instrument from bank
            int midiprogram = value;
            do{
                if(midiopts.getProperty("exportformat", "gm_ch10").toString() == "original"){
                    dbgmsg("Not converting Chn Instrument because want original format export");
                    break;
                }
                if(bank == nullptr){
                    dbgmsg("Could not load MIDI instrument from bank: no bank specified");
                    break;
                }
                ValueTree instlist = bank->d.getChildWithName("abbank").getChildWithProperty("name", "ABBank")
                        .getChildWithProperty("meaning", "List of Ptrs to Insts");
                if(!instlist.isValid()){
                    dbgmsg("Could not load MIDI instrument from bank: abbank invalid");
                    break;
                }
                ValueTree instlistitem = instlist.getChild(value);
                if(!instlistitem.isValid()){
                    dbgmsg("Could not load MIDI instrument from bank: no ABBank entry for inst #" + String(value) + " (usually means out of range)");
                    break;
                }
                int instindex = instlistitem.getProperty("index", -1);
                if(instindex < 0){
                    dbgmsg("Could not load MIDI instrument from bank: instrument is nullptr");
                    break;
                }
                ValueTree instrument = bank->d.getChildWithName("instruments").getChild(instindex);
                if(!instrument.isValid()){
                    dbgmsg("Could not load MIDI instrument from bank: could not load instrument #" + String(instindex));
                    break;
                }
                String map = instrument.getProperty("map", "Error").toString();
                if(map == "program"){
                    midiprogram = instrument.getProperty("program", 0);
                    int tp = instrument.getProperty("transpose", 0);
                    if(tp != 0){
                        msg = MidiMessage::controllerEvent(channel+1, progoptionscc, progoptions.getNumChildren());
                        msg.setTimeStamp(t*ticks_multiplier);
                        mtracks[channel]->addEvent(msg);
                        ValueTree tpopt("instrument");
                        tpopt.setProperty("tp", tp, nullptr);
                        progoptions.addChild(tpopt, progoptions.getNumChildren(), nullptr);
                    }
                    dbgmsg("Changed instrument " + String(value) + " to program " + String(midiprogram)
                             + ", transpose " + String(tp));
                }else if(map == "drum"){
                    msg = MidiMessage::controllerEvent(channel+1, progoptionscc, progoptions.getNumChildren());
                    msg.setTimeStamp(t*ticks_multiplier);
                    mtracks[channel]->addEvent(msg);
                    ValueTree tpopt("drum");
                    tpopt.setProperty("drum1", instrument.getProperty("drumsplit1", 0), nullptr);
                    tpopt.setProperty("drum2", instrument.getProperty("drumsplit2", 0), nullptr);
                    tpopt.setProperty("drum3", instrument.getProperty("drumsplit3", 0), nullptr);
                    ValueTree temp = instrument.getChildWithName("struct").getChildWithProperty("meaning", "Split Point 1");
                    if(!temp.isValid()){
                        dbgmsg("Instrument has no Split Point 1 field!");
                        tpopt.setProperty("split1", -1, nullptr);
                    }else{
                        tpopt.setProperty("split1", (int)temp.getProperty("value", -1) + midi_basenote, nullptr);
                    }
                    temp = instrument.getChildWithName("struct").getChildWithProperty("meaning", "Split Point 2");
                    if(!temp.isValid()){
                        dbgmsg("Instrument has no Split Point 2 field!");
                        tpopt.setProperty("split2", -1, nullptr);
                    }else{
                        tpopt.setProperty("split2", (int)temp.getProperty("value", -1) + midi_basenote, nullptr);
                    }
                    progoptions.addChild(tpopt, progoptions.getNumChildren(), nullptr);
                    if(midiopts.getProperty("exportformat", "gm_ch10").toString() == "gm_multi"){
                        //Add multi-drum-channel hacks
                        //GM2 mode on
                        // uint8 gm2modeonsysex[4] = {0x7E, 0x7F, 0x09, 0x03};
                        // msg = MidiMessage::createSysExMessage(gm2modeonsysex, 4);
                        // msg.setTimeStamp(t*ticks_multiplier);
                        // mtracks[channel]->addEvent(msg);
                        //GM2 bank 120,0 is percussion
                        msg = MidiMessage(0xB0 | channel, 0, 120, t*ticks_multiplier);
                        mtracks[channel]->addEvent(msg);
                        msg = MidiMessage(0xB0 | channel, 32, 0, t*ticks_multiplier);
                        mtracks[channel]->addEvent(msg);
                        //Roland GS: SysEx to turn any channel to percussion mode
                        uint8 gssysex[9] = {0x41, 0x10, 0x42, 0x12, 0x40, (uint8)(0x10 + channel), 0x15, 0x02, (uint8)(0x19 - channel)};
                        msg = MidiMessage::createSysExMessage(gssysex, 9);
                        msg.setTimeStamp(t*ticks_multiplier);
                        mtracks[channel]->addEvent(msg);
                        //TODO none of this is ever turned off, in case the sequence turns this back from drum mode to an instrument!
                    }
                    continue; //Don't add program change message
                }
            }while(false);
            */
            //
            msg = MidiMessage::programChange(channel+1, midiprogram);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else if(action == "Track Note"){
            //qDelay = qVelocity = qGate = false;
            //Delay already taken care of
            //Note
            param = command.getChildWithProperty(idMeaning, "Note");
            if(!param.isValid()){
                dbgmsg("Track Note event with no note!");
                continue;
            }
            value = getAdjustedValue(param);
            transpose = transposes[(channel*max_layers)+notelayer];
            note = value + transpose + midi_basenote;
            if(note < 0 || note >= 128){
                dbgmsg("Bad (transposed?) note @" + hex(a, 4)
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
                //qVelocity = true;
			}else{
				velocity = 0x7F;
			}
            //Gate time
            param = command.getChildWithProperty(idMeaning, "Gate Time");
            if(param.isValid()){
                gate = getAdjustedValue(param);
                //qGate = true;
            }else{
                gate = 0;
            }
            //Fetch delay to get gate time proportion
            param = command.getChildWithProperty(idMeaning, "Delay");
            if(param.isValid()){
                delay = getAdjustedValue(param);
                //qDelay = true;
            }else{
                if(delay < 0){
                    dbgmsg("Track Note command using previous delay, but not previously set! (Corrupted sequence / will break timings)");
                    delay = 1;
                }
                //dbgmsg("@" + hex(a, 6) + ": No delay value given, using current " + hex((uint32)delay, 4));
                //Add it so we actually do the delay!
                param = ValueTree("parameter");
                param.setProperty(idMeaning, "Delay", nullptr);
                param.setProperty(idValue, delay, nullptr);
                command.addChild(param, command.getNumChildren(), nullptr);
            }
            /*
            dbgmsg("@" + hex(a, 4) + " c " + hex((uint8)channel, 1) + " l " + hex((uint8)notelayer, 1)
                    + " n " + hex((uint8)note)       + " v " +  hex((uint8)velocity) 
                    + " g " +  hex((uint32)gate, 4)  + " d " + hex((uint32)delay, 4)
                    + " r " + String((float)((gate*delay) / 256.0))
                    + (qDelay ? ("") : (" (using old delay)"))
                    + (qGate ? ("") : (" (no gate)"))
                    + (qVelocity ? ("") : (" (using old velocity)"))  );
            */
            msg = MidiMessage::noteOn(channel+1, note, (uint8)velocity);
            msg.setTimeStamp(t*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
            msg = MidiMessage::noteOff(channel+1, note, (uint8)0);
            msg.setTimeStamp((t + delay - ((gate*delay) >> 8))*ticks_multiplier);
            mtracks[channel]->addEvent(msg);
        }else{
            dbgmsg("Unknown command action " + action + "!");
        }
        //Execute delay
        param = command.getChildWithProperty(idMeaning, "Delay");
        if(param.isValid()){
            //Don't set the variable "delay"--future notes reference the last note's delay, not just the last delay which may have occurred
            t += getAdjustedValue(param);
        }
    }
    if(!ended_naturally){
        dbgmsg("Converting sequence ran off end! a==" + hex(a) + ", length==" + hex((uint32)data.size()));
    }
    //Ensure messages are in order
    for(channel=0; channel<16; channel++){
        mtracks.set(channel, ensureSimulMsgsInOrder(*mtracks[channel]), true);
    }
    //Resolve progoptions
    dbgmsg("Resolving progoptions...");
    for(channel=0; channel<16; channel++){
        int tp = 0;
        int drummode = 0, drum1 = -1, drum2 = -1, drum3 = -1, split1 = -1, split2 = -1;
        for(int m=0; m<mtracks[channel]->getNumEvents(); ++m){
            MidiMessage* msgp = &(mtracks[channel]->getEventPointer(m)->message);
            if(msgp->isController() && msgp->getControllerNumber() == progoptionsnullcc){
                dbgmsg("--Chn " + String(channel) + ": progoptions reset");
                tp = 0;
                drummode = 0;
                mtracks[channel]->deleteEvent(m, false);
                --m;
            }else if(msgp->isController() && msgp->getControllerNumber() == progoptionscc){
                ValueTree po = progoptions.getChild(msgp->getControllerValue());
                mtracks[channel]->deleteEvent(m, false);
                --m;
                if(!po.isValid()){
                    dbgmsg("progoptions consistency error!");
                    continue;
                }
                if(po.getType().toString() == "instrument"){
                    dbgmsg("--Chn " + String(channel) + ": new inst progoptions tp=" + String(tp));
                    tp = po.getProperty("tp", 0);
                }else if(po.getType().toString() == "drum"){
                    drum1 = po.getProperty("drum1", -1);
                    drum2 = po.getProperty("drum2", -1);
                    drum3 = po.getProperty("drum3", -1);
                    split1 = po.getProperty("split1", -1);
                    split2 = po.getProperty("split2", -1);
                    if(midiopts.getProperty("exportformat", "gm_ch10").toString() == "gm_multi"){
                        dbgmsg("--Chn " + String(channel) + ": new progoptions multi drum mode");
                        drummode = 2;
                    }else{
                        dbgmsg("--Chn " + String(channel) + ": new progoptions ch10 drum mode");
                        drummode = 1;
                    }
                }else{
                    dbgmsg("progoptions type error!");
                }
            }else if(msgp->isNoteOnOrOff()){
                if(drummode == 0){
                    if(tp != 0){
                        msgp->setNoteNumber(msgp->getNoteNumber() + tp);
                    }
                }else{
                    int n = msgp->getNoteNumber();
                    if(n < split1){
                        msgp->setNoteNumber(drum1);
                    }else if(n > split2){
                        msgp->setNoteNumber(drum3);
                    }else{
                        msgp->setNoteNumber(drum2);
                    }
                    if(drummode == 1){
                        //Move to Ch. 10 (0x9)
                        msgp->setChannel(10);
                        mtracks[0x9]->addEvent(*msgp);
                        mtracks[channel]->deleteEvent(m, false);
                        --m;
                    }
                }
            }
        }
    }
    dbgmsg("Finishing MIDI...");
    //Ensure messages are in order (again)
    for(channel=0; channel<16; channel++){
        mtracks.set(channel, ensureSimulMsgsInOrder(*mtracks[channel]), true);
    }
    //Combine into MIDI file
    ret->addTrack(mastertrack);
    for(channel=0; channel<16; channel++){
        ret->addTrack(*mtracks[channel]);
    }
    dbgmsg("====== DONE ======");
    return ret;
}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////// importCom functions /////////////////////////////
////////////////////////////////////////////////////////////////////////////////


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
            dbgmsg("Pointer to section @" + hex(a,4) + " from stype " 
                    + String(stype) + " to stype " + String(sections[s]->stype) + "!");
        }
        return true;
    }
    return false;
}
SeqData* SeqFile::getSection(int s){
    if(s < 0 || s >= sections.size()) return nullptr;
    return sections[s];
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// importCom objects //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Array<uint8> data;

uint8 SeqFile::readByte(uint32 address){
    return data[address];
}
void SeqFile::writeByte(uint32 address, uint8 d){
    data.set(address, d);
}
uint32 SeqFile::getLength(){
    return data.size();
}


struct SeqData{
    SeqData();

    uint32 address;
    uint32 address_end;
    int8 stype;
    int8 channel;
    int8 layer;
    int8 calldepth;
    int8 finished;
    int16 tsection;
    Array<uint32> cmdoffsets;
};

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

OwnedArray<SeqData> sections;


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// importCom //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool SeqFile::load(ROM& rom, int seqnumber){
    //if(rom.byteOrdering != ROM::ABCD && ((seqaddr & 0x00000003) || (length & 0x00000003))){
    //    dbgmsg("Byte-swapped ROM with non-word-aligned data... this will end poorly!");
    //}
    //Get file and index properties from RomDesc
    ValueTree asiinfonode = romdesc.getChildWithName("knownfilelist")
            .getChildWithProperty("type", "Audioseq Index");
    if(!asiinfonode.isValid()){
        dbgmsg("Audioseq Index not defined in RomDesc!");
        return false;
    }
    uint32 asiaddr = (int)asiinfonode.getProperty("address");
    if(asiaddr >= rom.getSize()){
        dbgmsg("Audioseq Index at invalid index " + hex(asiaddr) + "!");
        return false;
    }
    ValueTree asinfonode = romdesc.getChildWithName("knownfilelist")
            .getChildWithProperty("type", "Audioseq");
    if(!asinfonode.isValid()){
        dbgmsg("Audioseq not defined in RomDesc!");
        return false;
    }
    uint32 asaddr = (int)asinfonode.getProperty("address");
    if(asaddr >= rom.getSize()){
        dbgmsg("Audioseq at invalid index " + hex(asaddr) + "!");
        return false;
    }
    //Get sequence properties from index
    uint32 seqaddr, seqlen;
    if((int)romdesc.getProperty("indextype", 1) == 2){
        seqaddr = asaddr + rom.readWord(asiaddr + (16*seqnumber) + 16);
        seqlen = rom.readWord(asiaddr + (16*seqnumber) + 20);
    }else{
        seqaddr = asaddr + rom.readWord(asiaddr + (8*seqnumber) + 4);
        seqlen = rom.readWord(asiaddr + (8*seqnumber) + 8);
    }
    if(seqlen >= 10000000){
        dbgmsg("Trying to load sequence more than 10MB! Probably wrong!");
        return false;
    }
    //Actually load sequence
    dbgmsg("Loading sequence file from " + hex(seqaddr) + " length " + hex(seqlen));
    data.ensureStorageAllocated(seqlen);
    for(int i=0; i<seqlen; i++){
        data.add(rom.readByte(i+seqaddr));
    }
    dbgmsg("Copied ROM data to sequence, size == " + hex((uint32)data.size()));
    trim();
    /*
    TODO bank integration
    //Try to load bank number
    bank_num = -1;
    ValueTree sbminfonode = romdesc.getChildWithName("knownfilelist")
            .getChildWithProperty("type", "Sequence Banks Map");
    do{
        if(!sbminfonode.isValid()){
            dbgmsg("No Sequence Banks Map defined in RomDesc, cannot load bank");
            break;
        }
        uint32 sbmaddr = (int)sbminfonode.getProperty("address");
        if(sbmaddr >= rom.getSize()){
            dbgmsg("Invalid Sequence Banks Map in RomDesc " + hex(sbmaddr) + ", cannot load bank");
            break;
        }
        //Read bank number
        uint16 ptr = rom.readHalfWord(sbmaddr + (seqnumber << 1));
        uint8 seq_isetcount = rom.readByte(sbmaddr + ptr);
        if(seq_isetcount == 0){
            dbgmsg("Sequence has no banks, cannot load bank");
            break;
        }
        if(seq_isetcount > 1){
            dbgmsg(
                    "========================== PLEASE NOTE ============================\n"
                    "This sequence uses more than one bank.\n"
                    "By default the first one will be used for MIDI export--\n"
                    "if you want to use a different one, change them in the Sequence Banks\n"
                    "section of the Files Pane.");
        }
        bank_num = rom.readByte(sbmaddr + ptr + 1);
    }while(false);
    */
    //Before we leave
    parse();
    return true;
}

bool SeqFile::loadRaw(File file){
    int len = file.getSize();
    if(!file.existsAsFile() || len <= 0){
        dbgmsg("File " + file.getFullPathName() + " doesn't exist!");
        return false;
    }
    if(len > 1000000){
        dbgmsg("File " + file.getFullPathName() + " is more than 1MB, probably not a sequence!");
        return false;
    }
    FileInputStream fis(file);
    if(fis.failedToOpen()){
        dbgmsg("Couldn't open file " + file.getFullPathName() + "!");
        return false;
    }
    dbgmsg("Loading " + String(len) + " bytes to sequence from " + file.getFullPathName());
    data.clear();
    data.ensureStorageAllocated(len);
    for(int i=0; i<len; ++i){
        data.add(fis.readByte());
    }
    name = file.getFileNameWithoutExtension();
    dbgmsg("Successfully loaded raw sequence");
    parse();
    return true;
}

void SeqFile::parse(){
    sections.clear();
    dbgmsg("Sequence starts with " 
            + hex(data[0]) + hex(data[1]) + hex(data[2]) + hex(data[3])
            + hex(data[4]) + hex(data[5]) + hex(data[6]) + hex(data[7]));
    ValueTree command, param;
    String action, meaning;
    int cmdlen = 1, channel = -1, notelayer = -1, value;
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
    dbgmsg("Parsing Sequence");
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
                        dbgmsg("@" + hex(a,4) + ": ran into branch destination (normal)");
                    }else{
                        dbgmsg("@" + hex(a,4) + ": reading section ran into start of previously-jumped-to section of DIFFERENT type!");
                    }
                    sections.remove(value);
                    value--;
                }else{
                    dbgmsg("@" + hex(a,4) + ": reading section ran into start of already-read data!");
                }
            }else{
                dbgmsg("@" + hex(a,4) + ": reading section lawnmowed across start of existing section!");
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
                    dbgmsg("Finished parsing sequence");
                    return;
                }
                //Finish this section
                sec = sections[value];
                a = sec->address;
                stype = sec->stype;
                channel = sec->channel;
                notelayer = sec->layer;
                dbgmsg("Finishing unfinished section @" + hex(a,4));
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
            dbgmsg("Jump Same Level @" + hex(a,4) + " to @" + hex(address,4), false);
            if(address <= a && address >= sec->address){
                //Pointer is to earlier in the current section
                dbgmsg("...earlier in same section");
                continue;
            }
            //Make a new section, but don't jump to it
            dbgmsg("...making new section for later");
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
                dbgmsg("FATAL: Stack Overflow SeqFile::parse()!");
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
                dbgmsg("@" + hex(a,4) + ": Ptr Channel Header from something other than seq header!");
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
                dbgmsg("Ptr Channel Header with channel >= 16!");
                continue;
            }
            //Jump to new address
            sec->address_end = a;
            addrstack[stackptr] = a;
            stypestack[stackptr] = stype;
            sectionstack[stackptr] = sec;
            stackptr++;
            if(stackptr >= stack_size){
                dbgmsg("FATAL: Stack Overflow SeqFile::parse()!");
                break;
            }
            a = address;
            stype = 1;
            sec = getOrMakeSectionAt(a);
            sec->stype = 1;
            sec->channel = channel;
        }else if(action == "Ptr Track Data"){
            if(stype != 1){
                dbgmsg("@" + hex(a,4) + ": Ptr Track Data from something other than a channel!");
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
                dbgmsg("Ptr Track Data with no note layer value!");
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
                dbgmsg("FATAL: Stack Overflow SeqFile::parse()!");
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
            dbgmsg("Unknown command action " + action + "!");
        }
    }
    dbgmsg("Parsing sequence ran off end! a==" + hex(a) + ", length==" + hex((uint32)data.size()));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// exportCom functions /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

 //Overwrite whatever is at address, don't resize
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
                dbgmsg("Variable datalen only supported with length 1 or 2!");
            }
        }else{
            dbgmsg("Unknown datasrc: " + datasrc);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// exportCom //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void SeqFile::render(){
    dbgmsg("Rendering sequence structure to binary data...");
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
    int ptraddr = -1, ptrsec, ptrhash, cmd2;
    ValueTree section2, command2, param;
    for(sec=0; sec<structure.getNumChildren(); sec++){
        //dbgmsg("----Section " + String(sec));
        section = structure.getChild(sec);
        for(cmd=0; cmd<section.getNumChildren(); cmd++){
            command = section.getChild(cmd);
            action = command.getProperty(idAction, "No Action");
            len = command.getProperty(idLength, 1);
            //Get addresses of pointers
            if(command.hasProperty(idTargetSection)){
                ptrsec = command.getProperty(idTargetSection);
                if(ptrsec >= structure.getNumChildren()){
                    dbgmsg("Pointer to undefined section!");
                    importresult |= 2;
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
                            dbgmsg("Could not find command with correct hash!");
                            ptraddr = 0;
                            importresult |= 2;
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
                        dbgmsg("Command had idTargetSection but no parameters with absolute or relative address!");
                        importresult |= 2;
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

bool SeqFile::saveRaw(File file){
    if(!file.hasWriteAccess()){
        dbgmsg("No write access to " + file.getFullPathName() + "!");
        return false;
    }
    if(file.exists()){
        file.deleteFile();
    }
    FileOutputStream fos(file);
    if(fos.failedToOpen()){
        dbgmsg("Couldn't open file " + file.getFullPathName() + " for writing!");
        return false;
    }
    for(int i=0; i<data.size(); ++i){
        fos.writeByte(data[i]);
    }
    fos.flush();
    dbgmsg("Saved " + String(data.size()) + " bytes from sequence to " + file.getFullPathName());
    return true;
}


void SeqFile::saveToROM(ROM& rom, uint32 start_addr){
    dbgmsg("Saving " + hex((uint32)data.size(), 4) + " bytes to sequence @" + hex(start_addr));
    for(int i=0; i<data.size(); i++){
        rom.writeByte(i+start_addr, data[i]);
    }
}

#endif

////////////////////////////////////////////////////////////////////////////////
///////////////////////// No longer used (GUI editing) /////////////////////////
////////////////////////////////////////////////////////////////////////////////

#if 0

void SeqFile::trim(){
    int lastbyte = data.size() - 1;
    for(; lastbyte >= 0; lastbyte--){
        if(data[lastbyte] != 0){
            break;
        }
    }
    lastbyte = (lastbyte & 0xFFFFFFFC) + 4;
    if(lastbyte >= data.size()){
        dbgmsg("SeqFile::trim(): no trim required");
        return;
    }
    dbgmsg("Trimming SeqFile from " + hex((uint32)data.size(), 4) + " to " + hex((uint32)lastbyte, 4) + " bytes");
    data.removeRange(lastbyte, data.size() - lastbyte);
}

int SeqFile::getNumSections(){
    return sections.size();
}


String SeqFile::getSectionDescription(int s){
    if(s < 0 || s >= sections.size()) return "";
    SeqData* sec = sections[s];
    String ret = "@" + hex(sec->address, 4) + ": ";
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
        ret += hex(data[a+i]) + " ";
    }
    ret = ret.paddedRight(' ', 15);
    ret = "@" + hex(a, 4) + ": " + ret;
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
        dbgmsg("Asked to remove data with invalid size " + String(size) + "!");
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
            dbgmsg("Address command parameters must be fixed-length! (in " + action + ")");
            return;
        }
        int oldvalue = (int)param.getProperty(idValue, 0);
        if(oldvalue >= daddr){
            if(oldvalue == daddr && addrOfChangeSection == daddr){
                return; //Leave pointer
            }
            int newvalue = oldvalue + dsize;
            int datalen = (int)param.getProperty(idDataLen, 1);
            //Check out-of-range
            if(newvalue < 0 || newvalue >= (1 << (datalen << 3))){ //8-bit for one, 16-bit for two...
                dbgmsg("Absolute address pointer going out-of-range @" + hex(cmdaddr,4) 
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
            dbgmsg("Address command parameters must be fixed-length! (in " + action + ")");
            return;
        }
        int oldvalue = (int)param.getProperty(idValue, 0);
        //dbgmsg("Relative address value @" + hex(cmdaddr,4) + " parsed to " + String(oldvalue));
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
            dbgmsg("Relative address pointer going out-of-range @" + hex(cmdaddr,4) 
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
    dbgmsg("Editing command parameter @" + hex(address,4) + " stype " + String(stype) + " " + meaning + " to " + hex((uint32)newvalue));
    int ret = 0;
    ValueTree command = getCommand(address, stype);
    ValueTree param = command.getChildWithProperty(idMeaning, meaning);
    if(!param.isValid()){
        dbgmsg("Error: asked to edit command parameter with meaning " + meaning + ", does not exist!");
        return -1;
    }
    int value = param.getProperty(idValue, 0);
    if(newvalue == value) return 0;
    uint32 a = address + (int)param.getProperty(idDataAddr, 1);
    String datasrc = param.getProperty(idDataSrc, "fixed");
    int datalen = param.getProperty(idDataLen, 1);
    //int dataactuallen = param.getProperty(idDataActualLen, 1);
    if(datasrc == "offset"){
        ValueTree desc = getDescription(data[address], stype);
        int cmdbegin = desc.getProperty(idCmd, 0);
        int cmdend = desc.getProperty(idCmdEnd, cmdbegin);
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
            dbgmsg("Due to SeqFile variable length format, length > 2 not defined!");
            return -1;
        }
    }else{
         dbgmsg("Invalid command description! datasrc == " + datasrc);
         return -1;
    }
    return ret;
}
bool SeqFile::swapCommands(int sectionidx, int firstcmdidx){
    SeqData* section = getSection(sectionidx);
    if(firstcmdidx <= 0 || firstcmdidx >= section->cmdoffsets.size() - 1) return false;
    //Get commands
    uint32 cmdaddr_1 = section->cmdoffsets[firstcmdidx];
    uint32 cmdaddr_2 = section->cmdoffsets[firstcmdidx+1];
    ValueTree cmd_1 = getCommand(cmdaddr_1, section->stype);
    ValueTree cmd_2 = getCommand(cmdaddr_2, section->stype);
    uint32 len_1 = (int)cmd_1.getProperty("length", 1);
    uint32 len_2 = (int)cmd_2.getProperty("length", 1);
    if(len_1 != (cmdaddr_2 - cmdaddr_1)){
        dbgmsg("Difference in address between commands not equal to first command's length!");
        return false;
    }
    //Edit command relative addresses
    for(int p=0; p<cmd_1.getNumChildren(); ++p){
        ValueTree param = cmd_1.getChild(p);
        if(param.getProperty("meaning", "None") == "Relative Address"){
            editCmdParam(sectionidx, cmdaddr_1, section->stype, "Relative Address",
                (int)param.getProperty("value", 0) - len_1);
        }
    }
    for(int p=0; p<cmd_2.getNumChildren(); ++p){
        ValueTree param = cmd_2.getChild(p);
        if(param.getProperty("meaning", "None") == "Relative Address"){
            editCmdParam(sectionidx, cmdaddr_2, section->stype, "Relative Address",
                (int)param.getProperty("value", 0) + len_1);
        }
    }
    //Swap commands
    uint32 s, d;
    for(s=cmdaddr_1, d=cmdaddr_2+len_2; s<cmdaddr_2; ++s, ++d){
        data.insert(d, data[s]);
    }
    for(s=0; s<len_1; ++s){
        data.remove(cmdaddr_1);
    }
    //Done
    parse();
    return true;
}

void SeqFile::insertCommand(int section, int cmdidx, ValueTree command){
    if(!command.isValid()) return;
    //dbgmsg("Writing command " + command.getProperty(idAction).toString() + " section " 
    //        + String(section) + " index " + String(cmdidx));
    if(section >= sections.size() || section < 0){
        dbgmsg("Invalid section " + String(section));
        return;
    }
    SeqData* sec = sections[section];
    //int address_start = sec->address;
    ValueTree param;
    String datasrc;
    //Get address to insert command at
    uint32 address;
    //bool insertAtEnd = false;
    if(cmdidx < sec->cmdoffsets.size() && cmdidx >= 0){
        address = sec->cmdoffsets[cmdidx];
    }else{
        cmdidx = sec->cmdoffsets.size();
        address = sec->address_end;
        //insertAtEnd = true;
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
        dbgmsg("Invalid section " + String(section));
        return;
    }
    SeqData* sec = sections[section];
    if(cmdidx >= sec->cmdoffsets.size() || cmdidx < 0){
        dbgmsg("Invalid command " + String(section));
        return;
    }
    uint32 address = sec->cmdoffsets[cmdidx];
    ValueTree command = getCommand(address, sec->stype);
    int cmdlen = command.getProperty(idLength, 1);
    //Delete the cmdoffset
    sec->cmdoffsets.remove(cmdidx);
    //Delete the data
    removeData(address, cmdlen, section);
}



#endif
