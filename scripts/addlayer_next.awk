#! /usr/bin/awk -f

BEGIN {
    x0=4.0
    y0=7.98
    dx=0.0818899999999996

    if (length(n)==0) {
	printf("n should be given\n") > "/dev/stderr"
	exit
    }
    
    rho=1.0
    p=15.0
    T=1.0
    # number of removed water particles 
    irem=0
}

NR==1{
    print
}

# number of particles
NR==2 {
    print $1
}

# all lines
NR>2 {
    if (($1=="Water") && (irem<n) ) {
	irem++
    } else {
	print 
    }
}

END {
    for (k=0; k<n; k++) {
	vy = -rand();
	vx = 2.0*rand() - 1.0;
	print "Air", x0 + dx*k + 0.25*dx*rand(), y0, vx, vy, rho, p, T
    }
}
