#! /bin/bash

set -e
set -u

source ../../scripts/getval.sh
source ../../scripts/float.sh

# copy executable
cp ../../src/sph sph
#SPH_TCL="set omegaRot -0.5" ./sph rotating-cylinder
# copy log files
cp /tmp/sph.INFO /tmp/sph.ERROR output/

# post processing
../../scripts/dat2punto.sh output/
omega=$(getval output/config.tcl  omegaRot)
R=$(getval output/config.tcl  R)
centerx=$(getval output/config.tcl  "centerRot(0)")
centery=$(getval output/config.tcl  "centerRot(1)")
rho=$(getval output/config.tcl "material_rho0(1)")
eta=$(getval output/config.tcl "material_eta(1)")
sl=$(getval output/config.tcl "SUPPORT_LENGTH")
cr=$(getval output/config.tcl "CELL_RATIO")
mass=$(float_eval "($sl/$cr)^2*$rho")
gamma_dot=$(getval output/config.tcl "gamma_dot")
Re=$(float_eval "$R^2*$gamma_dot/$eta/$rho")
printf "mass=%s\n" $mass > "/dev/stderr"
printf "Re=%s\n" $Re > "/dev/stderr"

# get torque on the cylinder
awk -v m=$mass -v x0=$centerx -v y0=$centery \
    -f torque.awk output/punto.dat > output/t.dat

# get normalize torque
awk -v Re=$Re -v gd=$gamma_dot \
    '{t_dl=t/gd^2; print 2*pi*t/Re}' output/t.dat > output/t-n.dat