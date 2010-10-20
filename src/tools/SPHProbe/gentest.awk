#!/usr/bin/awk -f 

BEGIN {
    if (length(A)==0) {
	printf("A must be given\n") > "/dev/stderr"
	exit(2)
    }
    if (length(omega)==0) {
	printf("omega must be given\n") > "/dev/stderr"
	exit(2)
    }
    pi = 3.1415926
    Lx = 1.0
    Ly = 2.0
    dx = 0.05
    dy = 0.05
    nx = 20
    ny = 40
    for (i=0; i<nx; i++) {
	for (j=0; j<ny; j++) {
	    x = i*dx
	    y = j*dy
	    v = A*sin(2*pi/Lx * omega * x) 
	    rho = 1.0
	    m = rho * (Lx*Ly) / (nx*ny)
	    print x, y, rho, m, v
	}
    }
}