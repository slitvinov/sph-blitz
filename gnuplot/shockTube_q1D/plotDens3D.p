



set xlabel "length x"; set ylabel "length y"; set zlabel "density";
splot [1.5:2.5][-0.03:0.06][0.0:1.4] 'prtl.dat' u 1:2:3 title 'SPH' w p;

