#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
mkdir Visualization


gnuplot << EOF
set terminal postscript eps enhanced color
set output "Visualization/Damping.eps"


set grid;
set title "damping for 1D velocity oscillation"
set mxtics 1.0;
set xtics 1.0;

set xlabel "period"; set ylabel "Amplitude A/A_0";
plot [:][0.0:1.2] 'peakVelocities.dat' u 1:3 title '' with linespoints;

set terminal png
set output "Visualization/Damping.png"
replot

reset
set terminal postscript eps enhanced color
set output "Visualization/Period.eps"

set grid;
set title "period 1D velocity oscillation";
set mxtics 1.0;
set xtics 1.0;

set xlabel "period"; set ylabel "period time T/T_0";
plot [:][0.0:1.2] 'DampingPeriod.dat' u 1:3 title '' with linespoints;

set terminal png
set output "Visualization/Period.png"
replot


reset
set terminal postscript eps enhanced color
set output "Visualization/DampingFactor.eps"

set grid;
set title "damping factor 1D velocity oscillation";
set mxtics 1.0;
set xtics 1.0;

set xlabel "period"; set ylabel "damping factor";
plot [:][0.0:] 'DampingPeriod.dat' u 1:2 title '' with linespoints;

set terminal png
set output "Visualization/DampingFactor.png"
replot

reset



EOF
