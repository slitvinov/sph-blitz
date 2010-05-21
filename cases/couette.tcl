set INITIAL_CONDITION	10

set DIAGNOSE			2

set MLS_MAX				100

set CELLS(1) 8
set CELLS(2) 8

set CELL_SIZE 5.0e-3

set SMOOTHING_LENGTH 5.0e-3

set CELL_RATIO  3

# INITIAL_STATES		0.0		0.0		1.0		0.5		1.0

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

