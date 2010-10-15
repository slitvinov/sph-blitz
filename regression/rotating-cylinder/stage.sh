#! /bin/bash

set -e
set -u
dirlist="$*"
for outputdir in $dirlist; do
    # get the last snapshot
    awk 'NF&&flag{n=0; flag=0} NF{aux[n++]=$0} !NF{flag=1} END {for (i=1; i<n; i++) print aux[i]}' ${outputdir}/punto.dat | \
	awk '$7==0' > ${outputdir}/punto.last

    awk -v x0=$centerx -v y0=$centery -v R=$R '{print ($1-x0)/R, ($2-y0)/R}' ${outputdir}/punto.last > rot.in
    sed -e "s,omega:.*,omega: -($omega) ;,g" rotating-cylinder.max | maxima -b "/dev/stdin"
    paste rot.in rot.out | awk -v x0=$centerx -v y0=$centery -v R=$R -v gd=$gamma_dot \
	'{print R*$1 + x0, R*$2 + y0, $3*gd*R, $4*gd*R}' > ${outputdir}/ref
    paste ${outputdir}/ref ${outputdir}/punto.last  | awk '{print $1, $2, ($7-$3)/$3, ($8-$4)/$4}' > ${outputdir}/ref.diff
done