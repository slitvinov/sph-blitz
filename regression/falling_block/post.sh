#! /bin/bash

set -e
set -u
for outd in $(ls -1 -d outdata*); do
    ../../scripts/plain2punto.sh $outd
    awk '!NF{print} NF{print $1, $2, $11; print -$1, $2, $11}' $outd/punto.dat > $outd/punto.vis
    awk -f block-cm.awk $outd/punto.dat > $outd/punto.block
    
    echo $outd
done

