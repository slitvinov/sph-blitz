#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 


gnuplot << EOF
set terminal postscript eps enhanced color "Helvetica" 26
set output "Damping.eps"


set grid;
set title "damping for 1D velocity oscillation"
set mxtics 1.0;
set xtics 1.0;

set xlabel "Time t/T"; set ylabel "Velocity amplitude U/U_0";
plot [:][0.0:1.2] 'peakVelocities.dat' u 1:3 title '' with linespoints;

set terminal png
set output "Damping.png"
replot

reset
set terminal postscript eps enhanced color "Helvetica" 26
set output "Period.eps"

set grid;
set mxtics 1.0;
set xtics 1.0;

set xlabel "Time t/T"; set ylabel "Periodical time T/T_0";
plot [:][0.0:1.2] 'DampingPeriod.dat' u 1:3 notitle with linespoints lw 8;

set terminal png
set output "Period.png"
replot


reset
set terminal postscript eps enhanced color "Helvetica" 26
set output "DampingFactor.eps"

set grid;
set mxtics 1.0;
set xtics 1.0;

set xlabel "Time t/T"; set ylabel "Damping factor c_d";
plot [:][0.0:] 'DampingPeriod.dat' u 1:2 notitle with linespoints lw 8;

set terminal png
set output "DampingFactor.png"
replot

reset



EOF
