set terminal postscript enhance
set output "conv.eps"
plot "conv.dat" w lp ps 2 pt 7

set xlabel "x"
set ylabel "v_y"
set output "prof.eps"
plot "prof.3", "<sort -g prof.3.ref" w l t "theory"