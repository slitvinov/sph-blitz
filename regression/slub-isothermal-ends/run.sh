#! /bin/bash

set -e
set -u

source ../../scripts/getval.sh
source ../../scripts/float.sh

SPHPROBE=../../src/tools/SPHProbe/sphprobe
if [[ ! -x "${SPHPROBE}" ]]; then
    printf "%s:%i: %s must be compiled for postprocesing\n" "$0" $LINENO "${SPHPROBE}" > "/dev/stderr"
    printf "%s:%i: try make -C ../../src/tools/SPHProbe\n" "$0" $LINENO > "/dev/stderr"
    exit 2
fi

# copy executable
cp ../../src/sph sph
reslist="30 40 60 90 100 120"
for res in $reslist; do
    SPH_TCL="set res_level $res" ./sph slub
    touch /tmp/sph.INFO /tmp/sph.ERROR
    cp /tmp/sph.INFO /tmp/sph.ERROR output$res/

    time=$(awk 'NR==2{print $1}' output$res/time.dat) 
    sphfile=$(awk 'NR==2{print $2}' output$res/time.dat)
    
    kernel_type=$(getval output$res/config.tcl "KERNEL_TYPE")
    printf "%s:%i: kernel_type = %s\n" "$0" $LINENO $kernel_type > "/dev/stderr"
    L=$(getval output$res/config.tcl "L")
    sl=$(getval output$res/config.tcl "SUPPORT_LENGTH")
    printf "%s:%i: sl = %s\n" "$0" $LINENO $sl > "/dev/stderr"

    seq $(float_eval 1.0/2.0*$sl) $(float_eval $sl) $L | awk -v L=$L -v sl=$sl '{print $1, 1.0/6.0*sl}' > probe.$res
    awk '{print $1, $1}' probe.$res > prof.$res.ref
    
    "${SPHPROBE}"  --probe probe.$res --c1 "${sphfile}" --ktype "${kernel_type}" --sl $sl | awk '{print $1, $10}' > prof.$res
done

PYTHONPATH=../ python slub.py prof.30 > conv.dat
gnuplot conv.gp