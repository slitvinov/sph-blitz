#! /bin/bash

set -e
set -u
cfgname=tube
awk '/INITIAL_CONDITION/{$2=0} 1' ${cfgname}.cfg | \
awk '/TIMING/{$3=1e-6; $4=1e-6} 1' > ${cfgname}_init.cfg
../src/sph  ${cfgname}_init

awk --lint=fatal -f ../scripts/${cfgname}.awk  ${cfgname}_init.rst | \
    awk --lint=fatal -f ../scripts/bubbles_intube.awk \
     > ${cfgname}.rst

rm outdata/*.dat
../src/sph  ${cfgname}