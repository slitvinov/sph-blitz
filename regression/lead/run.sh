#! /bin/bash

set -e
set -u

# copy executable
cp ../../src/sph sph
reslist="2"
for res in $reslist; do
    SPH_TCL="set res_level $res" ./sph lead
done

