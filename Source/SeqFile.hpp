/*
 * ============================================================================
 *
 * SeqFile.hpp
 * Class to hold/import/export a Nintendo 64 Music Macro Language (Audioseq) 
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

#pragma once

#include "Common.hpp"

class SeqFile{
public:
    SeqFile(ValueTree abi_);
    ~SeqFile();
    
    static StringArray getAvailABIs();
    static ValueTree loadABI(String name);
    static bool saveABI(String name, ValueTree abi_);
    
    //Results are 0 okay, 1 warnings, 2+ errors.
    int importMIDI(File midifile, ValueTree midiopts);
    int exportMIDI(File midifile, ValueTree midiopts);
    #if 0
    int importMus(File musfile, int dialect);
    int exportMus(File musfile, int dialect);
    #endif
    int importCom(File comfile);
    int exportCom(File comfile);
    
    String getInternalString();
    String getDebugOutput();
    
    String name;
    
private:
    //For all
    ValueTree abi;
    ValueTree structure;
    int importresult;
    
    String debug_messages;
    CriticalSection debug_mutex;
    void dbgmsg(String s, bool newline = true);
    
    //For importMIDI
    MidiMessageSequence* ensureSimulMsgsInOrder(MidiMessageSequence &in);
    
    int getCommandRange(ValueTree command, String meaning);
    int getLargestCommandRange(int stype, String action, String meaning);
    bool isCommandValidIn(ValueTree command, int stype);
    
    ValueTree wantAction(String action, int stype);
    void wantProperty(ValueTree want, String meaning, int value);
    ValueTree createCommand(ValueTree want, bool warnIfImpossible = true);
    void advanceToTimestamp(ValueTree section, int stype, int &cmd, int &t, int newt);
    ValueTree createMarker();
    int getNewCommandLength(ValueTree command); //For a command that was just created, not one read from an existing sequence
    
    bool isCloseEnough(ValueTree command1, ValueTree command2, bool allowCCMerge, ValueTree midiopts);
    int getTotalSectionTime(ValueTree section);
    void deleteSection(int sectodelete);
    
    void optimize(ValueTree midiopts);
    void reduceTrackNotes();
    
    //For importCom
    ValueTree getDescription(uint8_t firstbyte, int stype); //Stype: 0 seq hdr, 1 chn hdr, 2 track data
    ValueTree getCommand(Array<uint8_t> &data, uint32_t address, int stype);
    int getPtrAddress(ValueTree command, uint32_t currentAddr, int seqlen);
    
    struct SectionSorter {
        static int compareElements(const ValueTree &first, const ValueTree &second){
            int one = first.getProperty(idAddress, -1);
            int two = second.getProperty(idAddress, -1);
            jassert(one != two && one >= 0 && two >= 0);
            return one - two;
        }
    };

    //For exportCom
    void writeCommand(Array<uint8_t> &data, uint32_t address, ValueTree command);
    
    //Identifiers
    
    static Identifier idName;
    static Identifier idLength;
    static Identifier idAction;
    static Identifier idCmd;
    static Identifier idCmdEnd;
    static Identifier idMeaning;
    static Identifier idValue;
    static Identifier idAdd;
    static Identifier idMultiply;
    static Identifier idDataSrc;
    static Identifier idDataLen;
    static Identifier idDataAddr;
    static Identifier idDataActualLen;
    static Identifier idValidInSeq;
    static Identifier idValidInChn;
    static Identifier idValidInTrk;
    
    static Identifier idSType;
    static Identifier idChannel;
    static Identifier idLayer;
    static Identifier idTSection;
    static Identifier idSection;
    static Identifier idOldSectionIdx;
    static Identifier idAddress;
    static Identifier idAddressEnd;
    static Identifier idHash;
    static Identifier idTargetSection;
    static Identifier idTargetHash;
    static Identifier idWillDrop;
    
};
