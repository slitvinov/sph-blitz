set SIMULATION_MODE 2
set INITIAL_CONDITION 0

set CELLS(1) 40
set CELLS(2) 1

set CELL_SIZE 0.05
set SUPPORT_LENGTH 0.03

set CELL_RATIO 1

set U0(1) 0.0
set U0(2) 0.0

set rho0 0.0
set p0 0.5
set T0 1.0

set G_FORCE(1) 0.0
set G_FORCE(2) 0.0

# ARTIFICIAL_VISCOSITY		0	

# BOUNDARY			0	0	0.0		0.0
# 						0	0.0		0.0
# 						0	0.0	0.0
# 						0	0.0		0.0

set NUMBER_OF_MATERIALS 2
set Start_time 0.0		
set End_time 0.25	
set D_time 0.0025

# MATERIALS
# Wall	1		0.0	0.0	0.0	0.0		0.0	0.0
# Air	1		1.0e3	0.0	0.0	1.4		0.0	0.0