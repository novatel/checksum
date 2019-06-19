/*
The MIT License (MIT)

Copyright (c) 2019 NovAtel Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#define CRC32_POLYNOMIAL 0xEDB88320L
/* --------------------------------------------------------------------------
Calculate a CRC value to be used by CRC calculation functions.
-------------------------------------------------------------------------- */
unsigned long CRC32Value(int i) {
	int j;
	unsigned long ulCRC;
	ulCRC = i;
	for ( j = 8 ; j > 0; j-- ) {
		if ( ulCRC & 1 )
			ulCRC = ( ulCRC >> 1 ) ^ CRC32_POLYNOMIAL;
		else
			ulCRC >>= 1;
	}
	return ulCRC;
}

/* --------------------------------------------------------------------------
Calculates the CRC-32 of a block of data all at once
ulCount - Number of bytes in the data block
ucBuffer - Data block
-------------------------------------------------------------------------- */
unsigned long CalculateBlockCRC32( unsigned long ulCount, unsigned char *ucBuffer ) {
	unsigned long ulTemp1;
	unsigned long ulTemp2;
	unsigned long ulCRC = 0;
	while ( ulCount-- != 0 ) {
		ulTemp1 = ( ulCRC >> 8 ) & 0x00FFFFFFL;
		ulTemp2 = CRC32Value( ((int) ulCRC ^ *ucBuffer++ ) & 0xff );
		ulCRC = ulTemp1 ^ ulTemp2;
	}
	return( ulCRC );
}

void demoCalculateAsciiChecksum() {
	//Note that the checksum is computed between the leading '#' and the trailing '*' characters, exclusively.

	//Checksum for this block was: 9c9a92bb	
	//char *sampleMessageBlock = "BESTPOSA,COM1,0,78.0,FINESTEERING,1427,325298.000,00000000,\
6145,2748;SOL_COMPUTED,SINGLE,51.11678928753,-114.03886216575,\
1064.3470,-16.2708,WGS84,2.3434,1.3043,4.7300,\"\",0.000,0.000,7,7,0,0,0,06,0,03";

	//Checksum for this block was: 73cf9be2
	char *sampleMessageBlock = "BESTPOSA,ICOM2,0,85.0,FINESTEERING,2007,169577.000,02000020,b1f6,14693;SOL_COMPUTED,PPP,51.11679200638,-114.03886802392,1064.4326,-16.9000,WGS84,0.0498,0.0410,0.0756,\"TSTR\",17.000,0.000,18,18,18,16,00,00,00,33";
 
	unsigned long CRC = CalculateBlockCRC32(strlen(sampleMessageBlock), (unsigned char*)sampleMessageBlock);

	printf("\n%s %s\n", "Demonstrating CRC computed for the block:", sampleMessageBlock);
	
	//printf("\n\n%s %lu\n", "Computed ASCII checksum (in Decimal) is: ", CRC);
	printf("%s %lx\n", "Computed ASCII checksum is: ", CRC);
}

void demoCalculateBinaryChecksum() {
	//Expect checksum 0x51, 0x7D, 0xFD, 0x3B (517dfd3b)
/*	unsigned char buffer[] = {0xAA, 0x44, 0x12, 0x1C, 0x2A, 0x00, 0x00, 0x20, 0x48, 0x00,
        	                  0x00, 0x00, 0x9C, 0xB4, 0x93, 0x05, 0x50, 0xA7, 0x63, 0x13,
                	          0x00, 0x00, 0x00, 0x00, 0x45, 0x61, 0xBC, 0x0A, 0x00, 0x00,
                        	  0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x74, 0x3B, 0x8D, 0xF3,
	                          0xF2, 0x8E, 0x49, 0x40, 0xAC, 0xBC, 0xBC, 0xB7, 0x7C, 0x82,
        	                  0x5C, 0xC0, 0xD9, 0xCE, 0xF7, 0x53, 0x63, 0xA1, 0x90, 0x40, 
                	          0x99, 0x2A, 0x82, 0xC1, 0x3D, 0x00, 0x00, 0x00, 0x44, 0xFA, 
                        	  0x15, 0x40, 0x4D, 0xF3, 0xA6, 0x3F, 0x29, 0x5C, 0x97, 0x40,
	                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        	                  0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x03};
*/

	// Expect checksum 0x42, 0xDC, 0x4C, 0x48 (42dc4c48)
	unsigned char buffer[] = {0xAA, 0x44, 0x12, 0x1C, 0x2A, 0x00, 0x02, 0x20, 0x48, 0x00,
				  0x00, 0x00, 0x90, 0xB4, 0x93, 0x05, 0xB0, 0xAB, 0xB9, 0x12, 
				  0x00, 0x00, 0x00, 0x00, 0x45, 0x61, 0xBC, 0x0A, 0x00, 0x00, 
				  0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x1B, 0x04, 0x50, 0xB3, 
				  0xF2, 0x8E, 0x49, 0x40, 0x16, 0xFA, 0x6B, 0xBE, 0x7C, 0x82,
				  0x5C, 0xC0, 0x00, 0x60, 0x76, 0x9F, 0x44, 0x9F, 0x90, 0x40,
				  0xA6, 0x2A, 0x82, 0xC1, 0x3D, 0x00, 0x00, 0x00, 0x12, 0x5A,
				  0xCB, 0x3F, 0xCD, 0x9E, 0x98, 0x3F, 0xDB, 0x66, 0x40, 0x40,
				  0x00, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				  0x00, 0x00, 0x0B, 0x0B, 0x00, 0x00, 0x00, 0x06, 0x00, 0x03}; 

	//Note that the CRC on the binary data will be little-endian ordered.
	unsigned long CRCle = CalculateBlockCRC32(sizeof(buffer), buffer);

	//big-endian users (such as x86 users) may swap endianness as follows
	unsigned long CRCbe = __builtin_bswap32(CRCle);

	printf("\n\n%s %lx \n", "Computed binary checksum (little-endian): ", CRCle);
	printf("%s %" PRIx64 "\n", "Computed binary checksum (big-endian): ", CRCbe);
}

void main() {
	demoCalculateAsciiChecksum();
	demoCalculateBinaryChecksum();
}
