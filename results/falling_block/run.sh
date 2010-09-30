#! /bin/bash

cp ../../src/sph sph
SPH_TCL="set eta_media 1" ./sph ../../cases/falling_block_sym &
SPH_TCL="set eta_media 0.1" ./sph ../../cases/falling_block_sym &
SPH_TCL="set eta_media 0.01" ./sph ../../cases/falling_block_sym &
SPH_TCL="set eta_media 0.001" ./sph ../../cases/falling_block_sym &
SPH_TCL="set eta_media 0.0001" ./sph ../../cases/falling_block_sym &


