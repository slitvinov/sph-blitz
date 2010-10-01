# 1D shock configuration file
# 1: liquids
# 2: gas dynamics
set SIMULATION_MODE 1

# possible values are 
# QuinticSpline, BetaSpline, CubicSpline
set KERNEL_TYPE QuinticSpline

# disable boundary conditions:
# 1: boundary conditions disabled
# 0: boundary conditions enabled
set DISABLE_BOUNDARY 0

#possible density treatments
#1: summation density (density obtained by smoothing)
#2: continuity density (density is integrated)
set DENSITY_MODE 1

set INITIAL_CONDITION	0

# number of cell
set ncell 8
set CELLS(0) $ncell
set CELLS(1) $ncell

# sizer of the domain
set L 1.0
set SUPPORT_LENGTH [expr {$L / $ncell}]
set CELL_SIZE $SUPPORT_LENGTH

# the number of particles in one support length
set CELL_RATIO  3

# initial velocity
set U0(0) 0.0
set U0(1) 0.0

set g -1.0

set T0 0.0

set Start_time 0.0
set End_time 0.108507
# time between output
set D_time 0.108507

# boundary conditions
set wall 0 
set periodic 1
set freeslip 2
set symmetry 3

# type and velocity
set xBl $periodic
set UxBl(0) 0.0
set UxBl(1) 0.0

set xBr $periodic
set UxBr(0) 0.0
set UxBr(1) 0.0

set yBd $periodic
set UyBd(0) 0.0
set UyBd(1) 0.0

set yBu $periodic
set UyBu(0) 0.0
set UyBu(1) 0.0

set rho_media 1.0
set rho_block 1.033333
set eta_block 1.0

set NUMBER_OF_MATERIALS 3
set material_name(0) Wall
set material_type(0) 1
set material_cv(0) 1.0e3
set material_eta(0) 1.0
set material_gamma(0) 1.0
set material_b0(0) 1.0e2
set material_rho0(0) $rho_media
set material_sound_speed(0) 1.0

set material_name(1) Media
set material_type(1) $material_type(0)
set material_cv(1) $material_cv(0)
set material_eta(1) $material_eta(0)
set material_gamma(1) $material_gamma(0)
set material_b0(1) $material_b0(0)
set material_rho0(1) $material_rho0(0)
set material_sound_speed(1) $material_sound_speed(0)

set material_name(2) Block
set material_type(2) $material_type(0)
set material_cv(2) $material_cv(0)
set material_eta(2) $eta_block
set material_gamma(2) $material_gamma(0)
set material_b0(2) $material_b0(0)
set material_rho0(2) $rho_block
set material_sound_speed(2) $material_sound_speed(0)

# return material number based on the position of the particle
set xlength [expr {$CELLS(0)* $CELL_SIZE} ]
set ylength [expr {$CELLS(1)* $CELL_SIZE} ]

set blockFractionX 0.4
set blockFractionY 0.4
set sq_block [expr {$blockFractionX * $blockFractionY}]
set sq_media [expr {1.0 - $sq_block} ]

set g_all 1.0
set g_block [expr {$g_all / $rho_block / $sq_block}]
set g_media [expr {$g_all / $rho_media / $sq_media}]

set G_FORCE(0,0) 0.0
set G_FORCE(0,1) 0.0

set G_FORCE(1,0) 0.0
set G_FORCE(1,1) $g_media

set G_FORCE(2,0) 0.0
set G_FORCE(2,1) -$g_block


# set number of material variable  --- "no" 
proc getmatNo { } {
    # x and y provided by the main program 
    set blockX0 [expr {(0.5 - $blockFractionX/2.0) * $xlength}]
    set blockX1 [expr {(0.5 + $blockFractionX/2.0) * $xlength}]
    set blockY0 [expr {(0.6 - $blockFractionY/2.0) * $ylength}]
    set blockY1 [expr {(0.6 + $blockFractionY/2.0) * $ylength}]
    set inX [expr ($x > $blockX0) && ($x < $blockX1)]
    set inY [expr ($y > $blockY0) && ($y < $blockY1)]
    if {$inX && $inY} { 
	# block 
	set no 2
    } else {
	# media
	set no 1
    } 
}