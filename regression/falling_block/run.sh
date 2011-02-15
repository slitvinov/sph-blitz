#! /bin/bash

set -e
set -u
conf=falling_block_nosym
sph=../../src/sph

for eta_media in 0.005; do
    for vsound in 14.0; do
	SPH_TCL="set k_rho 0.9; set eta_block 1e4; set eta_media $eta_media; set vsound $vsound"  $sph $conf 
    done
done

