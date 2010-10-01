#!/usr/bin/awk -f

# Analytical solution for the Couette flow
# Input parameters:
# V0: velocity of the wall
# nu: kinimatic viscosity [L^2 T^-1]
# L: the length of the domain
# t: the time 
# yidx: the index of y in the input file (default value is 1)
# provide set of y as an input stream 
# the wall with y=L is moving and has velocity V0
# 
# Output:
# y v_y
# 
# Usage:
# seq 0.0 1e-4 1e-3 | ./couette.awk -v t=0.03 

function f(y, n) {
    return 2*V0 / (n*pi) * (-1)^n * sin(n*pi/L*y) * exp (-nu*n^2*pi^2/L^2*t)
}

function abs(x) {
    if (x>0) {
	return x
    } 
    else {
	return -x
    }
}

BEGIN {
    # maximum number of terms in the summation
    nmax = 1e6
    # where to find idx in the input file
    if (!length(yidx)) {yidx=1}
    if (!length(V0)) {V0=1.25e-5}
    if (!length(nu)) {nu=1.0e-6}
    if (!length(L)) {L=1e-3}
    if (L<0.0) {
	printf "L cannot be negative\n" > "/dev/stderr"
	exit(-1)
    }
    if (!length(t)) {t=0.1}
    if (t<0.0) {
	printf "time cannot be negative\n" > "/dev/stderr"
	exit(-1)
    }

    pi=3.1416
    if (!length(eps)) {eps=1e-18}

    if (verbose) {
	printf("yidx = %i\n", yidx) > "/dev/stderr"
	printf("V0 = %5.2e\n", V0) > "/dev/stderr"
	printf("nu = %5.2e\n", nu) > "/dev/stderr"
	printf("L = %5.2e\n", L) > "/dev/stderr"
	printf("t = %5.2e\n", t) > "/dev/stderr"
	printf("eps = %5.2e\n", eps) > "/dev/stderr"
    }
}

{
    y = $(yidx)
    if (y>L) {
	printf "y cannot be bigger then L\n"  > "/dev/stderr"
	exit(-1)
    }
    fn = 1e10
    fsum = 0.0
    n=1
    if (t==0) {
	fsum=-V0/L*y
    }
    else {
	while (abs(fn) > eps) {
	    fn = f(y, n)
	    fsum+=fn
	    n++
	    if (n>nmax) {
		printf("the sum does not convergs\n") > "/dev/stderr"
		printf("y = %5.2e\n"),  y> "/dev/stderr"
		exit(-2)
	    }
	}
    }
    print y, V0/L*y + fsum
}