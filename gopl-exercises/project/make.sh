# !/bin/bash

# usage example:
#	cd /path/to/project 
#	./make.sh ch05/ex15
#	../bin/ex15	

set -u -e

export GOPATH=$GOPATH:`pwd`/..

rm -rf ../bin/*
echo $1
go install $1