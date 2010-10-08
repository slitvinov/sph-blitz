set -e
set -u

cp ../../src/sph sph
./sph taylor-green
../../scripts/dat2punto.sh outdata
awk 'NF{en+=$3**2 + $4**2; n++} !NF{print en/n; en=n=0}' \
    outdata/punto.dat > outdata/kin.dat

gnuplot <<EOF
set terminal postscript 
set output "kin.eps"
set xlabel "time"
set ylabel "E"
set log y
dt=0.01
Re=1.0
plot "outdata/kin.dat" u (\$0*dt):1 w p pt 7 ps 2, \
     exp(-16*pi**2/Re*x)*0.5 t "theory"
EOF