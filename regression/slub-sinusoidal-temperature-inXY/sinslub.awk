#!/usr/bin/awk -f 

# returns an analytical solution for temperature distribution 
BEGIN {
  pi = 3.1415926
  alpha=k/(rho*cv)
  printf("alpha = %e\n", alpha) > "/dev/stderr"
}

NF{
  x=$1
  y=$2
  T = sin(pi*y/l)*sin(pi*x/l) * exp(-2.0*(pi/l)**2 * alpha * t)
  print x, y, T
}