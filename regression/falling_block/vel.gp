#file(eta, vs)=sprintf("outdata-ns%s-p0.2vsound%sxncell10niter40-1.0k_rho0.9rnd/block.vel", eta, vs)
# file(eta, vs)=sprintf("outdata-per%s-p0.2vsound%sxncell10niter40-1.0k_rho0.9rnd/block.vel", eta, vs)

#



set log y

set multiplot
set size square 0.5,0.5


set macros 
vs="30.0"


set origin 0, 0
st="u ($3) w lp"
set key off
plot \
      file("1", vs) @st, \
      file("1e1", vs) @st, \
      file("1e2", vs) @st, \
      file("1e4", vs) @st, \
      file("1e6", vs) @st

set origin 0.5, 0.0
st="u ($4) w lp"
set key off
plot \
      file("1", vs) @st, \
      file("1e1", vs) @st, \
      file("1e2", vs) @st, \
      file("1e4", vs) @st, \
      file("1e6", vs) @st

set origin 0.5, 0.5
unset log y
st="u (-$2) w l"
set key on
set log x
plot [50:] \
      file("1", vs) @st, \
      file("1e1", vs) @st, \
      file("1e2", vs) @st, \
      file("1e4", vs) @st, \
      file("1e6", vs) @st
unset log x

unset multiplot

     