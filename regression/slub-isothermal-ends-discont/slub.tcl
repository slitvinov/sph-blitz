# 1D shock configuration file
# 1: liquids
# 2: gas dynamics
# 3: thermal conductivity
set SIMULATION_MODE 3

# possible values are 
# QuinticSpline, BSpline, CubicSpline
set KERNEL_TYPE BSpline
set OutputType Plain
set output_file_format_factor 1e6

# disable boundary conditions:
# 1: boundary conditions disabled
# 0: boundary conditions enabled
set DISABLE_BOUNDARY 0

#possible density treatments
#1: summation density (density obtained by smoothing)
#2: continuity density (density is integrated)
set DENSITY_MODE 1

set INITIAL_CONDITION	0

#possible density treatments
#1: summation density (density obtained by smoothing)
#2: continuity density (density is integrated)
set DENSITY_MODE 1

#possible integration schemes
#1: leap frog
#2: predictor corrector
set INTEGRATION_SCHEME 2

# output directory
if  [catch {set OUTDIR output$res_level}] {
    set res_level 10
    set OUTDIR output$res_level
} 
set output_file_format_factor 1e4

# number of cell
set ncell [expr {int(2.0/3.0*$res_level)}]
set CELLS(0) $ncell
set CELLS(1) 3

# sizer of the domain
set L 1.0
set SUPPORT_LENGTH [expr {$L / $ncell}]
set CELL_SIZE $SUPPORT_LENGTH

# the number of particles in one support length
set CELL_RATIO  3

# initial velocity
set U0(0) 0.0
set U0(1) 0.0

set rho0 1e3
set p0 1.0
set T0 1.0

set G_FORCE(0) 0.0
set G_FORCE(1) 0.0

set Start_time 0.0
set End_time 135
# time between output
set D_time 135

# boundary conditions
set wall 0 
set periodic 1
set freeslip 2
set symmetry 3

# type and velocity
set xBl $wall
set UxBl(0) 0.0
set UxBl(1) 0.0
set xTl 0.0

set xBr $wall
set UxBr(0) 0.0
set UxBr(1) 0.0
set xTr 1.0

set yBd $periodic
set UyBd(0) 0.0
set UyBd(1) 0.0

set yBu $periodic
set UyBu(0) 0.0
set UyBu(1) 0.0

set kl 10.0
set kr 1.0
set NUMBER_OF_MATERIALS 3
set material_name(1) Bulk1
set material_type(1) 1
set material_cv(1) 1.0
set material_kthermal(1) $kr
set material_eta(1) 1.0e-3
set material_gamma(1) 7.0
set material_b0(1) 1.0e2
set material_rho0(1) 1.0e3
set material_sound_speed(1) 1.0e2

set material_name(0) Wall
set material_type(0) $material_type(1)
set material_cv(0) $material_cv(1)
set material_kthermal(0) 1.0
set material_eta(0) $material_eta(1)
set material_gamma(0) $material_gamma(1)
set material_b0(0) $material_b0(1)
set material_rho0(0) $material_rho0(1)
set material_sound_speed(0) $material_sound_speed(1)

set material_name(2) Bulk2
set material_type(2) $material_type(1)
set material_cv(2) $material_cv(1)
set material_kthermal(2) $kl
set material_eta(2) $material_eta(1)
set material_gamma(2) $material_gamma(1)
set material_b0(2) $material_b0(1)
set material_rho0(2) $material_rho0(1)
set material_sound_speed(2) $material_sound_speed(1)

proc getTemperature { } {
    # generate taylor-green initial conditions
    if {$x > [expr {0.5*$L}]} {
	set T $xTr
    } else {
	set T $xTl
    }
}

proc getmatNo { } {
    # generate taylor-green initial conditions
    if {$x > [expr {0.5*$L}]} {
	set no 1
    } else {
	set no 2
    }
}
