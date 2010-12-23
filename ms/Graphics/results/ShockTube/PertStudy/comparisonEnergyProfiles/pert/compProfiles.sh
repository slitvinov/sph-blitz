#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
#cp ../../src/outdata/prtl$1.dat prtl$1.dat

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "E_profiles$1.eps"


set grid;
set key top left
set xlabel "Position y"; set ylabel "Internal energy e";
plot [1.5:2.5][0.0:]  'exact$1.dat' u 1:6 title 'exact' with line lt 2 lw 8,'prtl$1.dat' u 1:6 title 'simu' lt 1 with line;

set terminal png large
set output "E_profiles$1.png"
replot

reset

EOF
