/*
 * ============================================================================
 *
 * SequenceBanksMap.h
 * Sequence Banks Map (list of all banks for each sequence) manipulation
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

#ifndef SEQUENCEBANKSMAP_H_INCLUDED
#define SEQUENCEBANKSMAP_H_INCLUDED

#include "JuceHeader.h"
#include "ROM.h"
#include "IndexedFile.h"

class SequenceBanksMap {
public:
    SequenceBanksMap(ROM &rom_, ValueTree &romdesc_, IndexedFile &audioseq_);
    ~SequenceBanksMap();
    bool reloadFileProps();
    
    int getSeqNumBanks(int seqidx);
    int getSeqBank(int seqidx, int bankidx);
    bool setSeqBank(int seqidx, int bankidx, int bank);
    
    bool canAddBank(int seqidx);
    bool canAddSeq();
    bool addBank(int seqidx, int bankidx, int bank);
    bool addSeq(int seqidx);
    
    bool canRemoveBank(int seqidx, int bankidx);
    bool canRemoveSeq(int seqidx, bool seqAlreadyRemovedFromAudioseq = false);
    bool removeBank(int seqidx, int bankidx);
    bool removeSeq(int seqidx);
    
private:
    ROM &rom;
    ValueTree &romdesc;
	IndexedFile &audioseq;
	bool filePropsOkay;
    
    uint32 sbmaddr;
    uint32 sbmdataend, sbmrealend;
};



#endif  // SEQUENCEBANKSMAP_H_INCLUDED
