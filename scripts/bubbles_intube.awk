#! /usr/bin/awk -f
function isin(xp, yp,           k) {
    for (k=1; k<=n; k++) {
	if ( (xp-x0[k])^2 + (yp-y0[k])^2  < R[k]^2 ) return 1
    } 
    return 0
}

{
    rho_w = 1e3
    rho_a = 1.0
    cx=64
    cy=35
    cutoff=0.25
    Lx=cx*cutoff
    Ly=cy*cutoff


    n=0
    for (q=1; q<=4; q++) {
	n++
	x0[n]=0.35*q*Ly
	y0[n]=0.25*Ly
	R[n]=4*cutoff
	
	n++
	x0[n]=0.35*q*Ly
	y0[n]=0.75*Ly
	R[n]=4*cutoff
    }

}

NR==1{print}

NR==2{print}

NF>2{
    x=$2
    y=$3
    if ($1=="Wall") {
	# do nothing
	$6=rho_w
    } else if (isin(x, y)) {
	$1="Air"
	$6=rho_a
    } else {
	$1="Water"
	$6=rho_w
    }
    print
}
