$11==2 {
    ip++
    # store block particles
    x[ip]=$1
    y[ip]=$2
    
    xcm+=$1
    ycm+=$2
}

!NF{
    xcm = xcm / ip
    ycm = ycm / ip
    for (i=1; i<=ip; i++) {
	print x[i] - xcm, y[i] - ycm
    }
    printf "\n"
    ip=xcm=ycm=0.0

}