/*
  ==============================================================================

    BankFile.h
    Created: 2 Jan 2015 9:03:51pm
    Author: Sauraen

  ==============================================================================
*/

#ifndef BANKFILE_H_INCLUDED
#define BANKFILE_H_INCLUDED

#include "ROM.h"


class BankFile {
    public:
    ValueTree d; //Data
    
    BankFile(ValueTree romdesc);
    void reset();
    
    //Returns number of bytes read/written
    int readStruct(ROM& rom, uint32 addr, ValueTree stru); //stru has been just copied from the template
    int writeStruct(ROM& rom, uint32 addr, ValueTree stru);
    
    ValueTree getCopyOfTemplate(String name);
    void loadElementList(ROM& rom, uint32 baseaddr, int bank_length, String listname, String elementname);
    void checkAddListItem(String listname, int addressval, ValueTree node);
    
    void load(ROM& rom, uint32 abientryaddr, uint32 abfaddr);
    void save(ROM& rom, uint32 abientryaddr, uint32 abfaddr);
    
    int getLength();
    int getLength(ValueTree stru);
    
    private:
    
    ValueTree abfstructsnode;
    
    int NUM_INST;
    int NUM_DRUM;
    int NUM_SFX;
    int NUM_BANK;
    int SSIindex;
};



#endif  // BANKFILE_H_INCLUDED
