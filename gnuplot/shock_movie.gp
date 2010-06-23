# show 'movie' 
# key n: next snapshots
# key p: previous snapshots

n=0
plot "punto.dat" u 1:2 every :::n::n w p pt 2  t sprintf("n=%.6i", n)

bind "p" "n=n-1; replot"
bind "n" "n=n+1; replot"
