#! /bin/bash

set -e
set -u

source ../../scripts/getval.sh
source ../../scripts/float.sh

# copy executable
cp ../../src/sph sph
reslist="20"
for res in $reslist; do
    SPH_TCL="set res_level $res" ./sph slub
    touch /tmp/sph.INFO /tmp/sph.ERROR
    cp /tmp/sph.INFO /tmp/sph.ERROR output$res/

    # get the last timestep 
    time=$(awk 'NR==2{print $1}' output$res/time.dat)
    sphfile=$(awk 'NR==2{print $2}' output$res/time.dat)

    printf "($0) time = %s\n" $time
    x0=$(getval output$res/config.tcl "x0")
    y0=$(getval output$res/config.tcl "y0")
    R=$(getval output$res/config.tcl "R")
    printf "($0) x0 = %s\n" $x0
    printf "($0) y0 = %s\n" $y0
    # get profile
    awk -v x0=$x0 -v y0=$y0 '{print sqrt( ($1-x0)^2 + ($2-y0)^2 ), $10}' ${sphfile} > prof.$res
    
    # get theoretical profile
    alpha=1e-3
    ../../prefix-thirdparty/bin/tclsh8.5 disc.tcl -a $alpha -r $R -t $time < prof.$res | sort -g > prof.$res.ref
done