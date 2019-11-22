/*
 * ============================================================================
 *
 * ROM.h
 * MemoryBlock subclass with 8-, 16-, and 32-bit reading/writing functions
 * 
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2019 Sauraen
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

#ifndef ROM_H_INCLUDED
#define ROM_H_INCLUDED

#include "JuceHeader.h"

class ROM : public MemoryBlock {
    public:
    enum BYTEORDERING {
        //Letter A is the most significant byte, letter D is the least significant
        ABCD,
        BADC,
        DCBA
    };
    
    //ROM();
    ROM(const size_t initialSize, bool initialiseToZero=false);
    BYTEORDERING byteOrdering;
    int cic_index;
    
    uint32 readWord(uint32 address);
    uint16 readHalfWord(uint32 address);
    uint8  readByte(uint32 address);
    
    void writeWord(uint32 address, uint32 data);
    void writeHalfWord(uint32 address, uint16 data);
    void writeByte(uint32 address, uint8 data);
    
    uint32 getAddressOfNextData(uint32 startaddress);
    
    String getROMName();
    
    static String hex(uint32 a, int digits = 8);
    static inline String hex(uint8 a, int digits = 2) {return ROM::hex((uint32)a, digits);}
};


#endif  // ROM_H_INCLUDED
