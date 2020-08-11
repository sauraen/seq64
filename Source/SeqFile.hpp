/*
 * ============================================================================
 *
 * SeqFile.hpp
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

#pragma once

#include "Common.hpp"

class SeqFile{
public:
    SeqFile(ValueTree abi_);
    ~SeqFile();
    
    static StringArray getAvailABIs();
    static ValueTree loadABI(String name);
    
    //Import results are 0 okay, 1 warnings, 2+ errors.
    
    int importMIDI(File midifile, ValueTree midiopts);
    #if 0
    void exportMIDI(File midifile, ValueTree midiopts);
    int importMus(File musfile, int dialect);
    void exportMus(File musfile, int dialect);
    int importCom(File comfile);
    void exportCom(File comfile);
    #endif
    
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
    
    #if 0
    //For exportMIDI
    ValueTree getDescription(uint8 firstbyte, int stype); //Stype: 0 seq hdr, 1 chn hdr, 2 track data
    ValueTree getCommand(uint32 address, int stype);
    int getAdjustedValue(const ValueTree& param);
    int getPtrAddress(ValueTree command, uint32 currentAddr);
    
    //For importCom
    SeqData* getOrMakeSectionAt(uint32 a);
    bool isSectionAt(uint32 a, int stype);
    SeqData* getSection(int s);
    
    //For exportCom
    void writeCommand(uint32 address, ValueTree command);
    #endif
    
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
    static Identifier idAddress;
    static Identifier idAddressEnd;
    static Identifier idHash;
    static Identifier idTargetSection;
    static Identifier idTargetHash;
    static Identifier idWillDrop;
    
};
