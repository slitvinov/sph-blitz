set INITIAL_CONDITION	10

set DIAGNOSE			2

set MLS_MAX				100

set CELLS(1) 8
set CELLS(2) 8

set CELL_SIZE 5.0e-3

set SMOOTHING_LENGTH 5.0e-3

set CELL_RATIO  3

set U0(1) 0.0
set U0(2) 0.0

set rho0 1.0
set p0 0.5
set T0 1.0

set G_FORCE(1) 0.0
set G_FORCE(2) 0.0

set ARTIFICIAL_VISCOSITY 0.0

set _lenth 1.0
set _v 1.0
set _rho 1.0
set _T 1.0

set NUMBER_OF_MATERIALS 3
set Start_time 0.0
set End_time 1.0
set D_time 1e-3


# DIMENSION			2.0e-2	0.9		1.0		1.0

# TIMING				0.0		0.1	1.0e-3

# G_FORCE				0.0		0.0		

# ARTIFICIAL_VISCOSITY		0.0e-3	

# BOUNDARY			0	1	0.0		0.0
# 						1	0.0		0.0
# 						0	-0.6	0.0
# 						0	0.6		0.0

# NUMBER_OF_MATERIALS 3

# MATERIALS
# Wall	1		1.0e3	2.0e-2	1.0e-2	1.0e2	7.0		1.0e1	1.0		1.0e2
# Air		1		1.0e3	2.0e-2	1.0e-2	1.0e2	7.0		1.0e1	1.0		1.0e2
# Water	1		1.0e3	1.0e-2	5.0e-3	1.0e2	7.0		1.0e1	1.0		1.0e2

# FORCES
# 0		0		0.0		0.0		0.0		0.0		0.0		
# 0		1		0.0		0.0		0.0		0.0		0.0			
# 0		2		0.0		0.0		0.0		0.0		0.0			
# 1		0		0.0		0.0		0.0		0.0		0.0				
# 1		1		0.0		0.0		0.0		0.0		0.0				
# 1		2		0.0		0.01	0.0		0.0		0.0				
# 2		0		0.0		0.0		0.0		0.0		0.0		
# 2		1		0.0		0.01	0.0		0.0		0.0			
# 2		2		0.0		0.0		0.0		0.0		0.0			

