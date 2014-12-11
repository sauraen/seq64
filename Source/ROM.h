/*
  ==============================================================================

    ROM.h
    Created: 1 Nov 2014 12:27:57pm
    Author:  Sauraen

  ==============================================================================
*/

#ifndef ROM_H_INCLUDED
#define ROM_H_INCLUDED

#include "JuceHeader.h"

class ROM : public MemoryBlock {
    public:
    ROM();
    ROM(const size_t initialSize, bool initialiseToZero=false);
    bool isByteSwapped;
    int cic_index;
    
    uint32 readWord(uint32 address);
    uint16 readHalfWord(uint32 address);
    uint8  readByte(uint32 address);
    
    void writeWord(uint32 address, uint32 data);
    void writeByte(uint32 address, uint8 data);
    
    String getROMName();
    
    void doByteSwap();
    
    static String hex(uint32 a, int digits = 8);
    static String hex(uint8 a, int digits = 2);
};


#endif  // ROM_H_INCLUDED
