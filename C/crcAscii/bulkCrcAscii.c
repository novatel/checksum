// This program reads logs defined by a file given as a parameter. Each log is checked and results are printed to screen


#include "crcAscii.c"
#include <stdio.h>
#include <stdlib.h>

#define MINIMUM_LOG_MESSAGE_LENGTH_TO_CONSIDER 5

int validateParameters(int argc, char** argv) {
	int error = 0;
	
	//Right number of args?
	if (argc != 2) error = 1;
	else {
		//Is argv[1] a file that can be read?
		FILE* fp = fopen(argv[1], "r");
		if (fp == NULL) error = 2;
		else fclose(fp);
	}
	
	//Inform user of the bad news
	if (error != 0) {
		printf("\nThis program must be run with a single parameter pointing to a file with logs in it. Error #%i\n\n", error);
		return(1);
	}
	
	return(0);
}

//Decide if this line is a log, if so, run the checksum function on it.
//Returns 1 if this is a log with a valid checksum
//Returns 0 if this is a log with an invalid checksum
//Returns -1 if this is not a log
int processPotentialLogEntry(char* maybeLog, int lineNumber) {
	if (strlen(maybeLog) < MINIMUM_LOG_MESSAGE_LENGTH_TO_CONSIDER) return -1;
	
	if (maybeLog[0] == ';') return -1;
	
	char* logMessage = getLogMessage(maybeLog);
	char* expectedChecksum = getExpectedChecksum(maybeLog);
	printf("Line %i: ", lineNumber);
	return checkAsciiChecksum(logMessage, expectedChecksum);
}

void main(int argc, char** argv) {
	if (validateParameters(argc, argv) != 0) return;
	
	//Read lines from file
	FILE* fp = fopen(argv[1], "r");
	char* line = NULL;
	ssize_t amountRead;
	size_t length = 0;
	int lineCount = 1;
	
	int validRecordCount = 0;
	int invalidRecordCount = 0;
	
	//Iterate through all lines in the file
	while ((amountRead = getline(&line, &length, fp)) != -1) {
		int retval = processPotentialLogEntry(line, lineCount++);
		if (retval == 1) validRecordCount++;
		if (retval == 0) invalidRecordCount++;
	}
	
	//Close file handle
	fclose(fp);
	
	//Print results
	printf("\n\nSummary:\n%i valid records\n%i invalid records\n\n", validRecordCount, invalidRecordCount);
}
