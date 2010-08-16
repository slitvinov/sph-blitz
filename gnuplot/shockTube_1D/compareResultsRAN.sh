#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
mkdir CompResFigures
cp ../../src/outdata/prtl$1.dat prtl$1.dat
cp ../../src/outdata/prtl00000000.dat prtl00000000.dat
mkdir particlePositionsAndCo

gnuplot << EOF
set terminal postscript eps enhanced color
set output "CompResFigures/Err_p$1.eps"


set grid;
set y2label "(absolute) error";
set y2range [0:1]
set y2tics border
set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; set ylabel "pressure p";
plot [1.5:2.5][0.0:1.5] 'relError$1.dat' u 1:4 title 'exact' with line, 'prtl$1.dat' u 1:4 title 'simu' with line, 'relError$1.dat' u 1:5 axes x1y2 title 'error'with line;


set terminal png
set output "CompResFigures/Err_p$1.png"
replot

reset

set terminal postscript eps enhanced color
set output "CompResFigures/Err_rho$1.eps"

set grid;
set y2label "(absolute) error";
set y2range [0:1]
set y2tics border
set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; set ylabel "density rho";
plot [1.5:2.5][0.0:1.3] 'relError$1.dat' u 1:2 title 'exact' with line, 'prtl$1.dat' u 1:3 title 'simu' with line, 'relError$1.dat' u 1:3 axes x1y2 title 'error'with line;

set terminal png
set output "CompResFigures/Err_rho$1.png"
replot

reset


set terminal postscript eps enhanced color
set output "CompResFigures/Err_u$1.eps"

set grid;
set y2label "(absolute) error";
set y2range [0:1]
set y2tics border
set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; set ylabel "velocity u";
plot [1.5:2.5][0.0:1.1] 'relError$1.dat' u 1:6 title 'exact' with line , 'prtl$1.dat' u 1:5 title 'simu' with line, 'relError$1.dat' u 1:7 axes x1y2 title 'error'with line;

set terminal png
set output "CompResFigures/Err_u$1.png"
replot
 
reset


set terminal postscript eps enhanced color
set output "CompResFigures/Err_e$1.eps"

set grid;
set y2label "(absolute) error";
set y2range [0:1]
set y2tics border
set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; set ylabel "internal energy e";
plot [1.5:2.5][0.0:4.0] 'relError$1.dat' u 1:8 title 'exact' with line, 'prtl$1.dat' u 1:6 title 'simu' with line, 'relError$1.dat' u 1:9 axes x1y2 title 'error'with line;

set terminal png
set output "CompResFigures/Err_e$1.png"
replot
 
reset

set terminal postscript eps enhanced color
set output "particlePositionsAndCo/pos00000000.eps"

set grid;

set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; 
plot [1.9:2.1][-0.05:0.05] 'prtl00000000.dat' u 1:2 title 'particles' with points;

set terminal png
set output "particlePositionsAndCo/pos00000000.png"
replot
 
reset

set terminal postscript eps enhanced color
set output "particlePositionsAndCo/pos$1.eps"

set grid;

set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; 
plot [1.9:2.1][-0.05:0.05] 'prtl$1.dat' u 1:2 title 'particles' with points;

set terminal png
set output "particlePositionsAndCo/pos$1.png"
replot
 
reset


set terminal postscript eps enhanced color
set output "particlePositionsAndCo/mass00000000.eps"

set grid;

set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; set ylabel "particle mass m";
plot [1.5:2.5] 'prtl00000000.dat' u 1:8 title 'particles' with points;

set terminal png
set output "particlePositionsAndCo/mass00000000.png"
replot
 
reset


set terminal postscript eps enhanced color
set output "particlePositionsAndCo/rho00000000.eps"

set grid;

set mxtics 0.05;
set xtics 0.25;

set xlabel "length x"; set ylabel "density rho";
plot [1.5:2.5][0.0:1.3] 'prtl00000000.dat' u 1:3  with line;

set terminal png
set output "particlePositionsAndCo/rho00000000.png"
replot

EOF
