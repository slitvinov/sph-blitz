set term postscript enhanced
set output "prof-sinusoidal-temperature-inXY.eps"

set key off
set size 0.7, 0.7
set xlabel "x"
set ylabel "T"
sphfile(y, dy, t) = sprintf("<awk -v y=%e -v dy=%e '$2>y&&$2<y+dy' prof.30.%s", y, dy, t)
reffile(y, dy, t) = sprintf("<awk -v y=%e -v dy=%e '$2>y&&$2<y+dy' prof.30.ref.%s", y, dy, t)

t="0.02"
set output sprintf("prof-sinusoidal-temperature-inXY-t%s.eps", t)
plot [0:1][0:1] \
      sphfile(0.5, 0.01, t) u 1:3 w p pt 8, \
      sphfile(0.3, 0.01, t) u 1:3 w p pt 8, \
      sphfile(0.8, 0.01, t) u 1:3 w p pt 8, \
      sphfile(0.1, 0.01, t) u 1:3 w p pt 8, \
      reffile(0.5, 0.01, t) u 1:3 w l lt 1 lw 2, \
      reffile(0.3, 0.01, t) u 1:3 w l lt 1 lw 2, \
      reffile(0.8, 0.01, t) u 1:3 w l lt 1 lw 2, \
      reffile(0.1, 0.01, t) u 1:3 w l lt 1 lw 2

t="0.5"
set output sprintf("prof-sinusoidal-temperature-inXY-t%s.eps", t)
plot [0:1][0:1] \
      sphfile(0.5, 0.01, t) u 1:3 w p pt 8, \
      sphfile(0.3, 0.01, t) u 1:3 w p pt 8, \
      sphfile(0.8, 0.01, t) u 1:3 w p pt 8, \
      sphfile(0.1, 0.01, t) u 1:3 w p pt 8, \
      reffile(0.5, 0.01, t) u 1:3 w l lt 1 lw 2, \
      reffile(0.3, 0.01, t) u 1:3 w l lt 1 lw 2, \
      reffile(0.8, 0.01, t) u 1:3 w l lt 1 lw 2, \
      reffile(0.1, 0.01, t) u 1:3 w l lt 1 lw 2

t="1.0"
set output sprintf("prof-sinusoidal-temperature-inXY-t%s.eps", t)
plot [0:1][0:1] \
      sphfile(0.5, 0.01, t) u 1:3 w p pt 8, \
      sphfile(0.3, 0.01, t) u 1:3 w p pt 8, \
      sphfile(0.8, 0.01, t) u 1:3 w p pt 8, \
      sphfile(0.1, 0.01, t) u 1:3 w p pt 8, \
      reffile(0.5, 0.01, t) u 1:3 w l lt 1 lw 2, \
      reffile(0.3, 0.01, t) u 1:3 w l lt 1 lw 2, \
      reffile(0.8, 0.01, t) u 1:3 w l lt 1 lw 2, \
      reffile(0.1, 0.01, t) u 1:3 w l lt 1 lw 2