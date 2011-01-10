#! /bin/bash

set -e
#set -u

if [ -z "$1" ]; then
    dlist=$(ls -1 -d outdata*)
else
    dlist=$1
fi

for outd in $dlist; do
    ../../scripts/plain2punto.sh $outd
    awk '!NF{print} NF{print $1, $2, -$5, $6, $11; print -$1, $2, -$5, $6, $11}' $outd/punto.dat > $outd/punto.vis
    awk -f block-cm.awk $outd/punto.dat > $outd/punto.block
    
    echo $outd
done

