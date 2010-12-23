#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 

gnuplot << EOF
set terminal postscript eps enhanced color "Helvetica" 26
set output "Err_p$1.eps"


set grid; set key left top
set y2label "(absolute) error";
set y2range [0:1]
set y2tics border
set mxtics 0.05;
set xtics 0.25;

set xlabel "Position x"; set ylabel "Pressure p";
plot [1.5:2.5][0.0:1.5] 'prtl$1.dat' u 1:4 title 'Simulation' with line lw 8, 'relError$1.dat' u 1:4 title 'Exact' with line lw 8,  'relError$1.dat' u 1:5 axes x1y2 title 'error'with line lw 8;


set terminal png
set output "Err_p$1.png"
replot

reset

set terminal postscript eps enhanced color "Helvetica" 26
set output "Err_rho$1.eps"

set grid; set key left top
set y2label "(absolute) error";
set y2range [0:1]
set y2tics border
set mxtics 0.05;
set xtics 0.25;

set xlabel "Position x"; set ylabel "Density rho";
 plot [1.5:2.5][0.0:1.3]  'prtl$1.dat' u 1:3 title 'Simulation' with line lw 8,'relError$1.dat' u 1:2 title 'Exact' with line lw 8,'relError$1.dat' u 1:3 axes x1y2 title 'error'with line lw 8;

set terminal png
set output "Err_rho$1.png"
replot

reset


set terminal postscript eps enhanced color "Helvetica" 26
set output "Err_u$1.eps"

set grid; set key 1.95,1.08
#set y2label "(absolute) error";
#set y2range [0:1]
#set y2tics border
set mxtics 0.05;
set xtics 0.25;

set xlabel "Position x"; set ylabel "Velocity u, Error (absolute)";
 plot [1.5:2.5][0.0:1.1]  'relError$1.dat' u 1:6 title 'Exact' with line lt 2 lw 8, 'prtl$1.dat' u 1:5 title 'Simulation' with line lt 1 lw 8, 'relError$1.dat' u 1:7  title 'Error' with line lw 8;

set terminal png
set output "Err_u$1.png"
replot
 
reset


set terminal postscript eps enhanced color "Helvetica" 26
set output "Err_e$1.eps"

set grid; set key left top
set y2label "(absolute) error";
set y2range [0:1]
set y2tics border
set mxtics 0.05;
set xtics 0.25;

set xlabel "Position x"; set ylabel "Internal energy e";
plot [1.5:2.5][0.0:4.0] 'prtl$1.dat' u 1:6 title 'Simulation' with line lw 8, 'relError$1.dat' u 1:8 title 'Exact' with line lw 8, 'relError$1.dat' u 1:9 axes x1y2 title 'error'with line lw 8;

set terminal png
set output "Err_e$1.png"
replot
 
reset

EOF
