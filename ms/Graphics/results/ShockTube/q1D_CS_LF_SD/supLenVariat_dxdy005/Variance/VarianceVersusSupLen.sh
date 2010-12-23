#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 



gnuplot << EOF
set terminal postscript eps enhanced color "Helvetia" 26
set output "VariancePart1.eps"

set grid;
set key top right;
set format y "10^{%L}"
set logscale y;
set xlabel "Support length l_s"; set ylabel "Variance";
plot [0.015:0.045][:] 'VarianceVersusSuplen.dat' u 1:2 title 'x-position' with linespoints lw 8, 'VarianceVersusSuplen.dat' u 1:3 title 'Density' with linespoints lw 8, 'VarianceVersusSuplen.dat' u 1:5 title 'Velocity' with linespoints lw 8;


set terminal png
set output "VariancePart1.png"
replot

reset

set terminal postscript eps enhanced color "Helvetia" 26
set output "VariancePart2.eps"

set grid;
set key top right;
set format y "10^{%L}"
set logscale y;
set xlabel "Support length l_s"; set ylabel "Variance";
plot [0.015:0.045][:] 'VarianceVersusSuplen.dat' u 1:4 title 'Pressure' with linespoints lw 8, 'VarianceVersusSuplen.dat' u 1:6 title 'Energy' with linespoints lw 8;

set terminal png
set output "VariancePart2.png"
replot

reset


EOF
