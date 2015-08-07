/*
 * ============================================================================
 *
 * BankFile.h
 * Class to hold/import/export a single instrument set (Audiobank format)
 * 
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2015 Sauraen
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

#ifndef BANKFILE_H_INCLUDED
#define BANKFILE_H_INCLUDED

#include "JuceHeader.h"
#include "seq64.h"
#include "ROM.h"


class BankFile {
    public:
    ValueTree d; //Data
    
    BankFile(ValueTree romdesc_);
    void reset();
    
    //Returns number of bytes read/written, -1 on error
    int readStruct(ROM& rom, uint32 addr, ValueTree stru); //stru has been just copied from the template
    int writeStruct(ROM& rom, uint32 addr, ValueTree stru);
    
    ValueTree getCopyOfTemplate(String name);
    void loadElementList(ROM& rom, uint32 baseaddr, int bank_length, String listname, String elementname);
    void checkAddListItem(String listname, int addressval, ValueTree node);
    
    bool load(ROM& rom, int banknum);
    bool save(ROM& rom, int banknum);
    
    int getLength();
    int getLength(ValueTree stru);
    
    private:
    ValueTree romdesc;
    ValueTree abfstructsnode;
    ValueTree rdnamesnode;
    
};



#endif  // BANKFILE_H_INCLUDED
