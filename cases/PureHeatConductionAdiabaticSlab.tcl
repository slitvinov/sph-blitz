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
set SMOOTH_DENSITY_PROFILE 0

# initial conditions flag 
# 0: use initial 
# 1: use restart file
set INITIAL_CONDITION 0

# external mass initialization marker
# 0: mass initialization within simulation program (by smoothing)
# 1: mass initialized externally (via initialization file)
set EXTERNAL_MASS_INITIALIZATION 0

# number of cells in X and Y directions
set CELLS(0) 20
set CELLS(1) 10

# size of one cell (must NOT be inferior to supportlength!)
set CELL_SIZE 0.05

# support length of the kernel
set SUPPORT_LENGTH 0.05

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

# pure Heat Condution
# all particles immobilized, no change in any parameters
# except for internal energy
# 1: pure conduction is ON
# 0: pure conduction is OFF (i.e. all quantities may change)
set PURE_CONDUCTION 1;


# artificial viscosity marker: (not used for pure heat conduction)
# 2. art. visc. globally turned on
# 1: incl. art. visc. for compression only (as needed for shock-tube case)
# 0: no artificial viscosity
set ARTIFICIAL_VISCOSITY_MARKER 0;

# parameters for artificial viscosity (not used for pure heat conduction)
set alpha_artVis 1.0
set beta_artVis 2.0
set epsilon_artVis 0.1

# physical viscosity flag (not used for pure heat conduction)
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
# applies only to WALL and FREE_SLIP boundary conditions!!
# isothermal or not (=adiabatic)
# 1: isothermal (temperature as specified at corresponding boundary)
# 0: NOT isothermal
set ISOTHERMAL_BOUNDARY 0


# disable boundary conditions:
# 1: boundary conditions disabled
# 0: boundary conditions enabled
set DISABLE_BOUNDARY 0

# left hand boundary
set xBl 3
set UxBl(0) 0.0
set UxBl(1) 0.0

# right hand boundary
set xBr 3
set UxBr(0) 0.0
set UxBr(1) 0.0

# lower boundary
set yBd 1
set UyBd(0) 0.0
set UyBd(1) 0.0

# upper boundary
set yBu 1
set UyBu(0) 0.0
set UyBu(1) 0.0

# time  control 
set Start_time 0.0		
set End_time 1.25
set D_time 1.2499999999999
#set D_time 1.25

#marker for automatic time control
# 0: autom. time conrtol switched off: specified dt used (see below) 
# 1: autom time control activated!
set AUTOMATIC_DT_CONTROL_MARKER 0

#timestep taken into account if autom. time-step-control switched off
#ATTENTION: the timestep has to be thoroughly choosen (respecting the stability criteria)
#(RECOMMENDATION: run the desired configuration with autom.dt-control turned on first to get an idea of the max. admissible dt, then pick a dt (including a certain margin, to be safe)
set manually_choosen_dt 0.005

set NUMBER_OF_MATERIALS 2
set material_name(0) Wall
set material_type(0) 1
set material_cv(0) 0.0
set material_eta(0) 0.0
set material_zeta(0) 0.0
set material_k(0) 0.0
set material_gamma(0) 0.0
set material_b0(0) 0.0
set material_rho0(0) 0.0
set material_a0(0) 0.0

#bulk viscosity neglected (zeta=0)
# viscosity eta is DYNAMIC VISCOSITY [Pa s]
set material_name(1) Air
set material_type(1) 1
set material_cv(1) 1
set material_eta(1) 0.0
set material_zeta(1) 0.0
set material_k(1) 1
set material_gamma(1) 2
set material_b0(1) 0.0
set material_rho0(1) 0.0
set material_a0(1) 0.0
