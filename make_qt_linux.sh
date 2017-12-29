#!/bin/sh
DATE=`date +%s`
make clean
make distclean
qmake
make
test -e ~/release && test -f batjorge-qt && echo "${DATE}: built=`pwd`/batjorge-qt size=`du -h batjorge-qt|cut -f1` bytes=`du -b batjorge-qt|cut -f1` sha256=`sha256sum batjorge-qt|cut -d" " -f1`" >> ~/release/built.log;
let RT="`date +%s`-DATE";
echo "runtime ${RT}s";
test -e ~/release && test -f "batjorge-qt" && mv -v "batjorge-qt" "/home/batjorge/release/batjorge-qt_${DATE}";

