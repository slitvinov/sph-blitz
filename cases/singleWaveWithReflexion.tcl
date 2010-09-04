# 1D shock configuration file
# 1: liquids
# 2: gas dynamics
set SIMULATION_MODE 2

# possible values are 
# QuinticSpline, BetaSpline, CubicSpline, CubicSpline1D
set KERNEL_TYPE CubicSpline1D

#possible integration schemes
#1: leap frog
#2: predictor corrector
set INTEGRATION_SCHEME 1

#possible density treatments
#1: summation density (density obtained by smoothing)
#2: continuity density (density is integrated)
set DENSITY_MODE 1

# initial conditions flag 
# 0: use initial 
# 1: use restart file
set INITIAL_CONDITION 0

# number of cells in X and Y directions
# 130 cells in x direction are good for supportlength =0.03 (for m=cte=0.001875)
# xx cells in x direction are good for supportlength =xx (for dx=cte=0.05)
set CELLS(0) 64
set CELLS(1) 1

# size of one cell
# ->make sure that cell size >= support length
set CELL_SIZE 0.03125

# support length of the kernel 
# -> make sure that support length > particle spacing
# (0.03 is not bad for m=cte=0.001875)
# (xx is not bad for dx=cte=0.005)
set SUPPORT_LENGTH 0.0252

# number of particles in one cell size
# not used in 1D shock 
set CELL_RATIO 1

# initial particles velocity (not used)
set U0(0) 0.0
set U0(1) 0.0

# initial propeties of the particles(not used)
set rho0 0.0
set p0 0.5
set T0 1.0

# gravity force
set G_FORCE(0) 0.0
set G_FORCE(1) 0.0

# parameters of artificial viscosity
set alpha_artVis 1.0
set beta_artVis 2.0
set epsilon_artVis 0.1

# boundary conditions

# disable boundary conditions:
# 1: boundary conditions disabled
# 0: boundary conditions enabled
set DISABLE_BOUNDARY 0
# type and velocity
set xBl 0
set UxBl(0) 0.0
set UxBl(1) 0.0

set xBr 0
set UxBr(0) 0.0
set UxBr(1) 0.0

set yBd 1
set UyBd(0) 0.0
set UyBd(1) 0.0

set yBu 1
set UyBu(0) 0.0
set UyBu(1) 0.0

# time step
set Start_time 0.0		
set End_time 3.38062
set D_time 0.0422411163

set NUMBER_OF_MATERIALS 2
set material_name(0) Wall
set material_type(0) 1
set material_cv(0) 0.0
set material_eta(0) 0.0
set material_gamma(0) 0.0
set material_b0(0) 0.0
set material_rho0(0) 0.0
set material_a0(0) 0.0

set material_name(1) Air
set material_type(1) 1
set material_cv(1) 717.645
set material_eta(1) 0.0
set material_gamma(1) 1.4
set material_b0(1) 0.0
set material_rho0(1) 0.0
set material_a0(1) 0.0
