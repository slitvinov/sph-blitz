#! /bin/bash

set -e

if [ -z "$1" ]; then
    dir="outdata"
else
    dir=$1
fi

for file in $(ls -1 "${dir}"/prtl[0-9]*.*); do
    cat "$file"
    printf "\n"
done   > ${dir}/punto.dat