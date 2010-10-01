#!/usr/bin/awk -f 
# Analytical solution for the Poiseuille flow
# Input parameters:
# F: gravity acceleration [L T^1]
# nu: kinimatic viscosity [L^2 T^-1]
# L: the length of the domain [L]
# t: the time  [T]
# sym: use symmetry Poiseuille flow (default is 0)
# yidx: the index of y in the input file (default value is 1)
# provide set of y as an input stream 
# 
# Output:
# y v_y
# 
# Usage:
# "normal" poiseuille
# seq 0.0 1e-5 1e-3 | ./poiseuille.awk  -v verbose=1 -v t=0.01 
# "symetic" poiseuille
# seq 0.0 1e-5 2e-3 | ./poiseuille.awk  -v verbose=1 -v t=0.01 -v sym=1


# assert --- assert that a condition is true. Otherwise exit.
function assert(condition, string)
{
    if (! condition) {
	printf("%s:%d: assertion failed: %s\n",
	       FILENAME, FNR, string) > "/dev/stderr"
	_assert_exit = 1
	exit 1
    }
}

END {
    if (_assert_exit)
	exit 1
}


function dprintf(msg) {
    printf ("DEBUG: (polymer.awk) : %s", msg) > "/dev/stderr"
}

function f(y, n,         aux) {
    aux = - (2*n+1)^2 * pi^2 * nu / L^2 * t
    if (aux<-HUGE) {
	return 0.0
    }
    else {
	return 4*F*L^2 / (nu*pi^3*(2*n+1)^3) * sin(pi*y/L * (2*n+1)) * exp(aux)
    }
}

function abs(x) {
    if (x>0)  {return x} else {return -x}
}

BEGIN {
    if (!length(yidx)) {yidx=1}
    if (!length(F)) {F=1e-4}
    if (!length(nu)) {nu=1e-6}
    if (!length(L)) {L=1e-3}
    if (!length(t)) {t=0.1}
    # if varible sym is set we use counter-flowing Poiseuille flows
    assert(t>=0.0, "t must be > 0")

    HUGE=1e2
    pi=3.1416
    eps=1e-15

    if (verbose) {
	dprintf(sprintf("F=%e\n", F))
	dprintf(sprintf("nu=%e\n", nu))
	dprintf(sprintf("L=%e\n", L))
	dprintf(sprintf("t=%e\n", t))
	dprintf(sprintf("sym=%i\n", sym))
	dprintf(sprintf("yidx=%i\n", yidx))
    }
}


{
    if (!sym) {
	y = $(yidx)
	assert(y<=L, "y must be smaller or equal to L")
    } else {
	y_org = $(yidx)
	if ($1>L) {
	    y = $(yidx) - L
	} else {
	    y = $(yidx)
	}
    }
    
    fn = 1e10
    fsum = 0.0
    n=0
    
    if (t==0) {
	fsum = -F/(2*nu) * y * (y - L)
    }
    else {
	while (abs(fn) > eps) {
	    fn = f(y, n)
	    fsum+=fn
	    n++
	}
    }
    
    if (!only) {
	vy = -F/(2*nu) * y * (y - L) - fsum
	if (!sym) {
	    print y, vy
	} else {
	    if (y_org < L) {
		print y_org, vy
	    } else {
		print y_org, -vy
	    }
	}
    } else {
	print -F/(2*nu) * y * (y - L) - fsum
    }
}