#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 

mkdir VisualScatterFigures

gnuplot << EOF
set terminal postscript eps enhanced color
set output "VisualScatterFigures/x_y_plane$1.eps"

set grid;
set xlabel "length x"; set ylabel "length y";
plot [1.5:2.5] 'prtl$1.dat' u 1:2 with points;

set terminal png
set output "VisualScatterFigures/x_y_plane$1.png"
replot

reset

set terminal postscript eps enhanced color
set output "VisualScatterFigures/x_rho$1.eps"

set grid;
set xlabel "length x"; set ylabel "density rho";
plot [1.5:2.5][0:1.5] 'prtl$1.dat' u 1:3  with points;

set terminal png
set output "VisualScatterFigures/x_rho$1.png"
replot

reset

set terminal postscript eps enhanced color
set output "VisualScatterFigures/x_p$1.eps"

set grid;
set xlabel "length x"; set ylabel "pressure p";
plot [1.5:2.5][0:1.5] 'prtl$1.dat' u 1:4  with points;

set terminal png
set output "VisualScatterFigures/x_p$1.png"
replot

reset

set terminal postscript eps enhanced color
set output "VisualScatterFigures/x_u$1.eps"

set grid;
set xlabel "length x"; set ylabel "velocity u";
plot [1.5:2.5][0:1.5] 'prtl$1.dat' u 1:5 with points;

set terminal png
set output "VisualScatterFigures/x_u$1.png"
replot

reset

set terminal postscript eps enhanced color
set output "VisualScatterFigures/x_e$1.eps"

set grid;
set xlabel "length x"; set ylabel "energy e";
plot [1.5:2.5][0:3.0] 'prtl$1.dat' u 1:6 with points;

set terminal png
set output "VisualScatterFigures/x_e$1.png"
replot


EOF
