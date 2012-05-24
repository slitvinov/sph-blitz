#! /usr/bin/awk -f
BEGIN {
    k_r = 1.0
    k_l = 0.0
    cx=8
    cutoff=0.25
    Lx=cx*cutoff
}

NR==1{print}

NR==2{print}

NF>2{
    x=$2
    y=$3
    if (x>Lx/2.0) {
	$8=k_r
    } else {
	$8=k_l
    }
    print
}
