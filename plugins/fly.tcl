source compile.tcl
set Lx 10.0
set g 3.0
set program  \
    "extern \"C\" void bodyforce(double x, double y, double& Fx, double& Fy) { 
          if (x>0.5*$Lx) {
             Fx = 0.0; Fy = $g;
          } else {
             Fx = 0.0; Fy = - $g;
          }
    }"
compile $program libforce.so