#! /bin/bash

set -e
set -u
PREFIX=$(pwd)/prefix-thirdparty
WRKDIR=$(pwd)

# compile and install blitz
cd blitz
CXX=g++ ./configure --prefix=$PREFIX
make install
cd ${WRKDIR}

# compile and install tcl
cd tcl8.5.8/unix
CC=gcc CXX=g++ ./configure --prefix=$PREFIX
make install
cd ${WRKDIR}

cd ..
./configure --with-blitz=${PREFIX}/blitz-prefix --with-tcl=${PREFIX}/lib/
make
