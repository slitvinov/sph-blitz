# Install

Run

	./local-install.sh

# Initial conditon file format

	<start time>
	<number of particles>
	...
	<material name> <X> <Y> <Vx> <Vy> <density> <pressure> <temperature>
	...
	<empty line>

# Input file format

To use restart file

	INITIAL_CONDITION	1

The level of statistics output

	DIAGNOSE			2

number of cells in x and y direction

	CELLS

size of one cell

	 CELL_SIZE			5.0e-3

support length

	 SMOOTHING_LENGTH	5.0e-3

the number of particle in one direction in a cell

	 CELL_RATIO			3

the basic of dimensions

	 DIMENSION
	 TIMING  <inital time> <the last time> <output timestep>

gravity force vector

	 G_FORCE

type code of coundary
1: periodic
0: wall coundary

	BOUNDARY <use or not wall file, must be 0> <type codes of boundry X0, X1, Y0, Y1>
	<velocity of the wall>

	NUMBER_OF_MATERIALS <numb_mat>

	MATERIALS
	<material_name><material_type>	<cv>	<eta>	<zeta>	<kappa>	<gamma>	<b0>	<rho0>	<a0>
	(one line for each material)

	 FORCES
	 <mat#k>	<mat#m>		<epsilon>	<sigma>	<shear_slip>	<bulk_slip>	<heat_slip>
	 (numb_mat*numb_mat lines, one for each material pair)

# Simulations

	cd src

Couette flow simulation

	./sph ../cases/couette

# Postprocessing

	cd outdata/
	../../scripts/dat2punto.sh > punto.dat

# Visualization

	punto -D 2 -V -s 50 punto.dat
	punto -D 2 -c 4 -B 0:0:0.04:0.04 -G -0.2:0.2 punto.dat

in gnuplot shell

	plot n=1, 'punto.dat' u 2:3 every :::n::n
	plot n=10, A=250.0, 'punto.dat' u 2:3 every :::n::n+5, A*x*(L-x)

# Others

To remove output directory

	rm -rf outdata/
