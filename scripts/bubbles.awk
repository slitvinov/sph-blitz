#! /usr/bin/awk -f
function isin(x, y,           k) {
    for (k=1; k<=n; k++) {
	if ( (x-x0[k])^2 + (y-y0[k])^2  < R[k]^2 ) return 1
    } 
    return 0
}

{
    n=3
    x0[1]=3
    y0[1]=4
    R[1]=1.0

    x0[2]=6
    y0[2]=5
    R[2]=1.5

    x0[3]=7
    y0[3]=2
    R[3]=1.3
}

NR==1{print}

NR==2{print}

NF>2{
    x=$2
    y=$3
    if (isin(x, y)) {
	$1="Air"
    } else {
	$1="Water"
    }
    print
}
