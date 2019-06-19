
This directory/folder contains C examples for working with NovAtel receiver log checksums.


--- Contents ------------------

checksumDemo.c
	Contains example invokations of binary and ascii checksum computations.
	
crcAscii > crcAscii.c
	Contains an ascii implementation of the checksum algorithm. This file is referenced and used by others.
	
crcAscii > checkCrcAscii.c
	A program that will validate a checksum in a log message. Run this program by calling it and providing your log as a parameter. Note your log must be wrapped in
	double-quotation characters (") and any internal double-quote characters must be escaped (ie " becomes \")
	
crcAscii > bulkCrcAscii.c
	This program validates checksums of raw ASCII logs dumped in to a file. Invoke this program with a parameter given for the file containing the logs.
	
crcAscii > sampleLogs.txt
	This file contains a series of real sample log outputs that can be used as input to the bulkCrcAscii program.
	

	
--- How to Compile ------------------

Unix type machines:
Run the build script: ./build.sh to produce "checkCrcAscii.bin" and "bulkCrcAscii.bin"

Windows machines:
Windows builds require the Microsoft C/C++ compiler that's freely bundled with Visual Studio. 

1. Install Visual Studio from here: https://visualstudio.microsoft.com/

2. Open the x64 Native Tools Command Prompt and change directories to where the code is

3. Run the build.bat file to build the checkCrcAscii program. Note that the cl compiler cannot build the present version of the bulkCrcAscii program. 
This program can be run on Windows, from within the Linux Subsystem, following the Unix instructions.