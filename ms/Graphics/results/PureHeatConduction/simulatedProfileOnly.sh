#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "T_profile$1.eps"


set grid;
set xlabel "Position x"; set ylabel "Temperature T";
plot [0.0:1.0][0.49:0.51] 'simuForPlot$1.dat' u 1:2 notitle with points;

set terminal png large
set output "T_profile$1.png"
replot

reset

EOF
