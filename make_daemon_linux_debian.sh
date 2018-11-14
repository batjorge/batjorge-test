#!/bin/sh
test -z $1 && DATE=`date +%s` || DATE=$1
cd src/leveldb
make clean
cd ..
make -f makefile.unix clean
make -f makefile.unix
test -e ~/release && test -f batjorged && echo "${DATE}: built=`pwd`/batjorged size=`du -h batjorged|cut -f1` bytes=`du -b batjorged|cut -f1` sha256=`sha256sum batjorged|cut -d" " -f1`" >> ~/release/built.log;
let RT="`date +%s`-DATE";
echo "runtime ${RT}s";
test -e ~/release && test -f batjorged && mv -v batjorged "/home/batjorge/release/batjorged_${DATE}";
