#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
#cp ../../src/outdata/prtl$1.dat prtl$1.dat

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "T_profiles$1.eps"

set key top left
set grid;
set xlabel "Position x"; set ylabel "Temperature T";
plot [0.0:1.0][-0.1:1.15] 'exact$1.dat' u 1:2 title 'Exact' with line lt 2 lw 8, 'simuForPlot$1.dat' u 1:2 title 'Simulation' with points lt 1 lw 8;

set terminal png large
set output "T_profiles$1.png"
replot

reset

EOF
