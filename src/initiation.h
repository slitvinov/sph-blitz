#ifndef INITIATION_H
#define INITIATION_H
/// \file initiation.h 
/// \brief initializes the simulation data

#include "cpptcl.h"
#include "vec2d.h"
#include <boost/utility.hpp>
#include "glbtype.h"
class Hydrodynamics;
class ParticleManager;
class Kernel;

///\brief Initiates the simulation
/// It must be a one copy of Initiation object
/// and copying is prevented
class Initiation : boost::noncopyable {
public:
	
  ///the project name
  std::string Project_name;
  //the ivs file name
  std::string Ivs_file_name;
  
  /// type of solid obstacle in calculation domain 
  /// (in addition to boundaries at the domain edges)
  /// possible values are
  /// NoObstacles, Cavity, Porosities
  std::string SolidObstacles_type;

  /// kernel type
  /// possible values are
  /// , BetaSpline, CubicSpline, CubicSpline1D
  std::string kernel_type;

  ///\brief number of materials
  ///
  ///- the no. zero material is always the wall
  ///- therefore at least 2 materials should be included
  int number_of_materials;

  ///tcl interpreter to read configuration data
  Tcl::interpreter interp; 

  ///\brief integation scheme selection
  ///
  ///possible integration schemes
  ///- 1: leap frog
  ///- 2: predictor corrector
  int integration_scheme;

  /// \brief initial condition marker:
  ///
  ///- 0 initialize from the .tcl file (+.ivs file for gas dynamics); 
  ///- 1 read from the .rst file particle by particle with non-dimensional data
  int initial_condition;

  ///\brief disable boundary condition marker:
  ///
  ///- 0 boundary conditions enabled
  ///- 1 boundary conditions disabled
  int disable_boundary;

  ///\brief isothermal boundaries (for "free-slip" and "wall" only)
  /// 
  /// 0 NOT isothermal
  /// 1 isothermal
  int isothermal_boundary;

  ///\brief marker for pure heat conduction simulation setup
  ///
  ///- 1: pure heat conduction ON (i.e. no change of quantities other than internak energy)
  ///- 0: pure heat conduction OFF (normal flow simulation taking int account all change rates)
  int pure_conduction; 

  ///\brief virtual velocity assignment type for ghost particles of solid Obstacles
  ///
  /// virtual velocity is used to calculate viscous forces and therefore
  /// influences quality of no--slip condition
  /// 0: solid Obstacles have zero real velocity AND ZERO virtual velocity
  /// 1: solid Obstacles have zero real vleocity AND virtual velocity
  ///    according to Morris1999
  int solObs_virt_veloc_type;

  /// limit for distance solObs surfacs <-> real particle for 
  /// virtual velocity calculation according to Morris1999
  double d_realPart_solObs_min;

  ///simulation mode (1: liquids, 2: gas dynamics)
  int simu_mode;

  ///\brief flag to turn on/off smoothing of initial density profile
  ///
  ///(only useful for initially discontinuous density profile like for shock-tube)
  /// 0: NO smoothing of initial density profile
  /// 1: smoothing of initial density profile
  int smoothDensityProfile;

  ///\brief physical viscosity marker:
  ///
  ///- 1: including physical viscosity
  ///- 0: no physical viscosity
  int physical_viscosity_marker; 

  ///\brief marker for temperature dependend viscosity and thermal conduction
  ///
  /// 1: variable viscosity/conductivity taken into account (Sutherland law)
  /// 0: constant viscosity/conductivity (takes values specified in .tcl file)
  int variableEtaAndK;

  ///\brief artificial viscosity marker:
  ///- 2: art. visc. globally turned on
  ///- 1: incl. art. visc. for compression only (as needed for shock-tube case)
  ///- 0: no artificial viscosity
  int artificial_viscosity_marker; 

  ///\brief external mass initialization marker
  ///- 0: mass initialization within simulation program (by smoothing)
  ///- 1: mass initialized externally (via initialization file)
  int external_mass_initialization;

  ///\brief density mode marker
  ///
  ///- 1: summation density (density obtained by smoothing),
  ///- 2: continuity density (density is integrated)
  int density_mode;
  ///supportlength
  double supportlength;
  /// parameter n for harmonic kerenel
  double harmonic_n;
  /// the compuational domain size
  Vec2d box_size;
  ///cell size
  double cell_size;
  /// the inital particle distance
  double delta;
  /// the ration between smoothing length and inital particle distance
  int hdelta;
  /// cells matrix for real particles
  int x_cells, y_cells;
  /// g force on particles
  Vec2d g_force;
  ///\brief temporal delay for beginning of g-force action
  double g_force_delay;

  ///\brief marker to choose output format
  /// 
  /// 0: used for post-processing of shocktube cases and wave propagation; format: x, y, rho, p, Ux, e, ID, m
  /// 1: used for visualization with SPLASH-program; format x, y, Ux, Uy, rho, e, p, h=supportlength/2, m, V, ID
  int splash_optimized_output;

  ///\brief  marker for 12-digit timestamp in file name (standard: 8 digit)
  ///
  /// this is necessary as for some applications (like pure heat conduction)
  /// the simulation time is so huge that the standard time stamp is
  /// not sufficient
  /// 0: standard timestamp (8 digits)
  /// 1: extra large timestamp (12 digits)
  int xxl_timestamp_marker;


  ///\brief  marker to switch timestamp  unit of outputfiles
  ///
  /// becomes necessary for simulations with very small dt,
  /// for example due to high viscosity values 
  /// 0: standard (timestamp unit [ms])
  /// 1: high resolution (timestamp unit [1e-10s])
  int high_res_timestamp_marker;

  //timing control
  double Start_time;///<Simulation start time
  double End_time;///<Simulation end time
  double D_time;///<time interval for output (every D_time: output)
  ///\brief marker for automatic time control
  /// 0: autom. time conrtol switched off
  /// 1: autom time control activated!
  double autom_dt_control;
  double manually_choosen_dt;///<Timestep (specified in .tcl-configuration file) which is applied if autom. dt-control is turned off


  Vec2d U0;///<inital flow speed (if initial condition is defined here)w
  double rho0;///<initial particle density(if initial condition is defined here)
  double p0;///<initial pressure(if initial condition is defined here)
  double T0;///<initial temperature(if initial condition is defined here)

  ///artificial viscosity
  double alpha_artVis;
  double beta_artVis;
  double epsilon_artVis;

  
 ///constructor 
  ///\param *project_name: a pointer to the project name array (the project name is defined as a main-function argument and therefore given as an additional command line element when running the progam)
///\param *ivs_file_name: a pointer to the project ivs file name array (the ivs file name is defined as the second main-function argument)or to NULL in case no ivs file is needed (liquids simulation)
  explicit Initiation(const std::string& project_name, const std::string& ivs_file_name);
  ///show information on screen
  void show_information() const;
  ///predict the particle volume and mass
  void VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, 
		  spKernel weight_function, spSolidObstacles obstacles);
};
#endif
