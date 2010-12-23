#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 

gnuplot << EOF
set terminal postscript eps enhanced color "Helvetica" 26
set output "VelocDecay.eps"



set grid;
#set y2label "Error";
set format x "%2.0t{/Symbol \327}10^{%L}"
#set y2range [0:1]
#set y2tics border
#set mxtics 0.05;
set xtics 0.0001;

set xlabel "Time t"; set ylabel "Velocity u, Error (relative)";
plot [0.0:0.0005][0.0:] 'decayAnalysis.dat' u 1:3 title 'Simulation' with line lw 8, 'decayAnalysis.dat' u 1:2 title 'Exact' with line lw 8, 'decayAnalysis.dat' u 1:4 title 'Error' with line lw 8;

set terminal png
set output "VelocDecay.png"
replot
reset


EOF
