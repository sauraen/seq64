/*
  ==============================================================================

    SeqFile.h
    Created: 1 Nov 2014 12:01:52pm
    Author:  Sauraen

  ==============================================================================
*/

#ifndef SEQFILE_H_INCLUDED
#define SEQFILE_H_INCLUDED

#include "ROM.h"


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
    String name;
    
    SeqFile(ROM& rom, ValueTree romdesc, uint32 seqaddr, uint32 length);
    SeqFile(ValueTree romdesc);
    ~SeqFile();
    uint32 getLength();
    uint8 readByte(uint32 address);
    void writeByte(uint32 address, uint8 d);
    void saveToROM(ROM& rom, uint32 start_addr);
    
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
    
    ValueTree wantAction(String action, int stype);
    void wantProperty(ValueTree want, String meaning, int value);
    ValueTree createCommand(ValueTree want);
    ValueTree createMarker();
    int getNewCommandLength(ValueTree command); //For a command that was just created, not one read from an existing sequence
    void writeCommand(uint32 address, ValueTree command); //Overwrite whatever is at address, don't resize
    void insertCommand(int section, int cmdidx, ValueTree command);
    void deleteCommand(int section, int cmdidx);
    
    MidiFile* toMIDIFile();
    
    void fromMidiFile(MidiFile& mfile);
    bool isCloseEnough(ValueTree command1, ValueTree command2);
    void optimize();
    void reduceTrackNotes();
    void render();
    
    private:
    Array<uint8> data;
    ValueTree structure;
    
    ValueTree cmdlist;
    ValueTree midiopts;
    
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
