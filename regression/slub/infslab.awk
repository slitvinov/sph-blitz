#!/usr/bin/awk -f 

# returns an analytical solution for temperature distribution 
# for infinit slab (see Cleary1999, eq. (35) 

BEGIN {
    if (length(k_l)==0) {
	printf("k_l should be given\n") > "/dev/stderr"
	exit(2)
    }
    if (length(rho_l)==0) {
	printf("rho_l should be given\n") > "/dev/stderr"
	exit(2)
    }
    if (length(cv_l)==0) {
	printf("cv_l should be given\n") > "/dev/stderr"
	exit(2)
    }
    if (length(k_r)==0) {
	# use "left" conductivity if not given
	k_r = k_l
    }
    if (length(rho_r)==0) {
	# use "left" density if not given
	rho_r = rho_l
    }
    if (length(cv_r)==0) {
	# use "left" heat capacity if not given
	cv_r = cv_l
    }
    if (length(Tl)==0) {
	printf("Tl should be given\n") > "/dev/stderr"
	exit(2)
    }
    if (length(Tr)==0) {
	printf("Tr should be given\n") > "/dev/stderr"
	exit(2)
    }
    if (length(xm)==0) {
	printf("xm should be given\n") > "/dev/stderr"
	exit(2)
    }
    if (length(t)==0) {
	printf("t should be given\n") > "/dev/stderr"
	exit(2)
    }
    alpha_l=k_l/(rho_l*cv_l)
    alpha_r=k_r/(rho_r*cv_r)
    printf("alpha_l = %e\n", alpha_l) > "/dev/stderr"
    printf("alpha_r = %e\n", alpha_r) > "/dev/stderr"
    Tc = (Tr-Tl) * sqrt(alpha_l) / ( sqrt(alpha_l) + sqrt(alpha_r) )
    printf("Tc = %e\n", alpha) > "/dev/stderr"
}

NF{
    x=$1
    if (x<xm) {
	T=erfc( (x-xm)/(alpha_l*t) )
    } else {
	T= 1 + sqrt(alpha_l/alpha_r) * erfc( (x-xm)/(alpha_r*t) )
    }
    print x, T
}