#! /bin/bash
set -e
set -u

function proflist() {
    local res=$(echo "$reslist" | xargs -n1 printf "prof.%s ")
    echo $res
}

source ../../scripts/getval.sh
source ../../scripts/float.sh

SPH=../../src/sph
if [[ ! -x "$SPH" ]]; then
    printf "%s:%i: %s must be compiled\n" "$0" $LINENO "$SPH"
    exit 2
fi

SPHPROBE=../../src/tools/SPHProbe/sphprobe
if [[ ! -x "${SPHPROBE}" ]]; then
    printf "%s:%i: %s must be compiled for postprocesing\n" "$0" $LINENO "${SPHPROBE}" > "/dev/stderr"
    printf "%s:%i: try make -C ../../src/tools/SPHProbe\n" "$0" $LINENO > "/dev/stderr"
    exit 2
fi

# copy executable
cp ${SPH} sph

reslist="30 40 50 60 80 90 100 120"
for res in $reslist; do
    SPH_TCL="set res_level $res" ./sph slub
    touch /tmp/sph.INFO /tmp/sph.ERROR
    cp /tmp/sph.INFO /tmp/sph.ERROR output$res/

    time=$(awk 'NR==3{print $1}' output$res/time.dat) 
    sphfile=$(awk 'NR==3{print $2}' output$res/time.dat)

    kernel_type=$(getval output$res/config.tcl "KERNEL_TYPE")
    L=$(getval output$res/config.tcl "L")
    sl=$(getval output$res/config.tcl "SUPPORT_LENGTH")

    n=500
    seq 1 $n | awk -v n=$n -v L=$L -v sl=$sl '{print L/(n+1)*$1, 0.25*L}' > probe.$res
    ./infslab.awk -v k_l=1.0 -v rho_l=1e3 -v cv_l=1.0 -v Tl=0.0 -v Tr=1.0 -v xm=0.5 -v t=$time probe.$res > prof.$res.ref
    #"${SPHPROBE}" --probe probe.$res --c1 "${sphfile}" --ktype "${kernel_type}" --sl $sl | awk '{print $1, $10}' > prof.$res
    "${SPHPROBE}" --probe probe.$res --c1 "${sphfile}" --ktype "${kernel_type}" --sl $sl > prof.$res
    exit
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