#! /usr/bin/awk -f
function isin(x, y,           k) {
    for (k=1; k<=n; k++) {
	if ( (x-x0[k])^2 + (y-y0[k])^2  < R[k]^2 ) return 1
    } 
    return 0
}

{
    n=1
    x0[1]=4
    y0[1]=4
    R[1]=2.0

    vx=0.0
    vy=0.0
}

NR==1{print}

NR==2{print}

NF>2{
    x=$2
    y=$3
    $4=vx
    $5=vy
    if (isin(x, y)) {
	$1="Air"
    } else {
	$1="Water"
    }
    print
}
