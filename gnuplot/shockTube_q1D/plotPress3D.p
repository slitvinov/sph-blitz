



set xlabel "length x"; set ylabel "length y"; set zlabel "pressure";
splot [1.5:2.5][-0.03:0.06][0.0:1.1] 'prtl.dat' u 1:2:4 title 'SPH' w p;

