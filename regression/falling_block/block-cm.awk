($11==2) && ($2>0.0) && ($2 < 1.0) {
    ip++
    # store block particles
    x[ip]=$1
    y[ip]=$2
    
    xcm+=$1
    ycm+=$2

    vx[ip]=$5
    vy[ip]=$6
}

!NF{
    xcm = xcm / ip
    ycm = ycm / ip
    for (i=1; i<=ip; i++) {
	print x[i] - xcm, y[i] - ycm, vx[i], vy[i]
    }
    printf "\n"
    ip=xcm=ycm=0.0
}
