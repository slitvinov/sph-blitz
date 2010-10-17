#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
#cp ../../src/outdata/prtl$1.dat prtl$1.dat

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "T_profiles$1.eps"


set grid;
set xlabel "Length"; set ylabel "Temperature";
plot [0.0:1.0][-0.1:1.15] 'simuForPlot$1.dat' u 1:2 title 'simu' with points lw 8, 'exact$1.dat' u 1:2 title 'exact' with line lw 8;

set terminal png large
set output "T_profiles$1.png"
replot

reset

EOF
