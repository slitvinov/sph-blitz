set output "punto.png"
set terminal png

set key off 
plot "<awk '$6==1' /tmp/punto.last", \
     "<awk '$6==2' /tmp/punto.last"
