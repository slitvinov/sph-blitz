#! /usr/bin/awk -f

BEGIN {
    # gate position
    Lx = 15.0
    gate = Lx / 3.0 * 2.0
    rho_w = 1e3
    rho_a = 1.0
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
    x = $2
    if ($1 != "Wall") {
	if (x<gate) {
	    $1 = "Water"
	    $6 = rho_w
	} else {
	    $1 = "Air"
	    $6 = rho_a
	}
    }
    print

}

