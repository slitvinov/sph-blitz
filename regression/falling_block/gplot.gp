set term png 
set size sq
set output "fb100.png"
plot "<awk '$11==1 {print $1, $2; print -$1, $2}' $(ls outdata100/prt*.dat  -1   | tail -n 1)" w p t "" , \
     "<awk '$11==2 {print $1, $2; print -$1, $2}' $(ls outdata100/prt*.dat  -1   | tail -n 1)" w p t ""

set output "fb1.png"
plot "<awk '$11==1 {print $1, $2; print -$1, $2}' $(ls outdata0/prt*.dat  -1   | tail -n 1)" w p t "" , \
     "<awk '$11==2 {print $1, $2; print -$1, $2}' $(ls outdata0/prt*.dat  -1   | tail -n 1)" w p t "" 

set output "fb10000.png"
plot "<awk '$11==1 {print $1, $2; print -$1, $2}' $(ls outdata10000/prt*.dat  -1   | tail -n 1)" w p t "", \
     "<awk '$11==2 {print $1, $2; print -$1, $2}' $(ls outdata10000/prt*.dat  -1   | tail -n 1)" w p t ""

set output "fb10.png"
plot "<awk '$11==1 {print $1, $2; print -$1, $2}' $(ls outdata10/prt*.dat  -1   | tail -n 1)" w p t "", \
     "<awk '$11==2 {print $1, $2; print -$1, $2}' $(ls outdata10/prt*.dat  -1   | tail -n 1)" w p t ""

