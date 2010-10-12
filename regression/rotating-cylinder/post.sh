#! /bin/bash

set -e
set -u

source ../../scripts/getval.sh
source ../../scripts/float.sh

if [ "$#" > 1 ]; then
    dirlist="$*"
else
    dirlist=$(ls -d output*)
fi


filename=$(basename $0)
# post processing

for outputdir in $dirlist; do
    printf "(%s) processing: %s\n" $filename $outputdir > /dev/stderr
    ../../scripts/dat2punto.sh ${outputdir}/
    omega=$(getval ${outputdir}/config.tcl  omegaRot)
    R=$(getval ${outputdir}/config.tcl  R)
    centerx=$(getval ${outputdir}/config.tcl  "centerRot(0)")
    centery=$(getval ${outputdir}/config.tcl  "centerRot(1)")
    rho=$(getval ${outputdir}/config.tcl "material_rho0(1)")
    eta=$(getval ${outputdir}/config.tcl "material_eta(1)")
    sl=$(getval ${outputdir}/config.tcl "SUPPORT_LENGTH")
    cr=$(getval ${outputdir}/config.tcl "CELL_RATIO")
    mass=$(float_eval "($sl/$cr)^2*$rho")
    gamma_dot=$(getval ${outputdir}/config.tcl "gamma_dot")
    Re=$(float_eval "$R^2*$gamma_dot/$eta/$rho")
    printf "(%s) mass=%s\n" $filename $mass > "/dev/stderr"
    printf "(%s) Re=%s\n" $filename $Re > "/dev/stderr"
    # get torque on the cylinder
    awk -v m=$mass -v x0=$centerx -v y0=$centery \
	-f torque.awk ${outputdir}/punto.dat > ${outputdir}/t.dat
    # get normalize torque
    pi=3.1415926
    awk -v pi=$pi -v Re=$Re -v gd=$gamma_dot -v R=$R \
	'{print $1/R^4*gd^2*Re/(2*pi)}' ${outputdir}/t.dat > ${outputdir}/t-n.dat

    # get the last snapshot
    awk 'NF&&flag{n=0; flag=0} NF{aux[n++]=$0} !NF{flag=1} END {for (i=1; i<n; i++) print aux[i]}' ${outputdir}/punto.dat | \
	awk '$7==0' > ${outputdir}/punto.last

    awk -v x0=$centerx -v y0=$centery -v R=$R '{print ($1-x0)/R, ($2-y0)/R}' ${outputdir}/punto.last > rot.in
    sed -e "s,omega:.*,omega: -($omega) ;,g" rotating-cylinder.max | maxima -b "/dev/stdin"
    paste rot.in rot.out | awk -v x0=$centerx -v y0=$centery -v R=$R -v gd=$gamma_dot \
	'{print R*$1 + x0, R*$2 + y0, $3*gd*R, $4*gd*R}' > ${outputdir}/ref
    paste ${outputdir}/ref ${outputdir}/punto.last  | awk '{print $1, $2, ($7-$3)/$3, ($8-$4)/$4}' > ${outputdir}/ref.diff
done
