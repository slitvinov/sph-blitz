

set multiplot;                          # get into multiplot mode
set grid;
set y2label "(absolute) error";

set size 0.5,0.5;
set origin 0.0,0.0;
set y2range [0:1];
set y2tics border;
set mxtics 0.05;
set xtics 0.25;





set xlabel "length x"; set ylabel "pressure p";
plot [1.5:2.5][0.0:1.5] 'relError00200000.dat' u 1:4 title "exact" with line, 'prtl00200000.dat' u 1:4 title 'simu' with line, 'relError00200000.dat' u 1:5 axes x1y2 title 'error'with line;

set size 0.5,0.5; 
set origin 0.5,0.0;

set xlabel "length x"; set ylabel "density rho";
plot [1.5:2.5][0.0:1.3] 'relError00200000.dat' u 1:2 title 'exact' with line, 'prtl00200000.dat' u 1:3 title 'simu' with line, 'relError00200000.dat' u 1:3 axes x1y2 title 'error'with line;

set size 0.5,0.5; 
set origin 0.0,0.5;

set xlabel "length x"; set ylabel "velocity u";
plot [1.5:2.5][-0.5:1.1] 'relError00200000.dat' u 1:6 title 'exact'  with line , 'prtl00200000.dat' u 1:5 title 'simu' with line, 'relError00200000.dat' u 1:7 axes x1y2 title 'error'with line;

set size 0.5,0.5; 
set origin 0.5,0.5;

set xlabel "length x"; set ylabel "internal energy e";
plot [1.5:2.5][0.0:4.0] 'relError00200000.dat' u 1:8 title 'exact' with line, 'prtl00200000.dat' u 1:6 title 'simu' with line, 'relError00200000.dat' u 1:9 axes x1y2 title 'error'with line;

unset multiplot                         # exit multiplot mode
