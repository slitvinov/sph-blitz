#! /bin/bash
set -e
set -u

function proflist() {
    local res=$(echo "$reslist" | xargs -n1 printf "prof.%s ")
    echo $res
}

source ../../scripts/getval.sh
source ../../scripts/float.sh

# copy executable
cp ../../src/sph sph
reslist="30 40 50 60 80 90 100 120"
for res in $reslist; do
    #SPH_TCL="set res_level $res" ./sph slub
    touch /tmp/sph.INFO /tmp/sph.ERROR
    cp /tmp/sph.INFO /tmp/sph.ERROR output$res/

    aux_time=$(echo output$res/prtl001*.dat | awk -v FS="prtl" '{print $2}'  | tr -d '.dat' | sed 's/^0*//')
    ff=$(getval output$res/config.tcl "output_file_format_factor")
    time=$(float_eval "$aux_time/$ff")
    L=$(getval output$res/config.tcl "L")
    sl=$(getval output$res/config.tcl "SUPPORT_LENGTH")

    n=50
    seq 1 $n | awk -v n=$n -v L=$L -v sl=$sl '{print L/(n+1)*$1, sl}' > probe.$res
    ./infslab.awk -v k_l=1.0 -v rho_l=1e3 -v cv_l=1.0 -v Tl=0.0 -v Tr=1.0 -v xm=0.5 -v t=$time probe.$res > prof.$res.ref
    ../../src/tools/SPHProbe/sphprobe --probe probe.$res --c1 output$res/prtl001*.dat --sl $sl | awk '{print $1, $8}' > prof.$res
done

PYTHONPATH=../ python slub.py $(proflist) > conv.dat

gnuplot <<EOF
set term postscript enhanced
set output "conf.eps"
set log 
set style data lp
set key spacing 1.5
plot [28:130][1e-4:1e-1]\
    "conv.dat" u 1:2 t "L_1" ,\
    "" u 1:3 t "L_2", \
    "" u 1:4 t "L_{inf}", \
    10/x**2 w l lt 2 t "second order"
EOF