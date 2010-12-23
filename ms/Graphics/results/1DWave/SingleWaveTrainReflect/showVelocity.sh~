#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 

gnuplot << EOF
set terminal postscript eps enhanced color "Helvetica" 26
set output "Velocity$1.eps"

set key left top
set grid;
set mxtics 0.25;
set xtics 0.25;

set xlabel "x position"; set ylabel "Velocity u";
plot [0.0:2.0][-0.04:0.04] 'prtl$1.dat' u 1:5 notitle with points lw 8;

set terminal png
set output "Velocity$1.png"
replot


EOF
