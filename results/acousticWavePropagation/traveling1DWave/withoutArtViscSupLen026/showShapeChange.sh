#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 

gnuplot << EOF
set terminal postscript eps enhanced color
set output "Visualization/ShapeChangeP.eps"

set key right bottom
set grid;
set title "damping for 1D velocity oscillation"
set mxtics 1.0;
set xtics 1.0;

set xlabel "position"; set ylabel "pressure";
plot [0.0:1.0][:] 'prtl00000000.dat' u 1:4 title 'at t=0' with points,'prtl$1.dat' u 1:4 title 'at t=$1 ms' with points ;

set terminal png giant
set output "Visualization/ShapeChangeP.png"
replot

reset

set terminal postscript eps enhanced color
set output "Visualization/ShapeChangeV.eps"

set key right bottom
set grid;
set title "damping for 1D velocity oscillation"
set mxtics 1.0;
set xtics 1.0;

set xlabel "position"; set ylabel "velocity";
plot [0.0:1.0][:] 'prtl00000000.dat' u 1:5 title 'at t=0' with points lw 3,'prtl$1.dat' u 1:5 title 'at t=$1 ms' with points lw 3 ;

set terminal png giant
set output "Visualization/ShapeChangeV.png"
replot

reset

set terminal postscript eps enhanced color
set output "Visualization/ShapeChangeRho.eps"

set key right bottom
set grid;
set title "damping for 1D velocity oscillation"
set mxtics 1.0;
set xtics 1.0;

set xlabel "position"; set ylabel "density";
plot [0.0:1.0][:] 'prtl00000000.dat' u 1:3 title 'at t=0' with points,'prtl$1.dat' u 1:3 title 'at t=$1 ms' with points ;

set terminal png
set output "Visualization/ShapeChangeRho.png"
replot

reset

EOF
