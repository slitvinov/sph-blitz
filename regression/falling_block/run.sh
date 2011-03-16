#! /bin/bash

set -e
set -u
conf=falling_block_nosym
sph=../../src/sph
b_eta=1e4

for eta_media in 0.005 0.01 0.02; do
    for vsound in 30.0 40.0 50.0; do
	SPH_TCL="set k_rho 0.9; set eta_block $b_eta; set eta_media $eta_media; set vsound $vsound"  $sph $conf  &
    done
done

