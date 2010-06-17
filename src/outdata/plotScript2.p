set multiplot;                          # get into multiplot mode
set size 0.5,0.5;
set origin 0.0,0.0;

set xlabel "length x"; set ylabel "pressure p";
plot [0.5:1.5][0.0:1.1] 'prtl.dat' u 1:3 title 'C' with line,"compData/ExactResultsN80.txt" using 1:3 title 'Exact' with line;


set size 0.5,0.5; 
set origin 0.5,0.0;

set xlabel "length x"; set ylabel "density rho";  plot [0.5:1.5][0.0:1.3] 'prtl.dat' u 1:2 title 'C' with line,"compData/ExactResultsN80.txt" using 1:2 title 'Exact' with line;

set size 0.5,0.5; 
set origin 0.0,0.5;

set xlabel "length x"; set ylabel "velocity u";  plot [0.5:1.5][0.0:1.1] 'prtl.dat' u 1:4 title'C' with line,"compData/ExactResultsN80.txt" using 1:4 title 'Exact' with line;

set size 0.5,0.5; 
set origin 0.5,0.5;

set xlabel "length x"; set ylabel "internal energy e";  plot [0.5:1.5][0.0:4.0] 'prtl.dat' u 1:5 title 'C' with line,"compData/ExactResultsN80.txt" using 1:5 title 'Exact' with line;

unset multiplot                         # exit multiplot mode


