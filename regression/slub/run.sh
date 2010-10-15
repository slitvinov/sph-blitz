#! /bin/bash

set -e
set -u

# copy executable
cp ../../src/sph sph
reslist="3 14 20 27 34 40"
for res in $reslist; do
    SPH_TCL="set res_level $res" ./sph slub
    cp /tmp/sph.INFO /tmp/sph.ERROR output$res/
done