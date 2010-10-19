#!/usr/bin/awk -f 

BEGIN {

    Lx = 1.0
    Ly = 2.0
    dx = 0.1
    dy = 0.1
    nx = 10
    ny = 20
    for (i=0; i<nx; i++) {
	for (j=0; j<ny; j++) {
	    x = i*dx
	    y = j*dy
	    rho = 1.0
	    m = rho * (Lx*Lx) / (nx*ny)
	    v = x*1.13
	    print x, y, rho, m, v
	}
    }
}