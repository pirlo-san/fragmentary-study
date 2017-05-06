#!/bin/bash

if [ $# -eq 0 ]
then
	echo "module name not specified, do nothing"
	exit 0
fi

make clean
make $1

./test$1

make clean

