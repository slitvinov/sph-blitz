set term postscript enhanced
set output "prof-slab-h.eps"

set size 0.7, 0.7
set xlabel "x"
set ylabel "T"
plot "prof.120.ref" w l lw 2 t "analytical solution", \
     "prof.120" w p ps 1 pt 7 t "SPH solution"