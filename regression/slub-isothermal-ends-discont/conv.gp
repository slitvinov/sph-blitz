set term postscript enhanced
set output "conv.eps"
set size 0.7, 0.7
set log 
set style data lp
set key spacing 1.5
set xlabel "N_x"
set xtics (30, 40, 60, 90, 100, 120)
set ytics ("10^{-4}" 1e-4, "10^{-3}" 1e-3, "10^{-2}" 1e-2)

plot [28:130][1e-4:1e-1]\
    "conv.dat" u 1:2 w lp lw 2 t "L_1" ,\
    "" u 1:3 w lp lw 2 t "L_2", \
    "" u 1:4 w lp lw 2 t "L_{inf}", \
    10/x**2 w l lt 2 t "second order"