#!/bin/bash

for i in prtl[0-9]*.dat
do awk 'NF>3 && NR>3 {print $1, $2, $3, $4}' "$i"
   printf '\n'
done 
