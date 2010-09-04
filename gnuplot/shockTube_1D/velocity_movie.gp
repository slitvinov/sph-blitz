# show 'movie' 
# key n: next snapshots
# key p: previous snapshots

n=0
set title "Movie of 1D shock with 2D particle distribution \n \n (press <n> for next image, <p> for previous image)"
set xlabel "position x"
set ylabel "velocity"

plot [1.5:2.5][]"punto.dat" u 1:5 every :::n::n w p pt 2  t sprintf("n=%.6i", n)

# do not go below zero
bind "p" "n=n>0?n-1:0; replot"

bind "n" "n=n+1; replot"
