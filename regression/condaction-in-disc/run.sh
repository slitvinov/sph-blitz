#! /bin/bash

set -e
set -u

source ../../scripts/getval.sh
source ../../scripts/float.sh

# copy executable
cp ../../src/sph sph
reslist="14 20 27 34 40"
#reslist="14"
for res in $reslist; do
    SPH_TCL="set res_level $res" ./sph slub
    touch /tmp/sph.INFO /tmp/sph.ERROR
    cp /tmp/sph.INFO /tmp/sph.ERROR output$res/

    # get the last timestep 
    auxTime=$(echo output$res/prtl0031*.dat | awk -v FS="prtl" '{print $2}'  | tr -d '.dat' | sed 's/0*//')
    printf "($0) auxTime = %s\n" $auxTime
    fromatf=$(getval output$res/config.tcl "output_file_format_factor")
    printf "($0) formatf = %s\n" $fromatf
    time=$(float_eval "$auxTime/$fromatf")
    printf "($0) time = %s\n" $time
    x0=$(getval output$res/config.tcl "x0")
    y0=$(getval output$res/config.tcl "y0")
    R=$(getval output$res/config.tcl "R")
    printf "($0) x0 = %s\n" $x0
    printf "($0) y0 = %s\n" $y0
    # get profile
    awk -v x0=$x0 -v y0=$y0 '$0~/^[0-9]/{print sqrt( ($1-x0)^2 + ($2-y0)^2 ), $9}' output$res/prtl0031*.dat > prof.$res
    
    # get theoretical profile
    alpha=1e-3
    ../../prefix-thirdparty/bin/tclsh8.5 disc.tcl -a $alpha -r $R -t $time < prof.$res > prof.$res.ref
done