#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
#cp ../../src/outdata/prtl$1.dat prtl$1.dat
mkdir Figures

gnuplot << EOF
set terminal postscript eps enhanced color
set output "Figures/VelocDecay.eps"



set grid;
set y2label "(relative) error";
set y2range [0:1]
set y2tics border
#set mxtics 0.05;
#set xtics 0.25;

set xlabel "Time"; set ylabel "Maximum Velocity (abs. value)";
plot [0.0:1.5][0.0:0.04] 'decayAnalysis.dat' u 1:2 title 'exact' with line, 'decayAnalysis.dat' u 1:3 title 'simu' with points,'decayAnalysis.dat' u 1:4 axes x1y2 title 'error' with line;

set terminal png
set output "Figures/VelocDecay.png"
replot
reset


EOF
