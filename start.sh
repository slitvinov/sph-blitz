#!/bin/bash
#rm log.log
# 0: run a new simulation
# 1: use output data as an initial conditions
export INITIAL_CONDITION=0

# CDF: netcdf output
#   OUTPUT_DIR/par.nc
# TEXT: text output (restart is not possible)
#   OUTPUT_DIR/par.txt: particle data
#   OUTPUT_DIR/attr.txt: time attributes
#   punto -g 600x600  -z 1:2:6 -s 4 -D 2  -c 6 par.txt  
export STREAMNAME=CDF

# maximum simulation time (wall clock, seconds)
export MAX_TIME=0

# the multiplication coefficient for the time step
export TIMESTEP_CO=1.0
src/sphopt marco-3

