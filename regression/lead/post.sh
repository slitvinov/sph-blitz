#! /bin/bash

set -u

for outdir in $(ls -d output*); do
    printf "post.sh:%i processing: %s\n" $LINENO $outdir > "/dev/stderr"
    ../../scripts/dat2punto.sh $outdir
done



