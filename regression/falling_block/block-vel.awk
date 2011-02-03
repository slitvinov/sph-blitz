NF{
    n++
    vxsum+=$3
    vysum+=$4
    
    vx_sq_sum+=$3^2
    vy_sq_sum+=$4^2
}

!NF{
    vx_av=vxsum/n
    vy_av=vysum/n
    print vx_av, vy_av, 
	vx_sq_sum/n - vx_av^2, 
	vy_sq_sum/n - vy_av^2
    vxsum=vysum=0
    n=0
    vx_sq_sum=0
    vy_sq_sum=0
}