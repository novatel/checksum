/*
The MIT License (MIT)

Copyright (c) 2019 NovAtel Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without r
estriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom
the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, A
RISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


//This file contains checksum code. It's not intended to be directly invoked (note the lack of a main() function. This code is 
//imported in to other areas and used there.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define CRC32_POLYNOMIAL 0xEDB88320L

typedef struct  {
	int recordNumber;
	char* computedChecksum;
	char* expectedChecksum;
} checksumReport;

//Calculate a CRC value to be used by CRC calculation functions.
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


//Calculates the CRC-32 of a block of data all at once ulCount - Number of bytes in the data block ucBuffer - Data block
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


//Validates the given input parameter(s). Could be altered to include more extensive checking logic
int isValidParametersGiven(int argc, char** argv) {
	if (argc == 2) return 0;
	return 1;
}

//Return the index of the last occurence of 'occurence' char, or -1 if not found
int findIndexOfLastOccurence(char* logString, char occurence) {
	int lastIndexOfOccurence = -1;
	
	for (int i=0;i<strlen(logString);i++) {
		if (logString[i] == occurence) lastIndexOfOccurence = i;
		if (logString[i] == '\0') break;
	}
	
	return lastIndexOfOccurence;
}

char* getLogMessage(char* rawMessage) {
	int pivot = findIndexOfLastOccurence(rawMessage, '*');
	char* logMessage = malloc(sizeof(char)*(pivot+1));
	for (int i=0;i<pivot+1;i++) logMessage[i] = '\0'; //clear the buffer out
	int offset=0;	//If the log message starts with a '#', then we use this to work around it. offset should only be 0 or 1.
	
	if (rawMessage[0] == '#') offset=1;
	for (int i=0;i<pivot;i++) logMessage[i] = rawMessage[i+offset];
	
	logMessage[pivot-offset] = '\0';	//Make this a null terminated string. If there was a leading '#', then the pivot ('*') will be at a later index.
	return logMessage;
}

char* getExpectedChecksum(char* rawMessage) {
	int pivot = findIndexOfLastOccurence(rawMessage, '*');
	int stringLength = strlen(rawMessage);
	char* checkSum = malloc(sizeof(char)*(stringLength - pivot + 1));
	for (int i=0;i<stringLength-pivot + 1;i++) checkSum[i] = '\0';
	for (int i=pivot+1;i<stringLength;i++) checkSum[i-pivot-1] = rawMessage[i];
	return checkSum;
}

//Receives a log message and its expected checksum value. If the checksum computed for the message matches the expected checksum, "valid message" is printed to screen
//If the message checksum does not match the expected checksum, "invalid message" is printed to screen.
int checkAsciiChecksum(char* logMessage, char* expectedChecksum) {
	unsigned long computedChecksum = CalculateBlockCRC32(strlen(logMessage), (unsigned char*)logMessage);
	char* endPtr; //not used
	unsigned long expectedChecksumLong = strtoul(expectedChecksum, &endPtr, 16);
	int match = 0; //For return value. 1 == true, 0 == no match
	if (expectedChecksumLong == computedChecksum) {
		printf("valid message\n");
		match = 1;
	}
	else printf("invalid message (Expected: %" PRIx64 ", Computed: %" PRIx64 ")\n", expectedChecksumLong, computedChecksum);
	
	return match;
}


