#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "temporalErrEvolution.eps"

#set format y "10^{%L}"
set logscale y
set ylabel "Y-AXIS" 2,0 # to move y axis to the left by 2 points

set grid;
set xlabel "Time"; set ylabel "Error";
plot [0.0:4.2][0.00001:0.08] 'tempErrEvolution.dat' u 1:2 title 'L_1 error' with lp lw 1.5, 'tempErrEvolution.dat' u 1:3 title 'L_2 error' with lp lw 1.5,'tempErrEvolution.dat' u 1:4 title 'L_inf error' with lp lw 1.5;

set terminal png large
set output "temporalErrEvolution.png"
replot

reset

EOF
