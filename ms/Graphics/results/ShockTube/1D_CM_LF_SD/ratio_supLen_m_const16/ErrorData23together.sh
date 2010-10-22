#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 


gnuplot << EOF
set terminal postscript eps enhanced color "Helvetica" 36
set output "WholeDomainRho.eps"

set grid;
set xlabel "Supportlength"; set ylabel "Error rho";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:2 title 'L_1' with linespoints lw 8, 'ErrorData.dat' u 1:5 title 'L_2' with linespoints lw 8, 'ErrorData.dat' u 1:8 title 'L_{inf}' with linespoints lw 8;

set terminal png
set output "WholeDomainRho.png"
replot
reset

set terminal postscript eps enhanced color "Helvetica" 36
set output "WholeDomainU.eps"
set grid;
set xlabel "Supportlength"; set ylabel "Error U";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:3 title 'L_1' with linespoints lw 8, 'ErrorData.dat' u 1:6 title 'L_2' with linespoints lw 8, 'ErrorData.dat' u 1:9 title 'L_{inf}' with linespoints lw 8;

set terminal png
set output "WholeDomainU.png"
replot
reset

set terminal postscript eps enhanced color "Helvetica" 36
set output "WholeDomainE.eps"

set grid;
set xlabel "Supportlength"; set ylabel "Error e";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:4 title 'L_1' with linespoints lw 8, 'ErrorData.dat' u 1:7 title 'L_2' with linespoints lw 8, 'ErrorData.dat' u 1:10 title 'L_{inf}' with linespoints lw 8;

set terminal png
set output "WholeDomainE.png"
replot
reset

set terminal postscript eps enhanced color "Helvetica" 36
set output "Area3Rho.eps"

set grid;
set xlabel "Supportlength"; set ylabel "Error rho";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:11 title 'L_{1,3}' with linespoints lw 8, 'ErrorData.dat' u 1:14 title 'L_{2,3}' with linespoints lw 8, 'ErrorData.dat' u 1:17 title 'L_{inf,3}' with linespoints lw 8, 'ErrorData.dat' u 1:20 title 'L_{1,2}' with linespoints lw 8, 'ErrorData.dat' u 1:23 title 'L_{2,2}' with linespoints lw 8, 'ErrorData.dat' u 1:26 title 'L_{inf,2}' with linespoints lw 8;

set terminal png
set output "Area23Rho.png"
replot
reset

set terminal postscript eps enhanced color "Helvetica" 36
set output "Area3U.eps"
set grid;
set xlabel "Supportlength"; set ylabel "Error U";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:12 title 'L_{1,3}' with linespoints lw 8, 'ErrorData.dat' u 1:15 title 'L_{2,3}' with linespoints lw 8, 'ErrorData.dat' u 1:18 title 'L_{inf,3}' with linespoints lw 8,  'ErrorData.dat' u 1:21 title '{L_1,2}' with linespoints lw 8, 'ErrorData.dat' u 1:24 title 'L_{2,2}' with linespoints lw 8, 'ErrorData.dat' u 1:27 title 'L_{inf,2}' with linespoints lw 8;
set terminal png
set output "Area23U.png"
replot

set terminal postscript eps enhanced color "Helvetica" 36
set output "Area23E.eps"

set grid;
set xlabel "Supportlength"; set ylabel "Error e";
set logscale x
set logscale y
set format y "10^{%L}"

plot [:][:] 'ErrorData.dat' u 1:13 title 'L_{1,3}' with linespoints lw 8, 'ErrorData.dat' u 1:16 title 'L_{2,3}' with linespoints lw 8, 'ErrorData.dat' u 1:19 title 'L_{inf,3}' with linespoints lw 8, 'ErrorData.dat' u 1:22 title 'L_{1,2}' with linespoints lw 8, 'ErrorData.dat' u 1:25 title 'L_{2,2}' with linespoints lw 8, 'ErrorData.dat' u 1:28 title 'L_{inf,2}' with linespoints lw 8;

set terminal png
set output "Area23E.png"
replot

EOF