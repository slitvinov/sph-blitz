#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 


gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "T_profile$1.eps"


set grid;
set xlabel "Length"; set ylabel "Temperature";
plot [0.0:1.0][-0.15:1.15] 'simuForPlot$1.dat' u 1:2 title 'simu' with points;

set terminal png large
set output "T_profile$1.png"
replot

reset

EOF
