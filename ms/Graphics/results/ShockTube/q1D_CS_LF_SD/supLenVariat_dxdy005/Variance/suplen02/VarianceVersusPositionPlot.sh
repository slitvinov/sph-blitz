#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 



gnuplot << EOF
set terminal postscript eps enhanced color "Helvetia" 26
set output "Variance$1.eps"

set grid;
set key top left;
set format y "10^{%L}"
set logscale y;
set xlabel "Position x"; set ylabel "Variance";
plot [1.5:2.5][1e-15:] 'variance$1.dat' u 1:4 title 'Density' with line lw 8, 'variance$1.dat' u 1:6 title 'Velocity' with line lw 8;

set terminal png
set output "Variance$1.png"
replot

reset

EOF
