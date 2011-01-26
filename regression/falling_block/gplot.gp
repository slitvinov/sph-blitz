set term png 
set size sq
set output "f1e4-g0.2vsound10.0xncell10niter5-1.0rnd-k_rho0.8.png"
plot [-0.5:0.5][0.0:1.0] \
     "<awk '$11==1 {print $1, $2; print -$1, $2}' $(ls outdata-f1e4-g0.2vsound10.0xncell10niter5-1.0rnd-k_rho0.8/prt*.dat  -1   | tail -n 1)" w p t "" , \
     "<awk '$11==2 {print $1, $2; print -$1, $2}' $(ls outdata-f1e4-g0.2vsound10.0xncell10niter5-1.0rnd-k_rho0.8/prt*.dat  -1   | tail -n 1)" w p t "" 
