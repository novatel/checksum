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

#include "crcAscii.c"

//Parameter 1 (argv[0]): The ASCII string from the NovAtel receiver, including checksum. Note the parameter needs to be quoted. And internal quotes will have to be escaped
//#BESTPOSA,ICOM2,0,85.0,FINESTEERING,2007,169577.000,02000020,b1f6,14693;SOL_COMPUTED,PPP,51.11679200638,-114.03886802392,1064.4326,-16.9000,WGS84,0.0498,0.0410,0.0756,\"TSTR\",17.000,0.000,18,18,18,16,00,00,00,33*73cf9be2
void main(int argc, char** argv) {
	if (isValidParametersGiven(argc, argv) != 0) {
		printf("\nError: This program expects input from a single parameter, which is an escaped ASCII string from the NovAtel receiver.\n");
		return;
	}

	char* logMessage = getLogMessage(argv[1]);
	char* expectedChecksum = getExpectedChecksum(argv[1]);

	checkAsciiChecksum(logMessage, expectedChecksum);
}
