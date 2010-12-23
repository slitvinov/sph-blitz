#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 



gnuplot << EOF
set terminal postscript eps enhanced color "Helvetia" 26
set output "x_y_plane$1.eps"

set grid;
set xlabel "length x"; set ylabel "length y";
plot [2.05:2.35][0.0:0.015] 'prtl$1.dat' u 1:2 notitle with points;

set terminal png
set output "x_y_plane$1.png"
replot

reset

EOF
