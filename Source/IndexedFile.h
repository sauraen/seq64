/*
 * ============================================================================
 *
 * IndexedFile.h
 * Manipulation of indexed files (Audiobank, Audioseq, Audiotable)
 * 
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2018 Sauraen
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

#ifndef INDEXEDFILE_H_INCLUDED
#define INDEXEDFILE_H_INCLUDED

#include "JuceHeader.h"
#include "ROM.h"

class IndexedFile {
public:
    IndexedFile(ROM &rom_, ValueTree &romdesc, String fname);
    ~IndexedFile();
    bool reloadFileProps();
    
    inline const String &getFName() { return fname; }
    inline const String &getIName() { return iname; }
    inline const String &getCName() { return cname; }
    
    inline uint32 getFAddr() { return faddr; }
    inline uint32 getIAddr() { return iaddr; }
    
    inline int16 getICount() { return icount; }
    
    inline bool hasMetadata() { return indextype == 2; }
    
    bool getObjectAddrLen(int o, uint32 &addr_within_file, uint32 &len);
    bool getObjectMetadata(int o, uint32 &md1, uint32 &md2);
    String getObjectName(int o);
    String getObjectDescription(int o);
    bool getObjectRealSize(int o, uint32 &realsize);
    
    bool setObjectAddr(int o, uint32 addr);
    bool setObjectLen(int o, uint32 len);
    bool setObjectMetadata(int o, uint32 md1, uint32 md2);
    bool setObjectName(int o, String name);
    
    bool compact();
    bool makeRoom(int o, uint32 newtotallen);
    
    bool createContents(int o);
    bool destroyContents(int o);
    
    bool addEntry(bool fromInsert = false);
    bool insertEntry(int o);
    bool removeEntry(int o);
    
    static uint32 getRealEnd(ROM &therom, uint32 dataend);
    
private:
    ROM &rom;
    ValueTree &romdesc;
    ValueTree idxlistnode;
    String fname, iname, cname;
    
    int indextype, it_hdrlen, it_entrylen;
    uint32 faddr;
    uint32 fdataend, frealend;
    uint32 iaddr;
    uint32 idataend, irealend;
    int16 icount;
    
    bool warnedOutsideFile, allowOutsideFile;
    
    void invalidateFileProps();
    
    uint32 correctOverzealousRealEnd(uint32 supposedrealend, int o_if_applicable);
    
    int16 readICount(); //This is cached, use getICount()
    void writeICount(int16 count);
    
    bool writeFileLen(uint32 flen);
    void moveRestOfFile(uint32 dstart, int32 delta);
    
    void addBlankName(int idx);
    void fixIndexNames(bool add, int idx);
    
};





#endif  // INDEXEDFILE_H_INCLUDED
