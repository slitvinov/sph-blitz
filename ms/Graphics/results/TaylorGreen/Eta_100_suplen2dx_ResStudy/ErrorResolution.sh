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
plot [900:7000][0.01:1] 'ErrorResolution.dat' u 1:2 title 'L_{inf,50} error' with linespoints lw 8;
set terminal png large
set output "ErrorResolution.png"
replot

reset

EOF
