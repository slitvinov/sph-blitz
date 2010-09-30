#! /bin/bash

for outdir in outdata*; do
    ../scripts/dat2punto.sh $outdir

    awk 'NF&&$6==1{s+=$4; n++} !NF{print s/n; s=n=0}' "$outdir"/punto.dat > "$outdir"/media.mom
    awk 'NF&&$6==2{s+=$4; n++} !NF{print s/n; s=n=0}' "$outdir"/punto.dat > "$outdir"/block.mom
done



