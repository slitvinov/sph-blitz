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
  std::string Project_name;
  //the ivs file name
  std::string Ivs_file_name;

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
  Tcl::interpreter interp; 

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

  ///simulation mode (1: liquids, 2: gas dynamics)
  int simu_mode;

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
  Vec2d g_force;

  //timing control
  double Start_time;///<Simulation start time
  double End_time;///<Simulation end time
  double D_time;///<time interval for output (every D_time: output)

  Vec2d U0;///<initial flow speed (if initial condition is defined here)w
  double rho0;///<initial particle density(if initial condition is defined here)
  double p0;///<initial pressure(if initial condition is defined here)
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
};


/// convert char* to std::string
const char *CharPtrToStdString(const char *str);

#endif
