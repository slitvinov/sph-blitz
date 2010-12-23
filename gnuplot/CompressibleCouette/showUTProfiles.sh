#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
cp ../../src/outdata/prtl$1.dat prtl$1.dat

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26


set output "U_profile$1.eps"
set key top left
set grid;
set xlabel "U"; set ylabel "length y";
plot [0.0:][0.0:1.0] 'prtl$1.dat' u 3:2 title 'simu' lt 1 with points;

set terminal png large
set output "U_profile$1.png"
replot

reset

set terminal postscript eps enhanced color  "Helvetica" 26

set output "T_profile$1.eps"
set key top left
set grid;
set xlabel "T"; set ylabel "length y";
plot [:][0.0:1.0] 'prtl$1.dat' u 6:2 title 'simu' lt 1 with points;

set terminal png large
set output "T_profile$1.png"
replot

reset

EOF
