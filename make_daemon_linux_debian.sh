#!/bin/sh
T1=`date +%s`
cd src/leveldb
make clean
cd ..
make -f makefile.unix clean
make -f makefile.unix
test -f batjorged && echo "built=`pwd`/batjorged size=`du -h batjorged|cut -f1` bytes=`du -b batjorged|cut -f1` sha256=`sha256sum batjorged|cut -d" " -f1`";
let RT="`date +%s`-T1";
echo "runtime ${RT}s";
cp -v batjorged ~/
