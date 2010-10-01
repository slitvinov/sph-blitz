#! /bin/bash

set -e
set -u

# copy executable
cp ../../src/sph sph
reslist="1 2 3"
for res in $reslist; do
    SPH_TCL="set res_level $res" ./sph poiseuille
    # copy log files
    cp /tmp/sph.INFO /tmp/sph.ERROR output$res/
    # to get the time step from the name of output file
    time=$(echo output$res/prtl00112*.dat | awk -v FS="prtl" '{print $2}'  | tr -d '.dat')
    # generate a SPH profiles "vx vs y"
    awk '$0~/^[0-9]/{print $2, $3}' output$res/prtl00112*.dat > prof.$res
    # generate a reference theoretical profiles
    ./poiseuille.awk -v t=${time}e-6 prof.$res > prof.$res.ref
done

printf "run.sh:$LINENO writing L2 norm in conv.dat\n" > "/dev/stderr"
PYTHONPATH=../ python poiseuille.py prof.1 prof.2 prof.3 | awk '{print 2^(NR+1), $1}' > conv.dat

gnuplot <<EOF
set term postscript enhanced
set output "conv.eps"
set log
plot "conv.dat"
EOF






