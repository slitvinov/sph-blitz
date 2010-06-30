set SIMULATION_MODE 1

# possible values are 
# QuinticSpline, BetaSpline, CubicSpline
set KERNEL_TYPE QuinticSpline

set INITIAL_CONDITION	0

set DIAGNOSE			2

set CELLS(0) 8
set CELLS(1) 8

set CELL_SIZE 5.0e-3

set SUPPORT_LENGTH 5.0e-3

set CELL_RATIO  3

set U0(0) 0.0
set U0(1) 0.0

set rho0 1.0
set p0 0.5
set T0 1.0

set G_FORCE(0) 0.0
set G_FORCE(1) 0.0

set NUMBER_OF_MATERIALS 3
set Start_time 0.0
set End_time 1e-1
set D_time 1e-3

# boundary conditions
# type and velocity
set xBl 1
set UxBl(0) 0.0
set UxBl(1) 0.6

set xBr 1
set UxBr(0) 0.0
set UxBr(1) -0.6

set yBd 0
set UyBd(0) 0.0
set UyBd(1) 0.0

set yBu 0
set UyBu(0) 0.0
set UyBu(1) 0.0

set NUMBER_OF_MATERIALS 2
set material_name(0) Wall
set material_type(0) 1
set material_cv(0) 1.0e3
set material_eta(0) 2.0e-2
set material_gamma(0) 7.0
set material_b0(0) 1.0e2
set material_rho0(0) 1.0e3
set material_a0(0) 1.0e2

set material_name(1) Air
set material_type(1) 1
set material_cv(1) 1.0e3
set material_eta(1) 2.0e-2
set material_gamma(1) 7.0
set material_b0(1) 1.0e2
set material_rho0(1) 1.0e3
set material_a0(1) 1.0e2
