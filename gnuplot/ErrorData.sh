#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 


gnuplot << EOF
set terminal postscript eps enhanced color
set output "WholeDomainRho.eps"

set grid;
set xlabel "Supportlength"; set ylabel "Error rho";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:2 title 'L_1' with linespoints, 'ErrorData.dat' u 1:5 title 'L_2' with linespoints, 'ErrorData.dat' u 1:8 title 'L_inf' with linespoints;

set terminal png
set output "WholeDomainRho.png"
replot
reset

set terminal postscript eps enhanced color
set output "WholeDomainU.eps"
set grid;
set xlabel "Supportlength"; set ylabel "Error U";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:3 title 'L_1' with linespoints, 'ErrorData.dat' u 1:6 title 'L_2' with linespoints, 'ErrorData.dat' u 1:9 title 'L_inf' with linespoints;

set terminal png
set output "WholeDomainU.png"
replot
reset

set terminal postscript eps enhanced color
set output "WholeDomainE.eps"

set grid;
set xlabel "Supportlength"; set ylabel "Error e";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:4 title 'L_1' with linespoints, 'ErrorData.dat' u 1:7 title 'L_2' with linespoints, 'ErrorData.dat' u 1:10 title 'L_inf' with linespoints;

set terminal png
set output "WholeDomainE.png"
replot
reset

set terminal postscript eps enhanced color
set output "Area3Rho.eps"

set grid;
set xlabel "Supportlength"; set ylabel "Error rho";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:2 title 'L_1' with linespoints, 'ErrorData.dat' u 1:5 title 'L_2' with linespoints, 'ErrorData.dat' u 1:8 title 'L_inf' with linespoints;

set terminal png
set output "Area3Rho.png"
replot
reset

set terminal postscript eps enhanced color
set output "Area3U.eps"
set grid;
set xlabel "Supportlength"; set ylabel "Error U";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:3 title 'L_1' with linespoints, 'ErrorData.dat' u 1:6 title 'L_2' with linespoints, 'ErrorData.dat' u 1:9 title 'L_inf' with linespoints;

set terminal png
set output "Area3U.png"
replot

set terminal postscript eps enhanced color
set output "Area3E.eps"

set grid;
set xlabel "Supportlength"; set ylabel "Error e";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:4 title 'L_1' with linespoints, 'ErrorData.dat' u 1:7 title 'L_2' with linespoints, 'ErrorData.dat' u 1:10 title 'L_inf' with linespoints;

set terminal png
set output "Area3E.png"
replot





EOF