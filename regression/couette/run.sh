#! /bin/bash

set -e
set -u

# copy executable
cp ../../src/sph sph
for res in 1 2 3; do
    SPH_TCL="set res_level $res" ./sph couette
done

