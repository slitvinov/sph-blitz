#ifndef INITIATION_H
#define INITIATION_H
/// \file initiation.h 
/// \brief initializes the simulation data

#include "cpptcl/cpptcl.h"
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
  const std::string Project_Name;
  //the ivs file name
  const std::string Ivs_File_Name;

  /// output directory name (default is outdata)
  std::string outdir;

  ///kernel type
  /// possible values are
  /// QuinticSpline, BetaSpline, CubicSpline, CubicSpline1D
  std::string kernel_type;

  ///\brief number of materials
  ///
  ///- the no. zero material is always the wall
  ///- therefore at least 2 materials should be included
  int number_of_materials;

  ///tcl interpreter to read configuration data
  boost::shared_ptr<Tcl::interpreter> interp; 

  /// a pointer to context class 
  /// used to define "special" rulles of partilce motion (ex. solid partilces)
  spParticleContext context;

  ///\brief integration scheme selection
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

  /// \brief initial position perturbation
  /// 
  /// add a rundom number to the initial postions (in the fraction of delta)
  double initial_perturb; 

  ///\brief disable boundary condition marker:
  ///- 0 boundary conditions enabled
  ///- 1 boundary conditions disabled
  bool disable_boundary;

  ///simulation mode (1: liquids, 2: gas dynamics)
  int simu_mode;

  ///\brief physical viscosity marker:
  ///
  ///- 1: including physical viscosity
  ///- 0: no physical viscosity
  int physical_viscosity_marker; 

  ///\brief artificial viscosity marker:
  ///- 2. art. visc. globally turned on
  ///- 1: incl. art. visc. for compression only (as needed for shock-tube case)
  ///- 0: no artificial viscosity
  int artificial_viscosity_marker; 

  ///\brief density mode marker
  ///
  ///- 1: summation density (density obtained by smoothing),
  ///- 2: continuity density (density is integrated)
  int density_mode;
  ///supportlength
  double supportlength;
  /// parameter n for harmonic kernel
  double harmonic_n;
  ///the computational domain size
  Vec2d box_size;
  ///cell size
  double cell_size;
  ///the initial particle distance
  double delta;
  ///the ration between smoothing length and initial particle distance
  int hdelta;
  ///cells matrix for real particles
  int x_cells, y_cells;
  ///g force on particles
  TMatrix g_force;
  /// is TRUE we use compiled body force 
  /// from cBodyForce variable in the config file
  bool useCompiledBodyForce;
  /// compiled body force function
  TBodyF bodyF;
  /// a handle of external function
  void* externalFunHandle;

  ///\brief marker to choose output format
  /// 
  /// 0: used for post-processing of shocktube cases and wave propagation; format: x, y, rho, p, Ux, e, ID, m
  /// 1: used for visualization with SPLASH-program; format x, y, Ux, Uy, rho, e, p, h=supportlength/2, m, V, ID
  int splash_optimized_output;

  //timing control
  double Start_time;///<Simulation start time
  double End_time;///<Simulation end time
  double D_time;///<time interval for output (every D_time: output)
  ///\brief marker for automatic time control
  /// 0: autom. time conrtol switched off
  /// 1: autom time control activated!
  double autom_dt_control;
  double manually_choosen_dt;///<Time-step (specified in .tcl-configuration file) which is applied if autom. dt-control is turned off

  /// output factor, used to generate the name of output file
  /// default value is 1e6
  double output_file_format_factor;


  Vec2d U0;///<initial flow speed (if initial condition is defined here)w
  //double rho0;///<initial particle density(if initial condition is defined here)
  //double p0;///<initial pressure(if initial condition is defined here)
  double T0;///<initial temperature(if initial condition is defined here)

  ///artificial viscosity
  double alpha_artVis;
  double beta_artVis;
  double epsilon_artVis;

  
 ///constructor 
  ///\param *project_name: a pointer to the project name array (the project name is defined as a main-function argument and therefore given as an additional command line element when running the program)
///\param *ivs_file_name: a pointer to the project ivs file name array (the ivs file name is defined as the second main-function argument)or to NULL in case no ivs file is needed (liquids simulation)
  explicit Initiation(const std::string& project_name, const std::string& ivs_file_name);
  ///show information on screen
  void show_information() const;
  ///predict the particle volume and mass
  void VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, 
		  spKernel weight_function);
  ~Initiation();

 private:
  /// helpper function to define body force
  void DefineBodyForce();
};


/// convert char* to std::string
const char *CharPtrToStdString(const char *str);

#endif
