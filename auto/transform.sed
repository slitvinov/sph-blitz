#!/bin/sed -f
#Template replasement in the sph configuration file
s/%MU%/1.0e-6/g # dynamic viscosity, [kg / m s]
s/%CELLRATIO%/3/g # cell particle ration []
s/%TIMESTEP%/5e-6/g # maximum timestep, output interval [s]
s/%MAXTIME%/5e-5/g # the end of time interval [s]