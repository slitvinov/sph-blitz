#! /bin/bash


# punto -D 2 -c 4 -G 0:0.2 -s 10 hm 

outputdir="$1"
for file in $(ls -1 ${outputdir}/prtl[0-9]*.dat); do
    #printf "file: %s\n" $file > "/dev/stderr"
    awk 'NF>3&&NR>3{$1=$1; print}'  $file 
    printf "\n"
done  > ${outputdir}/punto.dat
