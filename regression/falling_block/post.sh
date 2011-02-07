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
    #awk '!NF{print} NF{print $1, $2, $5, $6, $11; print -$1, $2, -$5, $6, $11}' $outd/punto.dat > $outd/punto.vis
    awk '!NF{print} NF{print $1, $2, $5, $6, $11}' $outd/punto.dat > $outd/punto.vis
    awk 'NF{vx+=$5; vy+=$6; ex+=$5^2+$6^2; n++} !NF{print vx/n, vy/n, ex/n; vx=vy=n=ex=0}' \
	$outd/punto.dat > $outd/punto.mom
    awk -f block-cm.awk $outd/punto.dat > $outd/punto.block
    # get average block velocity 
    awk -f block-vel.awk $outd/punto.block > $outd/block.vel
    printf "(post.sh) processing %s\n" $outd
done

