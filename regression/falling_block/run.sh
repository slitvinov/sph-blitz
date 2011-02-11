#! /bin/bash


SPH_TCL="set eta_block 1" ../../src/sph  falling_block_per &
SPH_TCL="set eta_block 1e1" ../../src/sph  falling_block_per &
SPH_TCL="set eta_block 1e2" ../../src/sph  falling_block_per & 
SPH_TCL="set eta_block 1e4" ../../src/sph  falling_block_per &
SPH_TCL="set eta_block 1e6" ../../src/sph  falling_block_per 
