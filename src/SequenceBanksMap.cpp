/*
 * ============================================================================
 *
 * SequenceBanksMap.cpp
 * Sequence Banks Map (list of all banks for each sequence) manipulation
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

#include "SequenceBanksMap.h"
#include "seq64.h"

SequenceBanksMap::SequenceBanksMap(ROM &rom_, ValueTree &romdesc_, IndexedFile &audioseq_) 
        : rom(rom_), romdesc(romdesc_), audioseq(audioseq_), filePropsOkay(false) {}
SequenceBanksMap::~SequenceBanksMap() {}

bool SequenceBanksMap::reloadFileProps(){
	filePropsOkay = false;
    ValueTree kfilelistnode = romdesc.getOrCreateChildWithName("knownfilelist", nullptr);
    ValueTree sbmnode = kfilelistnode.getChildWithProperty("type", "Sequence Banks Map");
    if(!sbmnode.isValid()) return false;
    sbmaddr = (int)sbmnode.getProperty("address", -1);
    if(sbmaddr <= 0 || sbmaddr >= rom.getSize()) return false;
    int seqcount = audioseq.getICount();
	if(seqcount <= 0 || seqcount > 1000) return false;
	//Get data end
	sbmdataend = 0;
	for(int s=0; s<seqcount; ++s){
		uint16 ptr = rom.readHalfWord(sbmaddr + (s << 1));
		uint8 nbanks = rom.readByte(sbmaddr + ptr);
		uint32 dend = sbmaddr + ptr + nbanks + 1;
		if(dend > sbmdataend) sbmdataend = dend;
	}
	//Get real end
	sbmrealend = IndexedFile::getRealEnd(rom, sbmdataend);
	if((int)sbmnode.getProperty("length", -1) != sbmrealend - sbmaddr){
	    SEQ64::say("Updating SequenceBanksMap length to " + ROM::hex(sbmrealend - sbmaddr));
	}
	sbmnode.setProperty("length", (int)(sbmrealend - sbmaddr), nullptr);
	filePropsOkay = true;
	return true;
}

int SequenceBanksMap::getSeqNumBanks(int seqidx){
    if(!filePropsOkay) return -1;
    if(seqidx < 0 || seqidx >= audioseq.getICount()) return -1;
    uint16 ptr = rom.readHalfWord(sbmaddr + (seqidx << 1));
    int nbanks = rom.readByte(sbmaddr + ptr);
    if(nbanks == 0){
        SEQ64::say("Warning, sequence " + String(seqidx) + " has 0 banks, crashes likely!");
    }
    return nbanks;
}

int SequenceBanksMap::getSeqBank(int seqidx, int bankidx){
    if(!filePropsOkay) return -1;
    if(seqidx < 0 || seqidx >= audioseq.getICount()) return -1;
    uint16 ptr = rom.readHalfWord(sbmaddr + (seqidx << 1));
    uint8 nbanks = rom.readByte(sbmaddr + ptr);
    if(nbanks == 0){
        SEQ64::say("Warning, sequence " + String(seqidx) + " has 0 banks, crashes likely!");
    }
    if(bankidx < 0 || bankidx >= nbanks) return -1;
    return rom.readByte(sbmaddr + ptr + bankidx + 1);
}
bool SequenceBanksMap::setSeqBank(int seqidx, int bankidx, int bank){
    if(!filePropsOkay) return false;
    if(seqidx < 0 || seqidx >= audioseq.getICount()) return false;
    uint16 ptr = rom.readHalfWord(sbmaddr + (seqidx << 1));
    uint8 nbanks = rom.readByte(sbmaddr + ptr);
    if(nbanks == 0){
        SEQ64::say("Warning, sequence " + String(seqidx) + " has 0 banks, crashes likely!");
    }
    if(bankidx < 0 || bankidx >= nbanks) return false;
    rom.writeByte(sbmaddr + ptr + bankidx + 1, bank & 0xFF);
    return true;
}

//
    
bool SequenceBanksMap::canAddBank(int seqidx){
    if(!filePropsOkay) return false;
    if(sbmrealend - sbmdataend < 1) return false;
    if(getSeqNumBanks(seqidx) == 0xFF) return false;
    return true;
}

bool SequenceBanksMap::canAddSeq(){
    if(!filePropsOkay) return false;
    if(sbmrealend - sbmdataend < 4) return false;
    return true;
}

bool SequenceBanksMap::addBank(int seqidx, int bankidx, int bank){
    if(!canAddBank(seqidx)) return false;
    uint16 nextptr = rom.readHalfWord(sbmaddr + ((seqidx+1)<<1)); //Old value of next seq's ptr
    //Adjust addresses for later seqs
    for(int s=seqidx+1; s<audioseq.getICount(); ++s){
        rom.writeHalfWord(sbmaddr + (s<<1), rom.readHalfWord(sbmaddr + (s<<1)) + 1);
    }
    //Move later data
    uint8* d = &((uint8*)rom.getData())[sbmaddr + nextptr];
    memmove(d+1, d, sbmdataend - (sbmaddr + nextptr));
    ++sbmdataend;
    //Change count
    uint16 thisptr = rom.readHalfWord(sbmaddr + (seqidx << 1));
    uint8 newcount = rom.readByte(sbmaddr + thisptr) + 1;
    rom.writeByte(sbmaddr + thisptr, newcount);
    //Add new bank
    if(bankidx >= 0 && bankidx < newcount-1){
        //Inserting
        d = &((uint8*)rom.getData())[sbmaddr + thisptr];
        memmove(d+2+bankidx, d+1+bankidx, newcount - 1 - bankidx);
        rom.writeByte(sbmaddr + thisptr + 1 + bankidx, bank);
    }else{
        //Adding at end
        rom.writeByte(sbmaddr + thisptr + newcount, bank);
    }
    return true;
}

bool SequenceBanksMap::addSeq(int seqidx){
    if(!canAddSeq()) return false;
    //Get pointer where new seq will be
    uint16 ptr;
    if(seqidx < audioseq.getICount()-1){ //The seq was already added to Audioseq, so the count here is the new number of sequences
        //The new seq was added in the middle
        ptr = rom.readHalfWord(sbmaddr + (seqidx<<1));
    }else if(seqidx == audioseq.getICount()-1){
        //The new seq was added at the end
        ptr = sbmdataend - sbmaddr;
    }else{
        return false;
    }
    //Adjust all seqs' addresses for additional pointer
    for(int s=0; s<audioseq.getICount()-1; ++s){
        rom.writeHalfWord(sbmaddr + (s<<1), rom.readHalfWord(sbmaddr + (s<<1)) + 2);
    }
    ptr += 2;
    //Adjust later seqs' addresses for additional 2 byte data
    for(int s=seqidx; s<audioseq.getICount()-1; ++s){
        rom.writeHalfWord(sbmaddr + (s<<1), rom.readHalfWord(sbmaddr + (s<<1)) + 2);
    }
    //Move later addresses and all data for additional pointer
    uint8* d = &((uint8*)rom.getData())[sbmaddr];
    memmove(&d[(seqidx<<1)+2], &d[seqidx<<1], sbmdataend - sbmaddr - (seqidx<<1));
    sbmdataend += 2;
    rom.writeHalfWord(sbmaddr + (seqidx<<1), ptr);
    //Move later data for new data
    memmove(&d[ptr+2], &d[ptr], sbmdataend - sbmaddr - ptr);
    sbmdataend += 2;
    rom.writeByte(sbmaddr + ptr, 1); //number of banks
    rom.writeByte(sbmaddr + ptr + 1, 0); //bank number
    return true;
}

//

bool SequenceBanksMap::canRemoveBank(int seqidx, int bankidx){
    if(!filePropsOkay) return false;
    if(seqidx < 0 || seqidx >= audioseq.getICount()) return false;
    int nbanks = getSeqNumBanks(seqidx);
    if(bankidx < 0 || bankidx >= nbanks || nbanks == 1) return false;
    return true;
}

bool SequenceBanksMap::canRemoveSeq(int seqidx, bool seqAlreadyRemovedFromAudioseq){
    if(!filePropsOkay) return false;
    if(seqidx < 0 || seqidx >= audioseq.getICount() + (seqAlreadyRemovedFromAudioseq ? 1 : 0)) return false;
    return true;
}

bool SequenceBanksMap::removeBank(int seqidx, int bankidx){
    if(!canRemoveBank(seqidx, bankidx)) return false;
    uint16 nextptr = rom.readHalfWord(sbmaddr + ((seqidx+1)<<1)); //Old value of next seq's ptr
    //Adjust addresses for later seqs
    for(int s=seqidx+1; s<audioseq.getICount(); ++s){
        rom.writeHalfWord(sbmaddr + (s<<1), rom.readHalfWord(sbmaddr + (s<<1)) - 1);
    }
    //Change count
    uint16 thisptr = rom.readHalfWord(sbmaddr + (seqidx << 1));
    uint8 newcount = rom.readByte(sbmaddr + thisptr) - 1;
    rom.writeByte(sbmaddr + thisptr, newcount);
    //Shift banks list
    uint8* d = &((uint8*)rom.getData())[sbmaddr + thisptr];
    if(bankidx >= 0 && bankidx < newcount){
        //Removing from middle
        memmove(d+1+bankidx, d+2+bankidx, newcount - bankidx);
    }else{
        //Removing from end
        //do nothing, will get overwritten
    }
    //Move later data
    d = &((uint8*)rom.getData())[sbmaddr + nextptr];
    memmove(d-1, d, sbmdataend - (sbmaddr + nextptr));
    --sbmdataend;
    rom.writeByte(sbmdataend, 0);
    return true;
}

bool SequenceBanksMap::removeSeq(int seqidx){
    if(!canRemoveSeq(seqidx, true)) return false;
    //Get current params
    uint16 ptr = rom.readHalfWord(sbmaddr + (seqidx<<1));
    uint8 nbanks = rom.readByte(sbmaddr + ptr);
    if(nbanks == 0){
        SEQ64::say("Warning, sequence " + String(seqidx) + " has 0 banks, crashes likely!");
    }
    //Adjust all seqs' addresses for one less pointer
    for(int s=0; s<=audioseq.getICount(); ++s){ //The seq was already removed from Audioseq, so the count here is the new number of sequences
        rom.writeHalfWord(sbmaddr + (s<<1), rom.readHalfWord(sbmaddr + (s<<1)) - 2);
    }
    //Adjust later seqs' addresses for less data
    for(int s=seqidx+1; s<=audioseq.getICount(); ++s){
        rom.writeHalfWord(sbmaddr + (s<<1), rom.readHalfWord(sbmaddr + (s<<1)) - 1 - nbanks);
    }
    //Move later addresses and all data for removed pointer
    uint8* d = &((uint8*)rom.getData())[sbmaddr];
    memmove(&d[seqidx<<1], &d[(seqidx<<1)+2], sbmdataend - sbmaddr - (seqidx<<1) - 2);
    sbmdataend -= 2;
    rom.writeByte(sbmdataend, 0);
    rom.writeByte(sbmdataend+1, 0);
    ptr -= 2;
    //Move later data for removed data
    memmove(&d[ptr], &d[ptr+nbanks+1], sbmdataend - sbmaddr - ptr - nbanks - 1);
    sbmdataend -= 1+nbanks;
    for(int i=0; i<=nbanks; ++i) rom.writeByte(sbmdataend+i, 0);
    return true;
}




    