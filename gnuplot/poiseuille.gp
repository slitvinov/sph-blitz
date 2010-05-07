set term png
set output "gnuplot/po-gnuplot.png"
set size 0.8, 0.8

set xlabel "y"
set ylabel "v_x" offset 2

set xtics (0.0, 0.01, 0.02, 0.03, 0.04)

plot [][:0.045] \
     n=1, A=80.0, L=0.04, \
     'src/outdata/punto.dat' u 2:3 every :::n::n w p pt 6 ps 3 t "velocity of SPH particles", \
     A*x*(L-x) w l lw 3 t "steady state velocity"