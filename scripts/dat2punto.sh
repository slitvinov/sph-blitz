#!/bin/bash

for i in prtl[0-9]*.dat
do awk '
/^zone/ { zone += 1 }
!/=/ { print $1, $2, $3, $4, zone + 0}
' "$i"
   printf '\n'
done 
