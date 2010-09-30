#! /bin/bash

set -e

if [ -z "$1" ]; then
    dir="outdata"
else
    dir=$1
fi

for file in $(ls -1 "${dir}"/prtl[0-9]*.*); do
    #printf "file: %s\n" $file > "/dev/stderr"
    awk 'NF>3&&NR>2{$1=$1; print $0, no} $0~/zone/{no++}'  $file
    printf "\n"
done   > ${dir}/punto.dat
