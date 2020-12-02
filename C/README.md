
This directory/folder contains C examples for working with NovAtel receiver log checksums.


<H1>Contents</H1>

<H2>checksumDemo.c</H2>
Contains example invokations of binary and ascii checksum computations.
	
<H2>crcAscii > crcAscii.c</H2>
Contains an ascii implementation of the checksum algorithm. This file is referenced and used by others.
	
<H2>crcAscii > checkCrcAscii.c</H2>
A program that will validate a checksum in a log message. Run this program by calling it and providing your log as a parameter. Note your log must be wrapped in double-quotation characters (") and any internal double-quote characters must be escaped (ie " becomes \")
	
<H2>crcAscii > bulkCrcAscii.c</H2>
This program validates checksums of raw ASCII logs dumped in to a file. Invoke this program with a parameter given for the file containing the logs.
	
<H2>crcAscii > sampleLogs.txt</H2>
This file contains a series of real sample log outputs that can be used as input to the bulkCrcAscii program.
	

	
<H1>How to Compile</H1>

<H2>Unix type machines</H2>
Run the build script: ./build.sh to produce "checkCrcAscii.bin" and "bulkCrcAscii.bin"

<H2>Windows machines</H2>
Windows builds require the Microsoft C/C++ compiler that's freely bundled with Visual Studio. 

<OL>
<LI>Install Visual Studio from here: https://visualstudio.microsoft.com/</LI>
<LI>Open the x64 Native Tools Command Prompt and change directories to where the code is.</LI>
</OL>
3. Run the build.bat file to build the checkCrcAscii program. Note that the cl compiler cannot build the present version of the bulkCrcAscii program. 
This program can be run on Windows, from within the Linux Subsystem, following the Unix instructions.
