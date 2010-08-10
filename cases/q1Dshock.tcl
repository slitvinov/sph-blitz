# 1D shock configuration file
set SIMULATION_MODE 2

# possible values are 
# QuinticSpline, BetaSpline, CubicSpline
set KERNEL_TYPE CubicSpline

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
set CELLS(0) 260
set CELLS(1) 1

# size of one cell
set CELL_SIZE 0.015

# support length of the kernel
set SUPPORT_LENGTH 0.015

# number of particles in one cell size
# not used in q1D shock 
set CELL_RATIO 1

# initial particles velocity
set U0(0) 0.0
set U0(1) 0.0

# initial propeties of the particles (noz used either)
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
#
# type and velocity
# 0: wall
# 1: periodic
# 2: freeslip
# 3: symmetry
#


# left hand boundary
set xBl 0
set UxBl(0) 0.0
set UxBl(1) 0.0

# right hand boundary
set xBr 0
set UxBr(0) 0.0
set UxBr(1) 0.0

# lower boundary
set yBd 1
set UyBd(0) 0.0
set UyBd(1) 0.0

# upper boundary
set yBu 1
set UyBu(0) 0.0
set UyBu(1) 0.0

# time step
set Start_time 0.0		
set End_time 0.2	
set D_time 0.0025

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
set material_cv(1) 1.0e3
set material_eta(1) 0.0
set material_gamma(1) 1.4
set material_b0(1) 0.0
set material_rho0(1) 0.0
set material_a0(1) 0.0
