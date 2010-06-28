set SIMULATION_MODE 2
set INITIAL_CONDITION 0

set CELLS(0) 40
set CELLS(1) 1

set CELL_SIZE 0.05
set SUPPORT_LENGTH 0.03

set CELL_RATIO 1

set U0(0) 0.0
set U0(1) 0.0

set rho0 0.0
set p0 0.5
set T0 1.0

set G_FORCE(0) 0.0
set G_FORCE(1) 0.0

# ARTIFICIAL_VISCOSITY		0	

set is_wall_file 0
set xBl 0
set UxBl(0) 0.0
set UxBl(1) 0.0

set xBr 0
set UxBr(0) 0.0
set UxBr(1) 0.0

set yBd 0
set UyBd(0) 0.0
set UyBd(1) 0.0

set yBu 0
set UyBu(0) 0.0
set UyBu(1) 0.0

set Start_time 0.0		
set End_time 0.25	
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
set material_gamma(1) 0.0
set material_b0(1) 1.4
set material_rho0(1) 0.0
set material_a0(1) 0.0