# get torque from punto file
# x0, y0: center of rotation
BEGIN{
    if (length(x0)==0) {
	printf("(angmom.awk) x0 must be given\n") > "/dev/stderr"
	exit 2
    }
    if (length(m)==0) {
	printf("(angmom.awk) m must be given\n") > "/dev/stderr"
	exit 2
    }
    if (length(y0)==0) {
	printf("(angmom.awk) x0 must be given\n") > "/dev/stderr"
	exit 2
    }
}

NF&&$7>0{
    have_data=1
    x=$1
    y=$2
    
    dx=x-x0
    dy=y-y0

    Fx=$6
    Fy=$7
    
    t+= dx*Fx + dy*Fy
}

function print_output() {
    if (have_data) {
	print t*m
	t=0
	have_data=0
    } 
}
    
!NF{
    print_output()
}

END{
    print_output()
}