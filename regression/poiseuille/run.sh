#! /bin/bash

set -e
set -u

source ../../scripts/getval.sh
source ../../scripts/float.sh

# copy executable
cp ../../src/sph sph
reslist="1 2 3"
for res in $reslist; do
    SPH_TCL="set res_level $res" ./sph poiseuille
    # copy log files
    touch /tmp/sph.INFO /tmp/sph.ERROR
    cp /tmp/sph.INFO /tmp/sph.ERROR output$res/
    # to get the time step from the name of output file
    aux_time=$(echo output$res/prtl00112*.dat | awk -v FS="prtl" '{print $2}'  | tr -d '.dat' | sed 's/^0*//')
    ff=$(getval output$res/config.tcl "output_file_format_factor")
    time=$(float_eval "$aux_time/$ff")
    L=$(getval output$res/config.tcl "L")
    sl=$(getval output$res/config.tcl "SUPPORT_LENGTH")
    n=100
    seq 1 $n | awk -v n=$n -v L=$L '{print 0.25*L, L/(n+1)*$1}' > probe.$res
    ./poiseuille.awk -v yidx=2  t=${time} probe.$res > prof.$res.ref
    ../../src/tools/SPHProbe/sphprobe  --probe probe.$res --c1 output$res/prtl00112*.dat --sl $sl | awk '{print $2, $5}' > prof.$res
done

printf "run.sh:$LINENO writing L2 norm in conv.dat\n" > "/dev/stderr"
PYTHONPATH=../ python poiseuille.py prof.1 prof.2 prof.3 | awk '{print 2^(NR+1), $1}' > conv.dat

gnuplot <<EOF
set term postscript enhanced
set output "conv.eps"
set log
set xlabel "resolution"
set ylabel "L2 norm"
plot "conv.dat" w lp ps 1 pt 7
EOF

gnuplot <<EOF
set term postscript enhanced
set output "prof.eps"
set xlabel "y"
set ylabel "vx"
plot "prof.1" w l, \
     "prof.2" w l, \
     "prof.3" w l, \
     "prof.3.ref" w l t "analytical"
EOF
