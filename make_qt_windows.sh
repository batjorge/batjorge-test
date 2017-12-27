#!/bin/sh
test -f batjorge-qt.pro || exit 1
if ! test -e /mnt/mxe; then echo "mxe env not found"; exit 1; fi

T1=`date +%s`

cd src/leveldb
make clean
cd ../../
make clean
make distclean

export PATH=/mnt/mxe/usr/bin:$PATH

MXE_INCLUDE_PATH=/mnt/mxe/usr/i686-w64-mingw32.static/include
MXE_LIB_PATH=/mnt/mxe/usr/i686-w64-mingw32.static/lib

i686-w64-mingw32.static-qmake-qt5 \
	BOOST_LIB_SUFFIX=-mt \
	BOOST_THREAD_LIB_SUFFIX=_win32-mt \
	BOOST_INCLUDE_PATH=$MXE_INCLUDE_PATH/boost \
	BOOST_LIB_PATH=$MXE_LIB_PATH \
	OPENSSL_INCLUDE_PATH=$MXE_INCLUDE_PATH/openssl \
	OPENSSL_LIB_PATH=$MXE_LIB_PATH \
	BDB_INCLUDE_PATH=$MXE_INCLUDE_PATH \
	BDB_LIB_PATH=$MXE_LIB_PATH \
	MINIUPNPC_INCLUDE_PATH=$MXE_INCLUDE_PATH \
	MINIUPNPC_LIB_PATH=$MXE_LIB_PATH \
	QMAKE_LRELEASE=/mnt/mxe/usr/i686-w64-mingw32.static/qt5/bin/lrelease batjorge-qt.pro

make -f Makefile.Release VERBOSE=1

test -f release/batjorge-qt.exe && echo "built=`pwd`/release/batjorge-qt.exe size=`du -h release/batjorge-qt.exe|cut -f1` bytes=`du -b release/batjorge-qt.exe|cut -f1` sha256=`sha256sum release/batjorge-qt.exe|cut -d" " -f1`";
let RT="`date +%s`-T1";
echo "runtime ${RT}s";
cp -v release/batjorge-qt.exe /home/user/batjorge/
