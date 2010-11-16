set term postscript enhanced
set output "conv-dis.eps"
set size 0.7, 0.7
set log 
set style data lp
set key spacing 1.5
set xlabel "N_x"
set xtics (30, 40, 60, 90, 100, 120)
set ytics ("10^{-4}" 1e-4, "1x10^{-3}" 1e-3, "5x10^{-3}" 5e-3)

plot [40:110][3e-4:6e-3]\
    "conv.dat.0.0" u 1:2 w lp lw 2 t "0.0", \
    "conv.dat.0.01" u 1:2 w lp lw 2 t "0.05", \
    "conv.dat.0.05" u 1:2 w lp lw 2 t "0.05", \
    "conv.dat.0.1" u 1:2 w lp lw 2 t "0.1", \
        3/x**2 w l lt 1 t "", \
        0.1/x w l lt 1 t ""
	
