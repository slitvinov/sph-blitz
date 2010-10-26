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

set xlabel "length x"; set ylabel "pressure p";
plot [1.5:2.5][0.0:1.5] 'prtl$1.dat' u 1:4 title 'simu' with line lw 8, 'relError$1.dat' u 1:4 title 'exact' with line lw 8,  'relError$1.dat' u 1:5 axes x1y2 title 'error'with line lw 8;


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

set xlabel "length x"; set ylabel "density rho";
 plot [1.5:2.5][0.0:1.3]  'prtl$1.dat' u 1:3 title 'simu' with line lw 8,'relError$1.dat' u 1:2 title 'exact' with line lw 8,'relError$1.dat' u 1:3 axes x1y2 title 'error'with line lw 8;

set terminal png
set output "Err_rho$1.png"
replot

reset


set terminal postscript eps enhanced color "Helvetica" 26
set output "Err_u$1.eps"

set grid; set key left top
set y2label "(absolute) error";
set y2range [0:1]
set y2tics border
set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; set ylabel "velocity u";
 plot [1.5:2.5][0.0:1.1] 'prtl$1.dat' u 1:5 title 'simu' with line lw 8, 'relError$1.dat' u 1:6 title 'exact' with line lw 8 , 'relError$1.dat' u 1:7 axes x1y2 title 'error'with line lw 8;

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

set xlabel "length x"; set ylabel "internal energy e";
plot [1.5:2.5][0.0:4.0] 'prtl$1.dat' u 1:6 title 'simu' with line lw 8, 'relError$1.dat' u 1:8 title 'exact' with line lw 8, 'relError$1.dat' u 1:9 axes x1y2 title 'error'with line lw 8;

set terminal png
set output "Err_e$1.png"
replot
 
reset

EOF
