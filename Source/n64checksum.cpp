/*
 * N64 Checksum (CRC/CIC) Algorithm
 * All known versions of this code have been released under the GPL
 * 
 * Authors/editors in reverse chronological order (AKA rabbit hole):
 * Modifications (C) 2014 Sauraen, released in seq64
 *     (http://code.google.com/p/seq-64/)
 * Modifications (C) 2005 Parasyte, released in M64ROMExtender1.3b
 *     (http://qubedstudios.rustedlogic.net/Mario64Tools.htm)
 *     (http://www.smwcentral.net/?p=section&a=details&id=4812)
 * Modifications (C) 2002-2004 dbjh, released in ucon64-2.0.0
 *               (C) 1999-2001 NoisyB <noisyb@gmx.net> 
 *     (http://ucon64.sourceforge.net/)
 * Written/RE'd  (C) 1997 Andreas Sterbenz <stan@sbox.tu-graz.ac.at>,
 *     released as chksum64 V1.2 (retrieved from 
 *     https://github.com/DragonMinded/libdragon/blob/master/tools/chksum64.c )
 * Original Code (C) ???? "Nagra"
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
 * 
*************************************************************************
Copyright/Attribution Notice from n64sums.c in M64ROMExtender1.3b,
as downloaded from http://qubedstudios.rustedlogic.net/Mario64Tools.htm
or http://www.smwcentral.net/?p=section&a=details&id=4812 :
*************************************************************************
 * 
 * snesrc - SNES Recompiler
 *
 * Copyright notice for this file:
 *  Copyright (C) 2005 Parasyte
 *
 * Based on uCON64's N64 checksum algorithm by Andreas Sterbenz
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*************************************************************************
Copyright/Attribution Notice from n64.c in ucon64-2.0.0,
as downloaded from http://ucon64.sourceforge.net/ :
*************************************************************************
 * n64.c - Nintendo 64 support for uCON64
 * 
 * Copyright (c) 1999 - 2001 NoisyB <noisyb@gmx.net>
 * Copyright (c) 2002 - 2004 dbjh
 * 
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*************************************************************************
Copyright/Attribution Notice from chksum64.c, as downloaded from
https://github.com/DragonMinded/libdragon/blob/master/tools/chksum64.c :
*************************************************************************
 * chksum64 V1.2, a program to calculate the ROM checksum of Nintendo64 ROMs.
 * Copyright (C) 1997  Andreas Sterbenz (stan@sbox.tu-graz.ac.at)
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*************************************************************************
Statements of original authorship from chksum64.c (same file):
*************************************************************************
  printf("CHKSUM64 V1.2   Copyright (C) 1997 Andreas Sterbenz (stan@sbox.tu-graz.ac.at)\n");
  printf("This program is released under the terms of the GNU public license. NO WARRANTY\n\n");
[...]
  fprintf(stderr, "Usage: %s [-r] [-o|-s] <File>\n\n", progname);
  fprintf(stderr, "This program calculates the ROM checksum for Nintendo64 ROM images.\n");
  fprintf(stderr, "Checksum code reverse engineered from Nagra's program.\n");
[...]
  Below is the actual checksum calculation algorithm, which was
  reverse engineered out of Nagra's program.

  As you can see, the algorithm is total crap. Obviously it was
  designed to be difficult to guess and reverse engineer, and not
  to give a good checksum. A simple XOR and ROL 13 would give a
  just as good checksum. The ifs and the data dependent ROL are really
  extreme nonsense.
*************************************************************************
Who this Nagra person is, or what code this originally appeared in, is
anyone's guess. My guess is that the algorithm was derived from an
analysis of some MIPS code (probably the actual checksum-verifying
routine in some ROM's boot code), due to the fact that there the
intermediate values are named t1-t6, which are temporary registers in the
R4300i CPU.
*************************************************************************
 */

#include "JuceHeader.h"
#include "ROM.h"

#include "n64checksum.h"



#define NUM_CICS 4

static const int cic_name_list[NUM_CICS] = {
//    6101, //what's the difference between 6101 and 6102?
    6102,
    6103,
    6105,
    6106
};

static const uint32 cic_seed_list[NUM_CICS] = {
//    0xF8CA4DDC, //what's the difference between 6101 and 6102?
    0xF8CA4DDC,
    0xA3886759,
    0xDF26F436,
    0x1FEA617A
};

int getNumCICs() { return NUM_CICS; }
int getCICName(int i) { if(i < 0 || i >= NUM_CICS) return 0; return cic_name_list[i]; }


#define ROL(i, b) (((i) << (b)) | ((i) >> (32 - (b))))

#define N64_HEADER_SIZE  0x40
#define N64_BC_SIZE      (0x1000 - N64_HEADER_SIZE)

#define N64_CRC1         0x10
#define N64_CRC2         0x14

#define CHECKSUM_START   0x00001000
#define CHECKSUM_LENGTH  0x00100000


int CalculateCRC(ROM& rom, int cic_index, uint32* crc1, uint32* crc2) {
    if(cic_index >= NUM_CICS){
        DBG("Unknown CIC index " + String(cic_index) + "! See n64checksum.cpp for usage!");
        return -1;
    }
    if(rom.getSize() < CHECKSUM_START+CHECKSUM_LENGTH){
        DBG("ROM smaller than area to calculate checksum on!");
        return -1;
    }
	uint32 seed = cic_seed_list[cic_index];
	int bootcode = cic_name_list[cic_index];
	//DBG("Checking CRCs of ROM with CIC " + String(bootcode) + "...");

	uint32 t1, t2, t3, t4, t5, t6;
	uint32 r, d, i;

	t1 = t2 = t3 = t4 = t5 = t6 = seed;

	i = CHECKSUM_START;
	while (i < (CHECKSUM_START + CHECKSUM_LENGTH)) {
		d = rom.readWord(i);
		if ((t6 + d) < t6) t4++;
		t6 += d;
		t3 ^= d;
		r = ROL(d, (d & 0x1F));
		t5 += r;
		if (t2 > d){
		    t2 ^= r;
		}else{
		    t2 ^= t6 ^ d;
		}

		if (bootcode == 6105){
		    t1 += rom.readWord(N64_HEADER_SIZE + 0x0710 + (i & 0xFF)) ^ d;
		}else{
		    t1 += t5 ^ d;
		}

		i += 4;
	}
	if (bootcode == 6103) {
		*crc1 = (t6 ^ t4) + t3;
		*crc2 = (t5 ^ t2) + t1;
	}
	else if (bootcode == 6106) {
		*crc1 = (t6 * t4) + t3;
		*crc2 = (t5 * t2) + t1;
	}
	else {
		*crc1 = t6 ^ t4 ^ t3;
		*crc2 = t5 ^ t2 ^ t1;
	}
	return 0;
}

int UpdateCRC(ROM& rom){
    if(rom.cic_index < 0 || rom.cic_index >= NUM_CICS){
        DBG("ROM has unknown CIC, cannot update CRC!");
        return -1;
    }
    uint32 crc1, crc2;
    int ret = CalculateCRC(rom, rom.cic_index, &crc1, &crc2);
    if(ret < 0) return ret;
    uint32 old_crc1 = rom.readWord(N64_CRC1);
	uint32 old_crc2 = rom.readWord(N64_CRC2);
	if(crc1 == old_crc1 && crc2 == old_crc2){
	    DBG("CRCs match: 0x" + ROM::hex(crc1) + ", 0x" + ROM::hex(crc2));
	    return 0;
	}
	DBG("CRC mismatch: original 0x" + ROM::hex(old_crc1) + ", 0x" + ROM::hex(old_crc2));
	DBG("            calculated 0x" + ROM::hex(crc1) + ", 0x" + ROM::hex(crc2));
	DBG("Updating CRCs in ROM...");
	rom.writeWord(N64_CRC1, crc1);
	rom.writeWord(N64_CRC2, crc2);
	return 1;
}

int FindCIC(ROM& rom){
    if(rom.getSize() < CHECKSUM_START+CHECKSUM_LENGTH){
        DBG("ROM smaller than area to calculate checksum on!");
        return -1;
    }
    uint32 crc1, crc2;
    uint32 old_crc1 = rom.readWord(N64_CRC1);
	uint32 old_crc2 = rom.readWord(N64_CRC2);
	int ret;
    for(int cic_index = 0; cic_index < NUM_CICS; cic_index++){
        ret = CalculateCRC(rom, cic_index, &crc1, &crc2);
        if(crc1 == old_crc1 && crc2 == old_crc2){
	        DBG("CRCs match: 0x" + ROM::hex(crc1) + ", 0x" + ROM::hex(crc2) 
	                + "-- ROM has CIC " + String(cic_name_list[cic_index]));
	        rom.cic_index = cic_index;
	        return cic_index;
	    }
    }
    DBG("CRCs did not match with any CIC!");
    rom.cic_index = -1;
    return -1;
}
