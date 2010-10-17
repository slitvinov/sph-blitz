

set multiplot;                          # get into multiplot mode
set size 0.5,0.5;
set origin 0.0,0.0;

set xlabel "length x"; set ylabel "pressure p";
plot [-0.5:0.5][0.0:1.1] 'dataStep000080.txt' u 1:4 title 'Simulation' with line,"compData/ExactResultsN80.txt" using 1:3 title 'Exact' with line;
#,"compData/dataStep80.txt" using 1:3 title '(2.18)' with line;


set size 0.5,0.5; 
set origin 0.5,0.0;

set xlabel "length x"; set ylabel "density rho";
plot [-0.5:0.5][0.0:1.3] 'dataStep000080.txt' u 1:3 title 'Simulation' with line,
"compData/ExactResultsN80.txt" using 1:2 title 'Exact' with line;
#,"compData/dataStep80.txt" using 1:2 title '(2.18)' with line;

set size 0.5,0.5; 
set origin 0.0,0.5;

set xlabel "length x"; set ylabel "velocity u"; 
plot [-0.5:0.5][0.0:1.3] 'dataStep000080.txt' u 1:5 title'Simulation' with line,
"compData/ExactResultsN80.txt" using 1:4 title 'Exact' with line;
#,"compData/dataStep80.txt" using 1:4 title '(2.18)' with line;

set size 0.5,0.5; 
set origin 0.5,0.5;

set xlabel "length x"; set ylabel "internal energy e";
plot [-0.5:0.5][0.0:4.0] 'dataStep000080.txt' u 1:6 title 'Simulation' with line,
"compData/ExactResultsN80.txt" using 1:5 title 'Exact' with line;
#,"compData/dataStep80.txt" using 1:5 title '(2.18)' with line;

unset multiplot                         # exit multiplot mode
