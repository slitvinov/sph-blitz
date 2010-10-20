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
    time=$(echo output$res/prtl00112*.dat | awk -v FS="prtl" '{print $2}'  | tr -d '.dat')
    L=$(getval output$res/config.tcl "L")
    n=100
    seq 1 $n | awk -v n=$n -v L=$L '{print L/(n+1)*$1, 0.25*L}' > probe
    # take a "line" in the middle of the domain
    awk '$0~/^[0-9]/{print $2, $3}' output$res/prtl00112*.dat > prof.$res
    # generate a reference theoretical profiles
    ./poiseuille.awk -v t=${time}e-6 prof.$res > prof.$res.ref
done

printf "run.sh:$LINENO writing L2 norm in conv.dat\n" > "/dev/stderr"
PYTHONPATH=../ python poiseuille.py prof.1 prof.2 prof.3 | awk '{print 2^(NR+1), $1}' > conv.dat






