set -e
set -u

cp ../../src/sph sph
./sph taylor-green
../../scripts/dat2punto.sh outdata
awk 'NF{en+=$3**2 + $4**2; n++} !NF{print en/n; en=n=0}' outdata/punto.dat > outdata/kin.dat

gnuplot <<EOF
set terminal postscript 
set output "kin.eps"
set log y
plot "outdata/kin.dat" w lp pt 7 ps 2
EOF