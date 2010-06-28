#! /bin/bash

set -e
set -u

# directory where third party libraries will be installed
PREFIX=$(pwd)/prefix-thirdparty

# working directory 
WRKDIR=$(pwd)

# compile and install tcl
cd tcl/unix
# if not given use default values
CC=${CC:=gcc} CXX=${CXX:=g++} ./configure --prefix=$PREFIX
make install
cd ${WRKDIR}

# compile and install blitz
cd blitz
CXX=g++ ./configure --prefix=$PREFIX
make install
cd ${WRKDIR}

./configure --with-blitz=${PREFIX} --with-tcl=${PREFIX}/lib/
make
