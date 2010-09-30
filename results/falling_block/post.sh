#! /bin/bash

set -u
for outdir in $(ls -d outdata*); do
    printf "post.sh:%i processing: %s\n" $LINENO $outdir > "/dev/stderr"
    ../../scripts/dat2punto.sh $outdir
    awk 'NF&&$6==1{s+=$4; n++} !NF{print s/n; s=n=0}' "$outdir"/punto.dat > "$outdir"/media.mom
    awk 'NF&&$6==2{s+=$4; n++} !NF{print s/n; s=n=0}' "$outdir"/punto.dat > "$outdir"/block.mom

    tac "$outdir"/punto.dat | awk '!NF&&NR>1{exit} NF{print}' > "$outdir"/punto.last
    awk 'NF{print; $1=-$1; print} !NF{print}' "$outdir"/punto.dat > "$outdir"/punto.sym

    cp $outdir/punto.last /tmp/punto.last
    gnuplot gplot.gp
    printf "post.sh:%i last time step configuration is in punto.png\n" $LINENO> "/dev/stderr"
done



