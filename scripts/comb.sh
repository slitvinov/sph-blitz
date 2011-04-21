#! /bin/bash

for del in *.del; do
    printf "(comb.sh) file: ${del}\n" > "/dev/stderr"
    awk '{$1=$1; print}' $del
    printf "\n"
done > punto.dat
