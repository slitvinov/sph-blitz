#! /bin/bash

set -e
set -u

# copy executable
cp ../../src/sph sph
reslist="14 20 27 34 40"
kllist="10 100 1000"
for res in $reslist; do
    for kl in $kllist; do
	SPH_TCL="set res_level $res; set kl $kl" ./sph slub
	touch /tmp/sph.INFO /tmp/sph.ERROR
	cp /tmp/sph.INFO /tmp/sph.ERROR output_res${res}_kl$kl
    done
done