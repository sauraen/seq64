/*
  ==============================================================================

    ROM.cpp
    Created: 1 Nov 2014 12:27:57pm
    Author:  Sauraen

  ==============================================================================
*/

#include "ROM.h"
#include "JuceHeader.h"


//ROM::ROM() {}
ROM::ROM(const size_t initialSize, bool initialiseToZero)
        : MemoryBlock(initialSize, initialiseToZero) {
    byteOrdering = ABCD;
}


uint32 ROM::readWord(uint32 address){
    address = (uint32)((uint32)address & (uint32)0xFFFFFFFC); //Clear lower two bits
    if(address+3 >= getSize()){jassertfalse; return 0;}
    uint32 ret = 0;
    switch(byteOrdering){
    case ABCD:
        ret = (uint8)(*this)[address];
        ret <<= 8;
        ret += (uint8)(*this)[++address];
        ret <<= 8;
        ret += (uint8)(*this)[++address];
        ret <<= 8;
        ret += (uint8)(*this)[++address];
        break;
    case BADC:
        ret = (uint8)(*this)[address+1];
        ret <<= 8;
        ret += (uint8)(*this)[address];
        ret <<= 8;
        ret += (uint8)(*this)[address+3];
        ret <<= 8;
        ret += (uint8)(*this)[address+2];
        break;
    case DCBA:
        address += 3;
        ret = (uint8)(*this)[address];
        ret <<= 8;
        ret += (uint8)(*this)[--address];
        ret <<= 8;
        ret += (uint8)(*this)[--address];
        ret <<= 8;
        ret += (uint8)(*this)[--address];
        break;
    default:
        jassertfalse;
    }
    return ret;
}

uint16 ROM::readHalfWord(uint32 address){
    address = (uint32)((uint32)address & (uint32)0xFFFFFFFE); //Clear lower bit
    if(byteOrdering == DCBA){
        address = (uint32)((uint32)address ^ (uint32)0x00000002); //Flip bit 1
    }
    if(address+1 >= getSize()){jassertfalse; return 0;}
    uint16 ret = 0;
    if(byteOrdering == ABCD){
        ret = (uint8)(*this)[address];
        ret <<= 8;
        ret += (uint8)(*this)[++address];
    }else{
        ret = (uint8)(*this)[++address];
        ret <<= 8;
        ret += (uint8)(*this)[--address];
    }
    return ret;
}

uint8 ROM::readByte(uint32 address){
    if(address >= getSize()){jassertfalse; return 0;}
    if(byteOrdering != ABCD){
        address = (uint32)((uint32)address ^ (uint32)0x00000001); //Flip lower bit
        if(byteOrdering == DCBA){
            address = (uint32)((uint32)address ^ (uint32)0x00000002); //Flip bit 1
        }
    }
    return (uint8)(*this)[address];
}

void ROM::writeWord(uint32 address, uint32 data){
    address = (uint32)((uint32)address & (uint32)0xFFFFFFFC); //Clear lower two bits
    if(address+3 >= getSize()){jassertfalse; return;}
    switch(byteOrdering){
    case ABCD:
        address += 3;
        (*this)[address] = (data & (uint32)0x000000FF);
        data >>= 8;
        (*this)[--address] = (data & (uint32)0x000000FF);
        data >>= 8;
        (*this)[--address] = (data & (uint32)0x000000FF);
        data >>= 8;
        (*this)[--address] = (data & (uint32)0x000000FF);
        break;
    case BADC:
        (*this)[address+2] = (data & (uint32)0x000000FF);
        data >>= 8;
        (*this)[address+3] = (data & (uint32)0x000000FF);
        data >>= 8;
        (*this)[address] = (data & (uint32)0x000000FF);
        data >>= 8;
        (*this)[address+1] = (data & (uint32)0x000000FF);
        break;
    case DCBA:
        (*this)[address] = (data & (uint32)0x000000FF);
        data >>= 8;
        (*this)[++address] = (data & (uint32)0x000000FF);
        data >>= 8;
        (*this)[++address] = (data & (uint32)0x000000FF);
        data >>= 8;
        (*this)[++address] = (data & (uint32)0x000000FF);
        break;
    default:
        jassertfalse;
    }
}

void ROM::writeByte(uint32 address, uint8 data){
    if(address >= getSize()){jassertfalse; return;}
    if(byteOrdering != ABCD){
        address = (uint32)((uint32)address ^ (uint32)0x00000001); //Flip lower bit
        if(byteOrdering == DCBA){
            address = (uint32)((uint32)address ^ (uint32)0x00000002); //Flip bit 1
        }
    }
    (*this)[address] = data;
}

String ROM::getROMName(){
    if(getSize() <= 0x20) return "No name";
    String ret = "";
    char c;
    int a = 0x20;
    while(true){
        c = readByte(a);
        if(c < 0x20 || c >= 0x80) return ret;
        ret += c;
        a++;
    }
}

String ROM::hex(uint32 a, int digits){
    String ret = "";
    int hexit;
    char c;
    for(int count=0; count<digits; count++){
        hexit = a & 0x0000000F;
        (hexit >= 0xA) ? (c = hexit + 0x37) : (c = hexit + 0x30);
        ret = c + ret;
        a >>= 4;
    }
    return ret;
}

String ROM::hex(uint8 a, int digits){
    String ret = "";
    int hexit;
    char c;
    for(int count=0; count<digits; count++){
        hexit = a & 0x0000000F;
        (hexit >= 0xA) ? (c = hexit + 0x37) : (c = hexit + 0x30);
        ret = c + ret;
        a >>= 4;
    }
    return ret;
}
