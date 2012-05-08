#! /bin/bash

set -e
set -u
sph=../../src/sph
dname=sim1

mkdir -p ${dname}
cd ${dname}
cp ../boiling.cfg boiling_run.cfg
awk 'NF>3{$4=0.0; $5=0.0} 1'   ../boiling.rst > boiling_run.rst
for n in $(seq 1 4); do
    ${sph} boiling_run
    awk -v n=30 -f ../../scripts/addlayer_next.awk boiling_run.rst > /tmp/b
    mv /tmp/b boiling_run.rst
done

sed -i '/TIMING/s/1.0e-2/5e2/g' boiling_run.cfg
${sph} boiling_run

