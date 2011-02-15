# 1D shock configuration file
# 1: liquids
# 2: gas dynamics
# 4: S1
set SIMULATION_MODE 1
set s1_niter 40
#set movePartilces 0

# possible values are 
# QuinticSpline, BSpline, CubicSpline
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
set OutputType Plain
set initial_perturb 0.25

# number of cell
set xncell 10
set yncell $xncell
set CELLS(0) $xncell
set CELLS(1) $yncell

# sizer of the domain
set L 1.0
set SUPPORT_LENGTH [expr {$L / $yncell}]
set CELL_SIZE $SUPPORT_LENGTH

# the number of particles in one support length
set CELL_RATIO 3

# initial velocity
set U0(0) 0.0
set U0(1) 0.0

set g -1.0

set T0 0.0
# output directory
# if isim is not given set OUTDIR to output_co0
# to set isim variable use
# SPH_TCL="set eta_block 42" ./sph ../cases/falling_block_sym

set Start_time 0.0
set Hook_time 1.0
set End_time 50.0
# time between output
set D_time 1e-2

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

set eta_media 0.1
set rho_media 1.0
set rho_block 1.033333
set k_rho 0.0

set NUMBER_OF_MATERIALS 2
set material_name(0) Wall
set material_type(0) 1
set material_cv(0) 1.0e3
set material_eta(0) $eta_media
set material_gamma(0) 1.0
set material_b0(0) 1.0e2
set material_rho0(0) $rho_media
set material_sound_speed(0) 14.0
set material_rho_ref(0) [expr {$k_rho*$rho_media}]


set material_name(1) Media
set material_type(1) $material_type(0)
set material_cv(1) $material_cv(0)
set material_eta(1) $eta_media
set material_gamma(1) $material_gamma(0)
set material_b0(1) $material_b0(0)
set material_rho0(1) $material_rho0(0)
set material_rho_ref(1) $material_rho_ref(0)
# a sound speed
set material_sound_speed(1) $material_sound_speed(0)

# return material number based on the position of the particle
set xlength [expr {$CELLS(0)* $CELL_SIZE} ]
set ylength [expr {$CELLS(1)* $CELL_SIZE} ]

set blockFractionX 0.2
set blockFractionY 0.2
set sq_block [expr {0.5 * $blockFractionX * $blockFractionY}]
set sq_media [expr {1.0 - $sq_block} ]

set g_all 0.0
set g_block [expr {$g_all / $rho_block / $sq_block}]
#set g_media [expr {$g_all / $rho_media / $sq_media}]
set g_media 0.0

if  [catch {set OUTDIR outdata-eta${eta_media}b}] {
    set OUTDIR outdata0
    set eta_block 1.0
} 
set output_file_format_factor 1e2


set G_FORCE(0,0) 0.0
set G_FORCE(0,1) 0.0

set G_FORCE(1,0) 0.0
set G_FORCE(1,1) $g_media

set G_FORCE(2,0) 0.0
set G_FORCE(2,1) -$g_block

# # x and y provided by the main program 
# set blockX0 [expr { (0.5 - $blockFractionX/2.0) * $xlength}]
# set blockX1 [expr { (0.5 + $blockFractionX/2.0) * $xlength}]
# set blockY0 [expr {(0.8 - $blockFractionY/2.0) * $ylength}]
# set blockY1 [expr {(0.8 + $blockFractionY/2.0) * $ylength}]

# # set number of material variable  --- "no" 
# proc getmatNo { } {
#     set inX [expr ($x > $blockX0) && ($x < $blockX1)]
#     set inY [expr ($y > $blockY0) && ($y < $blockY1)]
#     if {$inX && $inY} { 
# 	# block 
# 	set no 2
#     } else {
# 	# media
# 	set no 1
#     } 
# }

# # set number of material variable  --- "no" 
# proc getSolid { } {
#     set inX [expr ($x > $blockX0) && ($x < $blockX1)]
#     set inY [expr ($y > $blockY0) && ($y < $blockY1)]
#     if {$inX && $inY} { 
# 	# block 
# 	set issolid 1
#     } else {
# 	# media
# 	set issolid 0
#     } 
# }

set v0 0.1
proc filter_hook { } {
    # generate taylor-green initial conditions
    set pi 3.1415926
    set k0 [expr {2.0 * $pi/$L}]
    set vx  [expr {-$v0*cos($k0*$x)*sin($k0*$y)} ] 
    set vy  [expr {$v0*sin($k0*$x)*cos($k0*$y)} ]
    set issolid 0
}
