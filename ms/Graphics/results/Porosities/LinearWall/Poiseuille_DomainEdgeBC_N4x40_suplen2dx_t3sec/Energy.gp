
set terminal postscript eps enhanced color  "Helvetica" 26

set output "Energy.eps"

set nokey
set grid;
set xlabel "Internal Energy e"; set ylabel "Position y";
plot [2.5:][-0.5:0.5] 'prtl000001000065.dat' u 6:($2-0.5) notitle with points lw 8;

set terminal png large
set output "Energy.png"
replot

reset
