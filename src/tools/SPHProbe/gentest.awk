#!/usr/bin/awk -f 

BEGIN {

    Lx = 1.0
    Ly = 1.0
    dx = 0.1
    dy = 0.1
    n = 10
    for (i=0; i<n; i++) {
	for (j=0; j<n; j++) {
	    x = i*dx
	    y = j*dy
	    rho = 1.0
	    m = rho * Lx * Lx / (n*n)
	    rho = 1.0
	    
	    v = x
	    print x, y, rho, m, v
	}
    }
}