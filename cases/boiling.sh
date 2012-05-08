#! /bin/bash

set -e
set -u
cp boiling.cfg boiling_run.cfg
cp boiling.rst boiling_run.rst

for n in $(seq 1 100); do
    ../src/sph boiling_run
    awk -f ../scripts/addlayer.awk boiling_run.rst > /tmp/b
    mv /tmp/b boiling_run.rst
done

sed -i '/TIMING/s/5.0e-3/5e2/g' boiling_run.cfg
../src/sph boiling_run

