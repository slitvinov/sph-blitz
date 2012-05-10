#! /usr/bin/awk -f
function isin(xp, yp,           k) {

    for (k=1; k<=n; k++) {
	if ( (xp>x1[k]) && (xp<x2[k]) && (yp>y1[k]) && (yp<y2[k]) ) return 1
    } 
    return 0
}


BEGIN {
    cx=64
    cy=35
    cutoff=0.25
    Lx=cx*cutoff
    Ly=cy*cutoff
    # channel width
    s = (cy - 3)/2 * cutoff

    n=3
    # center
    x1[1]=0
    x2[1]=Lx-s
    y1[1]=(int(cy/2))*cutoff
    y2[1]=(int(cy/2)+1)*cutoff

    # bottom
    x1[2]=s
    x2[2]=Lx
    y1[2]=(cy-1)*cutoff
    y2[2]=Ly

    # top
    x1[3]=s
    x2[3]=Lx
    y1[3]=0
    y2[3]=cutoff
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
    x=$2
    y=$3
    if (isin(x, y)) {
	$1="Wall"
    } 
    print
}

