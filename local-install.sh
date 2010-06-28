#! /bin/bash

set -e
set -u
PREFIX=$(pwd)/prefix-thirdparty
WRKDIR=$(pwd)

# compile and install tcl
cd tcl/unix
CC=gcc CXX=g++ ./configure --prefix=$PREFIX
make install
cd ${WRKDIR}

# compile and install blitz
cd blitz
CXX=g++ ./configure --prefix=$PREFIX
make install
cd ${WRKDIR}

./configure --with-blitz=${PREFIX} --with-tcl=${PREFIX}/lib/
make
