set term png 
set size sq
set output "f1000bigRe-g20.0vsound10.0niter5.png"
plot [-0.5:0.5][0.0:1.0] \
     "<awk '$11==1 {print $1, $2; print -$1, $2}' $(ls outdata-f1000bigRe-g20.0vsound10.0niter5/prt*.dat  -1   | tail -n 1)" w p t "" , \
     "<awk '$11==2 {print $1, $2; print -$1, $2}' $(ls outdata-f1000bigRe-g20.0vsound10.0niter5/prt*.dat  -1   | tail -n 1)" w p t "" 
