#!/bin/bash

function make_module {
	make $1
	./$1.bin
	make clean
}

if [ $# -eq 0 ]
then
	echo "module name not specified, do nothing"
	exit 0
fi

modules="graph list sort"

if [ $1 = all ]
then
	for module in $modules
	do
		make_module $module
	done
	exit
fi

make_module $1
