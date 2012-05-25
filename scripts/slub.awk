#! /usr/bin/awk -f
BEGIN {
    cx=32
    cutoff=0.25
    Lx=cx*cutoff

    rho_w = 1e3
    rho_a = 1.0

    e_w = 1.0
    e_a = 0.0
}

NR==1{print}

NR==2{print}

NF>2{
    x=$2
    y=$3
    if (x<0.5*Lx) {
	$1="Air"
	$6=rho_a
	$8=e_a
    } else {
	$1="Water"
	$6=rho_w
	$8=e_w
    }
    print
}
