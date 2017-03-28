#!/bin/bash

if [ $# -eq 0 ]
then
	echo "module name not specified, do nothing"
	exit 0
fi

make clean
make all

for para in $*
do
	./testbin $para
done

make clean

