file(eta, vs)=sprintf("outdata-ns%s-p0.2vsound%sxncell10niter40-1.0k_rho0.0eta_media0.1/block.vel", eta, vs)
vs="8.0"

set macros
st='u (-$2) w lp lw 3'

plot \
     file("1", vs) @st, \
     file("1e1", vs) @st, \
     file("1e2", vs) @st, \
     file("1e4", vs) @st, \
     file("1e6", vs) @st
