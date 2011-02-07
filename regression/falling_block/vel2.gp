file(eta, nc, vs)= \
	  sprintf("outdata-nr%s-p0.2vsound%sxncell%sniter40-1.0k_rho0.0eta_media0.1gamma1.0/block.vel", eta, vs, nc)

file2(eta, nc, vs)= \
	  sprintf("outdata-nr%s-p0.2vsound%sxncell%sniter10-1.0k_rho0.0eta_media0.1gamma1.0/block.vel", eta, vs, nc)


tmax=30.0
tmin=0.0
dt=0.1

set multiplot
set size 1.0, 0.5
set origin 0, 0
set macros
unset log y

st='u ($0*dt):(-$2) w l lw 3'
set key on
vs="14.0"
nc="10"
plot [tmin:tmax] \
     file("1", nc, vs) @st, \
     file("1e1", nc, vs) @st, \
     file("1e2", nc, vs) @st, \
     file("1e4", nc, vs) @st, \
     file("1e6", nc, vs) @st

set origin 0.0, 0.5
vs="14.0"
nc="10"
set key off
plot [tmin:tmax]\
     file2("1", nc, vs) @st, \
     file2("1e1", nc, vs) @st, \
     file2("1e2", nc, vs) @st, \
     file2("1e4", nc, vs) @st, \
     file2("1e6", nc, vs) @st


unset multiplot
