#! /bin/bash

set -e
set -u

source ../../scripts/getval.sh
source ../../scripts/float.sh

# copy executable
cp ../../src/sph sph
reslist="1 2 3"
for res in $reslist; do
    #SPH_TCL="set res_level $res" ./sph flow-around-cylinder
    # copy log files
    touch /tmp/sph.INFO /tmp/sph.ERROR
    cp /tmp/sph.INFO /tmp/sph.ERROR output$res/

    L=$(getval output$res/config.tcl "L")
    sl=$(getval output$res/config.tcl "SUPPORT_LENGTH")
    sl=$(getval output$res/config.tcl "SUPPORT_LENGTH")

    # take the last snapshot
    time=$(tail -n 1 output$res/time.dat | awk '{print $1}') 
    sphfile=$(tail -n 1 output$res/time.dat | awk '{print $2}') 
    printf "$0:$LINENO: sphfile: $sphfile\n"

    n=100
    seq 0 $n | awk -v L=$L -v n=$n '{print L, $1/n* L*0.5}' > probe.1
    seq 0 $n | awk -v L=$L -v n=$n '{print 0.5*L, $1/n* L*0.5}' > probe.2

    ../../src/tools/SPHProbe/sphprobe --probe probe.1 --c1 $sphfile --sl $sl | \
	awk -v L=$L '{print $2+0.5*L, $5}' > prof.1.$res
    ../../src/tools/SPHProbe/sphprobe --probe probe.2 --c1 $sphfile --sl $sl | \
	awk -v L=$L '{print $2+0.5*L, $5}' > prof.2.$res
done