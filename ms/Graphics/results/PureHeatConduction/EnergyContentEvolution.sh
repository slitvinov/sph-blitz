#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "EnergyContentEvolution.eps"


set grid;
set xlabel "Time"; set ylabel "Energy Content";
plot [0.0:600][0.0:0.65] 'energyContentEvolution.dat' u 1:2 title 'simu' with line lw 8;
set terminal png large
set output "EnergyContentEvolution.png"
replot

reset

EOF
