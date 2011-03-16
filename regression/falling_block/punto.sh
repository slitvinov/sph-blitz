#! /bin/bash

set -e
set -u
eta="$1"
k="$2"
vs="$3"
nit="$4"
eta_block=1e4


title=$(printf "eta=%s k=%s vs=%s" $eta $k $vs)

dirname=outdata-nr${eta_block}-p0.04vsound${vs}xncell10niter${nit}-2.0k_rho${k}eta_media${eta}gamma2.0ht0.1
punto -z 1:2:5 -c -s 6 "$title" ${dirname}/punto.block &
punto -z 1:2:5 -c -s 6 -B 0.4:-0.1:0.6:1.1 -T "$title" ${dirname}/punto.vis 

