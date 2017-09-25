/*
 * ============================================================================
 *
 * SeqFile.h
 * Class to hold/import/export a Nintendo EAD (Audioseq) format sequence file
 * 
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2017 Sauraen
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

#ifndef SEQFILE_H_INCLUDED
#define SEQFILE_H_INCLUDED

#include "JuceHeader.h"
#include "seq64.h"

class ROM;
class BankFile;

class SeqTSection{
    public:
	SeqTSection();

    uint32 time;
    uint32 address;
    uint32 address_end;
};

class SeqData{
    public:
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

class CCTracker{
    public:
    CCTracker();
    
    String action;
    int q_time;
    int lasttime;
    int q_amp;
    int lastvalue;
};


class SeqFile{
    public:
    SeqFile(ValueTree romdesc_);
    ~SeqFile();
    
    uint32 getLength();
    uint8 readByte(uint32 address);
    void writeByte(uint32 address, uint8 d);
    
    bool load(ROM& rom, int seqnumber);
    void saveToROM(ROM& rom, uint32 start_addr);
    bool loadRaw(File file);
    bool saveRaw(File file);
    
    void trim();
    void parse();
    int getNumSections();
    SeqData* getSection(int s);
    String getSectionDescription(int s);
    String getCommandDescription(int s, int c);
    
    ValueTree getDescription(uint8 firstbyte, int stype); //Stype: 0 seq hdr, 1 chn hdr, 2 track data
    ValueTree getCommand(uint32 address, int stype);
    int getAdjustedValue(const ValueTree& param);
    int getPtrAddress(ValueTree command, uint32 currentAddr);
    SeqData* getOrMakeSectionAt(uint32 a);
    bool isSectionAt(uint32 a, int stype);
    int getCommandRange(ValueTree command, String meaning);
    
    void insertSpaceAt(uint32 address, int size, int enlargeSection); //If inserting at a section boundary, enlargeSection controls which section gets the new data
    void removeData(uint32 address, int size, int shrinkSection);
    void editCmdPointer(uint32 cmdaddr, int stype, uint32 daddr, int dsize, int addrOfChangeSection);
    int editCmdParam(int section, uint32 address, int stype, String meaning, int newvalue); //0 okay, -1 failed, 1 structure changed
    bool swapCommands(int sectionidx, int firstcmdidx);
    
    ValueTree wantAction(String action, int stype);
    void wantProperty(ValueTree want, String meaning, int value);
    ValueTree createCommand(ValueTree want);
    ValueTree createMarker();
    int getNewCommandLength(ValueTree command); //For a command that was just created, not one read from an existing sequence
    void writeCommand(uint32 address, ValueTree command); //Overwrite whatever is at address, don't resize
    void insertCommand(int section, int cmdidx, ValueTree command);
    void deleteCommand(int section, int cmdidx);
    
    MidiFile* toMIDIFile();
    void deleteSection(int sectodelete);
    void fromMidiFile(MidiFile& mfile);
    bool isCloseEnough(ValueTree command1, ValueTree command2, bool allowCCMerge);
    
    void optimize();
    void reduceTrackNotes();
    void render();
    
    String name;
    
    private:
    Array<uint8> data;
    ValueTree structure;
    
    ValueTree romdesc;
    ValueTree cmdlist;
    ValueTree midiopts;
    
    ScopedPointer<BankFile> bank;
    
    OwnedArray<SeqData> sections;
    
    bool debug;
    
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



#endif  // SEQFILE_H_INCLUDED
