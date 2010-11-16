#! /bin/bash

set -e
set -u

function timep() {
    local t0=$1
    local time=$(awk -v t=$t0 '$1>=t{print $1; exit}' output$res/time.dat) 
    local sphfile=$(awk -v t=$t0 '$1>=t{print $2; exit}' output$res/time.dat) 
    awk '{print $1, $10}' $sphfile > prof.$res.$t0
    ./sinslub.awk -v k=1.0 -v rho=10.0 -v cv=1.0 -v l=1.0 -v t=$time prof.$res.$t0 > prof.$res.ref.$t0

}

# copy executable
cp ../../src/sph sph
reslist="30"
for res in $reslist; do
    #SPH_TCL="set res_level $res" ./sph slub
    touch /tmp/sph.INFO /tmp/sph.ERROR
    cp /tmp/sph.INFO /tmp/sph.ERROR output$res/

    timep 0.02
    timep 0.5
    timep 1.5
done