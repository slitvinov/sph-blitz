#ifndef INITIATION_H
#define INITIATION_H
/// \file initiation.h 
/// \brief Initiates the simulation

#include "cpptcl.h"
#include "vec2d.h"
#include <boost/utility.hpp>

class Hydrodynamics;
class ParticleManager;
class Kernel;

///\brief Initiates the simulation
/// It must be a one copy of Initiation object
/// and copy is prevented
class Initiation : boost::noncopyable {
public:
	
  ///the project name
  std::string Project_name;

  ///\brief number of materials
  ///
  ///- the no. zero material is always the wall
  ///- therefore at least 2 materials should be included
  int number_of_materials;

  ///tcl interpreter to read configuration data
  Tcl::interpreter interp; 

  /// \brief initial condition marker:
  ///
  ///- 0 initialize from the .cfg file; 
  ///- 1 read from the .rst file particle by particle with non-dimensional data
  int initial_condition;

  ///simulation mode (1:liquids, 2: gas dynamics)
  int simu_mode;
  ///supportlength
  double supportlength;
  ///the compuational domain size
  Vec2d box_size;
  ///cell size
  double cell_size;
  ///the inital particle distance
  double delta;
  ///the ration between smoothing length and inital particle distance
  int hdelta;
  ///cells matrix for real particles
  int x_cells, y_cells;
  ///g force on particles
  Vec2d g_force;

  //timing control
  double Start_time;///<Simulation start time
  double End_time;///<Simulation end time
  double D_time;///<time interval for output (every D_time: output)

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
  explicit Initiation(const std::string& project_name);
  ///show information on screen
  void show_information() const;
  ///predict the particle volume and mass
  void VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, 
		  const Kernel &weight_function);
};
#endif
