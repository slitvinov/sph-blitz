



set xlabel "length x"; set ylabel "length y"; set zlabel "internal energy";
splot [1.5:2.5][-0.03:0.06][1.0:3.0] 'prtl.dat' u 1:2:6 title 'SPH' w p;

