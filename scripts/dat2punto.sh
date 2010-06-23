#! /bin/bash


# punto -D 2 -c 4 -G 0:0.2 -s 10 hm 

for file in $(ls -1 prtl[0-9]*.dat); do
    #printf "file: %s\n" $file > "/dev/stderr"
    awk 'NF>3&&NR>3{print $1, $2, $3, $4, $5, $6, $7}'  $file 
    printf "\n"
done 
