set term postscript enhanced
set output "prof-sinusoidal-temperature.eps"

set key off
set size 0.7, 0.7
set xlabel "x"
set ylabel "T"
plot [0:1][:] \
     "prof.30.0.02" w p pt 8 t "", "prof.30.ref.0.02" w l, \
     "prof.30.0.5" w p pt 9 t "", "prof.30.ref.0.5" w l, \
     "prof.30.1.5" w p pt 10 t "", "prof.30.ref.1.5" w l