#! /bin/bash
set -e
set -u
# copy executable
#cp ../../src/sph sph

for eta in 0.1; do
    for xscale in 2; do
	for yscale in 1 2 3 4; do
	    for ncell in 10; do
		for omega in -0.5; do
		    SPH_TCL="set omegaRot $omega; set ncell $ncell; set xscale $xscale; set yscale $yscale; set eta $eta" ./sph rotating-cylinder &
		done
	    done
	done
    done
done
