#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
#cp ../../src/outdata/prtl$1.dat prtl$1.dat

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "T_profiles$1.eps"


set grid;
set xlabel "Position y"; set ylabel "Temperature T";
plot [0.0:0.5][0.0:1.0]  'exact$1.dat' u 1:2 title 'Exact' with line lt 2 lw 8,'simuForPlot$1.dat' u 1:2 title 'Simulation' lt 1 lw 8 with points;

set terminal png large
set output "T_profiles$1.png"
replot

reset

EOF
