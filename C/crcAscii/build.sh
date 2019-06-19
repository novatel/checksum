#!/bin/bash

compileIt() {
	if [ ! -f "$1.c" ] ; then
		echo "Cannot build $1.c, does not exist"
	else
		echo -e "\nBuilding $1.c"
		gcc -o $1.bin $1.c
		echo "Built $1.bin"
	fi
}


## MAIN ##

#gcc -o checkCrcAscii.bin checkCrcAscii.c
compileIt "checkCrcAscii"
compileIt "bulkCrcAscii"
