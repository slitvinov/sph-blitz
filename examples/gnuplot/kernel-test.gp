clear
set terminal  png
set output "../img/kernel-test.png"
set size 0.7,0.7
set nokey
set xlabel "q, distance"
set ylabel "W, kernel value"
set grid
plot "../output/kernel-test.dat" with lines
set terminal postscript eps color
set output "../img/kernel-test.eps"
replot
