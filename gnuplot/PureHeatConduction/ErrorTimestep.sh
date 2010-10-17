#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "ErrorTimestep.eps"


set logscale x
set logscale y
#set format y "10^{%L}"

#set ylabel "Y-AXIS" 2,0 # to move y axis to the left by 2 points

set grid;
set xlabel "Timestep"; set ylabel "Error";
plot  'ErrorTimestep.dat' u 1:2 title 'L_1 error' with linespoints lw 3, 'ErrorTimestep.dat' u 1:3 title 'L_2 error' with linespoints lw 3,'ErrorTimestep.dat' u 1:4 title 'L_inf error' with linespoints lw 3;

set terminal png large
set output "ErrorTimestep.png"
replot

reset

EOF
