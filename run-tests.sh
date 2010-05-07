#! /bin/bash

set -e 
set -u

cd src


./sph ../cases/couette
cd outdata 
../../scripts/dat2punto.sh > punto.dat


