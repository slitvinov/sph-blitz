#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
mkdir Velocity
mkdir Pressure
mkdir Density


gnuplot << EOF
set terminal postscript eps enhanced color
set output "Velocity/$1.eps"

set grid
set title "single wave propagation with reflection and interference"
set xlabel "position"
set ylabel "velocity"
plot [0.0:2.0][-0.06:0.06] "../../src/outdata/prtl$1.dat" u 1:5 w p title " ";

set terminal png
set output "Velocity/$1.png"
replot

reset

set terminal postscript eps enhanced color
set output "Pressure/$1.eps"

set grid
set title "single wave propagation with reflection and interference"
set xlabel "position"
set ylabel "pressure"
plot [0.0:2.0][0.95:1.05] "../../src/outdata/prtl$1.dat" u 1:4 w p title " ";



set terminal png
set output "Pressure/$1.png"
replot

reset


set terminal postscript eps enhanced color
set output "Density/$1.eps"

set grid
set title "single wave propagation with reflection and interference"
set xlabel "position"
set ylabel "density"
plot [0.0:2.0][0.96:1.04] "../../src/outdata/prtl$1.dat" u 1:3 w p title " ";



set terminal png
set output "Density/$1.png"
replot

reset


EOF
