file(eta, vs)= \
	  sprintf("outdata-nr%s-p0.04vsound%sxncell10niter%s-2.0k_rho%seta_media%sgamma2.0ht0.1/block.vel", b_eta, vs, nit, k_rho, eta)

ftitle(eta, vs) = \
	    sprintf("eta=%s, vs=%s", eta, vs)

set macros 
dt=1.0

st='u ($0*dt):(-$2) w lp lw 2 t ftitle(eta, vs)'


xf=1/80
yf=1e10
vel='u ($0*xf):($1*yf)'

set key


set log y

b_eta="1e4"
k_rho="0.9"
nit="20"
set term x11 1
plot [2:150][0.001:] \
     eta="0.005", \
     vs="30.0", file(eta, vs) @st, \
     vs="40.0", file(eta, vs) @st, \
     vs="50.0", file(eta, vs) @st, \
     eta="0.01", \
     vs="30.0", file(eta, vs) @st, \
     vs="40.0", file(eta, vs) @st, \
     vs="50.0", file(eta, vs) @st, \
     eta="0.02", \
     vs="30.0", file(eta, vs) @st, \
     vs="40.0", file(eta, vs) @st, \
     vs="50.0", file(eta, vs) @st, \
     "vel.dat" u ($0*2):($1*2e8) w l lw 3

set term x11 2
k_rho="0.9"
b_eta="1e4"
nit="40"
replot

set term x11 3
k_rho="0.9"
b_eta="1e4"
replot
