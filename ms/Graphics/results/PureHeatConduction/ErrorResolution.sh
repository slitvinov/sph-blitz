#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "ErrorResolution.eps"


set logscale x
set logscale y
set format y "10^{%L}"

#set ylabel "Y-AXIS" 2,0 # to move y axis to the left by 2 points

set grid;
set xlabel "Number of particles N"; set ylabel "Error";
plot [30:250][0.00001:0.08] 'ErrorResolution.dat' u 1:2 title 'L_1 error' with linespoints lw 8, 'ErrorResolution.dat' u 1:3 title 'L_2 error' with linespoints lw 8,'ErrorResolution.dat' u 1:4 title 'L_{inf} error' with linespoints lw 8, '2nd_Order.dat' u 1:2 notitle with line lt -1 lw 0.1;

set terminal png large
set output "ErrorResolution.png"
replot

reset

EOF
