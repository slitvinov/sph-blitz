set output "punto.png"
set terminal png

set key off 
set size sq
plot [-0.5:0.5][0:1] \
     "<awk '$6==1' /tmp/punto.last" w p pt 7, \
     "<awk '$6==2' /tmp/punto.last" w p pt 7
