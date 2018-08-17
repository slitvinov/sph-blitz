#! /bin/bash

set -eu

cd blitz
./configure --prefix=$(pwd)/prefix --disable-doxygen
make install
cd ..
./configure --with-blitz=$(pwd)/blitz/prefix
make
