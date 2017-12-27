#!/bin/sh
T1=`date +%s`
make clean
make distclean
qmake
make
test -f batjorge-qt && echo "built=`pwd`/batjorge-qt size=`du -h batjorge-qt|cut -f1` bytes=`du -b batjorge-qt|cut -f1` sha256=`sha256sum batjorge-qt|cut -d" " -f1`";
let RT="`date +%s`-T1";
echo "runtime ${RT}s";
