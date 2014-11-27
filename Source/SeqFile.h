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


class SeqData{
    public:
    uint32 address;
    int8 channel;
    int8 layer;
    int8 calldepth;
    int8 stype;
    Array<uint32> cmdoffsets;
};


class SeqFile{
    public:
    SeqFile(ROM& rom, ValueTree cmdlistnode, uint32 seq_addr, uint32 orig_len);
    SeqFile(ValueTree cmdlistnode);
    ~SeqFile();
    uint32 getStartAddr();
    uint32 getLength();
    uint8 readByte(uint32 address);
    void writeByte(uint32 address, uint8 d);
    
    void parse();
    int getNumSections();
    SeqData* getSection(int s);
    String getSectionDescription(int s);
    String getCommandDescription(int s, int c);
    
    void insertSpaceAt(uint32 address, int size);
    void removeData(uint32 address, int size);
    void editCmdPointer(uint32 cmdaddr, int stype, uint32 daddr, int dsize);
    int editCmdParam(uint32 address, int stype, String meaning, int newvalue); //0 okay, -1 failed, 1 structure changed
    
    MidiFile* toMIDIFile();
    
    ValueTree getDescription(uint8 firstbyte, int stype); //Stype: 0 seq hdr, 1 chn hdr, 2 track data
    ValueTree getCommand(uint32 address, int stype);
    int getAdjustedValue(const ValueTree& param);
    SeqData* getOrMakeSectionAt(uint32 a);
    bool isSectionAt(uint32 a);
    
    String name;
    private:
    ScopedPointer<ROM> data;
    ValueTree cmdlist;
    
    uint32 seqaddr;
    uint32 length;
    
    OwnedArray<SeqData> sections;
    
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
    
};



#endif  // SEQFILE_H_INCLUDED
