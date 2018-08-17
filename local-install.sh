#! /bin/bash

set -eu

cd blitz
./configure --prefix=$(pwd)/blitz-prefix --disable-doxygen
make install
cd ..
./configure --with-blitz=$(pwd)/blitz/blitz-prefix
make
