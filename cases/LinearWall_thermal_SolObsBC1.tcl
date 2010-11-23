# 1D shock configuration file
set SIMULATION_MODE 2

# possible values are 
# QuinticSpline, BetaSpline, CubicSpline
set KERNEL_TYPE CubicSpline

# possible integration schemes
# 1: leap frog
# 2: predictor corrector
set INTEGRATION_SCHEME 1

# possible density treatments
# 1: summation density (density obtained by smoothing)
# 2: continuity density (density is integrated)
set DENSITY_MODE 1

# brief flag to turn on/off smoothing of initial density profile
# (only useful for initially discontinuous density profile like for shock-tube
# and if continuity density approach is selected)
# 0: no smoothing of initial density profile
# 1: smoothing of initial density profile
set SMOOTH_DENSITY_PROFILE 0;

# initial conditions flag 
# 0: use initial 
# 1: use restart file
set INITIAL_CONDITION 0

# external mass initialization marker
# 0: mass initialization within simulation program (by smoothing)
# 1: mass initialized externally (via initialization file)
set EXTERNAL_MASS_INITIALIZATION 0

# number of cells in X and Y directions
set CELLS(0) 1
set CELLS(1) 15

# size of one cell (must NOT be inferior to supportlegth!)
set CELL_SIZE 0.1

# support length of the kernel
set SUPPORT_LENGTH 0.1

# number of particles in one cell size
#( not used as paricle positions initialized from external file) 
set CELL_RATIO 1

# initial particles velocity (not used)
set U0(0) 0.0
set U0(1) 0.0

# initial properties of the particles (not used either)
set rho0 0.0
set p0 0.5
set T0 1.0

# gravity force
set G_FORCE(0) 0.0
set G_FORCE(1) 0.0

# temporal delay of gravity force action
# (can be useful to give the initial particle distribution some timeto relax
# before the actual gravity force (which can simulate a pressure gradient) 
# starts to act. (time in sec)
set g_force_delay 0.0

# pure Heat Condution
# all particles immobilized, no change in any parameters
# except for internal energy
# 1: pure conduction is ON
# 0: pure conduction is OFF (i.e. all quantities may change)
set PURE_CONDUCTION 1

# artificial viscosity marker:
# 2. art. visc. globally turned on
# 1: incl. art. visc. for compression only (as needed for shock-tube case)
# 0: no artificial viscosity
set ARTIFICIAL_VISCOSITY_MARKER 0;

# parameters for artificial viscosity
set alpha_artVis 1.0
set beta_artVis 2.0
set epsilon_artVis 0.1

# physical viscosity flag
# 1: physical viscosity included
# 0: no physical viscosity
set PHYSICAL_VISCOSITY_MARKER 1

# flag for variable viscosity and thermal conductivity
# 0: simulation with constant values (specified below as material properties)
# 1: simulation with variable eta, k (according to Sutherland law 
#    (see White1974) with parameters material_eta_0, material_S_0,
#     material_T_0 to be specified both for eta and k in materials
#      section below 
set VARIABLE_ETA_AND_K 0

# marker to choose output format
# 0: used for post-processing of shocktube cases and wave propagation
#    format: x, y, rho, p, Ux, e, ID, m
# 1: used for visualization with SPLASH-program and all "real" 2D simulations
#    format x, y, Ux, Uy, rho, e, p, h=supportlength/2, m, V, ID
set SPLASH_OPTIMIZED_OUTPUT 1

# marker for 12-digit time stamp in file name(standard: 8 digit)
# this is necessary as for some applications (like pure heat conduction)
# the simulation time is so huge that the standard time stamp is not sufficient
# 0: standard timestamp (8 digits)
# 1: extra large timestamp (12 digits)
set XXL_TIMESTAMP_MARKER 1

# marker to switch timestamp unit
# (becomes necessary for simulations with very small dt,
# for example due to high viscosity values)
#
# 0: standard (timestamp unit [ms])
# 1: high resolution (timestamp unit [1e-10s])
set HIGH_RES_TIMESTAMP_MARKER 0

# boundary conditions
#
# type and velocity
# 0: wall
# 1: periodic
# 2: freeslip
# 3: symmetry
#

# for simulations including heat conduction or for pure heat conduction
# boundaries isothermal or not?
# applies only to WALL and FREE_SLIP boundary conditions at domain edges!!
# isothermal or not (=adiabatic)
# 1: isothermal (temperature as specified at corresponding boundary)
# 0: NOT isothermal (wall is symmetric concerning temperature->adiabatic)
set ISOTHERMAL_BOUNDARY 0

# disable boundary conditions:
# 1: boundary conditions disabled
# 0: boundary conditions enabled
set DISABLE_BOUNDARY 0

# flag to output (or not) boundary particles in the prtlxxx.dat file
# along with real particles
# 0: NO outout of boundary particles
# 1: output of boundary particles
set OUTPUT_BOUNDARY_PRTL 1

# left hand boundary
set xBl 1
set UxBl(0) 0.0
set UxBl(1) 0.0

# right hand boundary
set xBr 1
set UxBr(0) 0.0
set UxBr(1) 0.0

# lower boundary
set yBd 3
set UyBd(0) 0.0
set UyBd(1) 0.0

# upper boundary
set yBu 3
set UyBu(0) 0.0
set UyBu(1) 0.0

# type of solid obstacle in calculation domain 
# (in addition to boundaries at the domain edges)
# possible values are:
# NoObstacles, Cavity, Porosities, LinearWall
set SOLID_OBSTACLES LinearWall

# virtual velocity assignment type for ghost particles of solid Obstacles
# virtual velocity is used to calculate viscous forces and therefore
# influences quality of no--slip condition
# 0: solid Obstacles have zero real velocity AND ZERO virtual velocity
# 1: solid Obstacles have zero real vleocity AND virtual velocity
#    according to Morris1999
set SOLOBS_VIRT_VELOC_TYPE 0

# for virtual velocity calculation according to Morris1999:
# lower limit for distance real-particle<->solObs surface
# NOTE: this parameter does not mean that physically
# distances < d_realPart_solObs_min are not possible, it only
# delimits the value used for virt. velocity calculations
# for porisity calculation Morris1999 suggests a value of
# sqrt(3)/4*dx=0.433*dx
set d_realPart_solObs_min 0.010825

# thermal boundary condition type for solid obstacles
# for the moment only isothermal BC implemented for solObs
# 0: isothermal, ghost prtl left at const T as initialized from .ivs file
# 1: isothermal, realized with constant ghost prtl. temperature T_w
# 2: isothermal, realized with linear extrapolation around T_w
set solObs_thermal_BC_type 1

# wall temperature for isothermal solid Obstacles temperature
# boundary condition 
set T_w_solObs_isothermal 1

# flag to select whether ghost particles for solid obstacles shall
# be contained in putput files or not
# 0: NO output of ghost particles for solid obstacles
# 1: output of solid obstacle ghost particles in prtlXXX.dat
# in this case ghost particles are marked by an ID=-1 in the output file
# (NOTE: their actual ID within the program is still an individual
# positive number as they are generated with the same constructor
# as real particles. It is only for the output that their ID is 
# set to -1 for identification purposes)
set OUTPUT_SOLOBS_GHOST_PRTL  0

# time  control 
set Start_time 0.0		
set End_time 20.0	
set D_time 0.005

#marker for automatic time control
# 0: autom. time control switched off: specified dt used (see below) 
# 1: autom time control activated!
set AUTOMATIC_DT_CONTROL_MARKER 1

#timestep taken into account if autom. time-step-control switched off
#ATTENTION: the timestep has to be thoroughly choosen (respecting the stability criteria)
#(RECOMMENDATION: run the desired configuration with autom.dt-control turned on first to get an idea of the max. admissible dt, then pick a dt (including a certain margin, to be safe)
set manually_choosen_dt 0.0015

set NUMBER_OF_MATERIALS 2
set material_name(0) Wall
set material_type(0) 1
set material_cv(0) 0.0
set material_eta(0) 0.0
set material_zeta(0) 0.0
set material_k(0) 0
set material_gamma(0) 0.0
set material_b0(0) 0.0
set material_rho0(0) 0.0
set material_a0(0) 0.0

#bulk viscosity neglected (zeta=0)
# viscosity eta is DYNAMIC VISCOSITY [Pa s]
set material_name(1) Air
set material_type(1) 1
set material_cv(1) 1
set material_eta(1) 0
set material_zeta(1) 0.0
set material_k(1) 1
set material_gamma(1) 2.0
set material_b0(1) 0.0
set material_rho0(1) 0.0
set material_a0(1) 0.0
