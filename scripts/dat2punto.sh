#! /bin/bash


# punto -D 2 -c 4 -G 0:0.2 -s 10 hm 

if [ -z "$1" ]; then
    pat="prtl"
else
    pat="$1"
fi

for file in $(ls -1 ${pat}[0-9]*.*); do
    #printf "file: %s\n" $file > "/dev/stderr"
    awk 'NF>3&&NR>3{$1=$1; print}'  $file 
    printf "\n"
done 
