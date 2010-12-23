#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 

gnuplot << EOF
set terminal postscript eps enhanced color "Helvetica" 26
set output "ShapeChangeV.eps"

set key left top
set grid;
set mxtics 0.1;
set xtics 0.1;

set xlabel "Position x"; set ylabel "Velocity u";
plot [0.0:1.0][:] 'prtl00000000.dat' u 1:5 title 'at t=0' with points lw 8,'prtl$1.dat' u 1:5 title 'at t=10T' with points lw 8;

set terminal png
set output "ShapeChangeV.png"
replot


EOF
