/*
 * See n64checksum.cpp for header information.
 */

#ifndef N64CHECKSUM_H_INCLUDED
#define N64CHECKSUM_H_INCLUDED

#include "ROM.h"

int getNumCICs();
int getCICName(int i);
int CalculateCRC(ROM& rom, int cic_index, uint32* crc1, uint32* crc2);
int UpdateCRC(ROM& rom);
int FindCIC(ROM& rom);

#endif
