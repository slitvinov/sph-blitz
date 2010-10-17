#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
mkdir CompResFigures

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "pressure.eps"


set border lw 3;
set grid lw 3;
set mxtics;
set xtics;
#lw sets line width (1= normal)
set xlabel "length x"; set ylabel "pressure p";
plot [-0.5:0.5][0.0:1.1] 'dataStep$1.txt' u 1:4 title 'Simulation' with line lw 8,"compData/ExactResultsN80.txt" using 1:3 title 'Exact' with line lw 8;

#### large for large fonts, options: tiny , small , medium,large, giant (does not work for postscript)

set terminal png large 
set output "pressure.png"
replot

reset


set terminal postscript eps enhanced color "Helvetica" 26
set output "velocity.eps"

set border lw 3;
set grid;
set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; set ylabel "velocity u"; 
plot [-0.5:0.5][0.0:1.15] 'dataStep$1.txt' u 1:5 title'Simulation' with line lw 8,"compData/ExactResultsN80.txt" using 1:4 title 'Exact' with line lw 8;

set terminal png  large 
set output "velocity.png"
replot

reset


set terminal postscript eps enhanced color "Helvetica" 26
set output "density.eps"

set border lw 3;
set grid;
set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; set ylabel "density rho";
plot [-0.5:0.5][0.0:1.1] 'dataStep$1.txt' u 1:3 title 'Simulation' with line lw 8, "compData/ExactResultsN80.txt" using 1:2 title 'Exact' with line lw 8;

set terminal png  large 
set output "density.png"
replot
 
reset


set terminal postscript eps enhanced color "Helvetica" 26
set output "energy.eps"

set border lw 3;
set grid;
set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; set ylabel "internal energy e";
plot [-0.5:0.5][0.0:4.0] 'dataStep$1.txt' u 1:6 title 'Simulation' with line lw 8, "compData/ExactResultsN80.txt" using 1:5 title 'Exact' with line lw 8;

set terminal png  large 
set output "energy.png"
replot
 
reset

EOF

