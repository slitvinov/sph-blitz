
set terminal postscript eps enhanced color  "Helvetica" 26

set output "Density.eps"

set nokey
set grid;
set xlabel "Density rho"; set ylabel "Position y";
plot [0.985:][-0.5:0.5] 'prtl000001000065.dat' u 5:($2-0.5) notitle with points lw 8;

set terminal png large
set output "Density.png"
replot

reset
