#! /bin/bash

set -e
set -u

source ../../scripts/getval.sh
source ../../scripts/float.sh

# copy executable
cp ../../src/sph sph
SPHPROBE=../../src/tools/SPHProbe/sphprobe
if [[ ! -x "${SPHPROBE}" ]]; then
    printf "%s:%i: %s must be compiled for postprocesing\n" "$0" $LINENO "${SPHPROBE}" > "/dev/stderr"
    printf "%s:%i: try make -C ../../src/tools/SPHProbe\n" "$0" $LINENO > "/dev/stderr"
    exit 2
fi

reslist="30"
for res in $reslist; do
    SPH_TCL="set res_level $res" ./sph slub
    touch /tmp/sph.INFO /tmp/sph.ERROR
    cp /tmp/sph.INFO /tmp/sph.ERROR output$res/
    
    time=$(awk 'NR==2{print $1}' output$res/time.dat) 
    printf "time: %s\n" $time > "/dev/stderr"
    sphfile=$(awk 'NR==2{print $2}' output$res/time.dat)
    L=$(getval output$res/config.tcl "L")
    sl=$(getval output$res/config.tcl "SUPPORT_LENGTH")
    seq $(float_eval 1.0/3.0*$sl) $(float_eval $sl) $L | awk -v L=$L -v sl=$sl '{print $1, L/2.0}' > probe.$res

    kernel_type=$(getval output$res/config.tcl "KERNEL_TYPE")
    sl=$(getval output$res/config.tcl "SUPPORT_LENGTH")
    "${SPHPROBE}"  --probe probe.$res --c1 "${sphfile}" --ktype "${kernel_type}" --sl $sl | awk '{print $1, $10}' > prof.$res
    ./sinslub.awk -v k=1.0 -v rho=1e3 -v cv=1.0 -v l=$(float_eval "sqrt(1.0/2.0)") -v t=$time prof.$res > prof.$res.ref
done