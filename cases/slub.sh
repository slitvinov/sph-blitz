#! /bin/bash

set -e
set -u

dname=slub1
mkdir -p ${dname}
sph=../../src/sph
cd ${dname}

cp ../slub.cfg slub.cfg
awk '/INITIAL_CONDITION/{$2=0} 1' ../slub.cfg | \
    awk '/TIMING/{$3=1e-6; $4=1e-6} 1' > slub_init.cfg
${sph}  slub_init
awk -f ../../scripts/slub.awk  slub_init.rst > slub.rst

rm outdata/*.dat
${sph}  slub