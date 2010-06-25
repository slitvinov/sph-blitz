#ifndef INITIATION_H
#define INITIATION_H
/// \file initiation.h 
/// \brief Initiates the simulation


///\brief Initiates the simulation
#include "vec2d.h"

class Initiation {
	
  friend class Material;
  friend class Hydrodynamics;

  //reference length, speed, and density for non-dimensionalization
  double _length;///<reference length for non dimensional value 
  double _v;///<reference speed for non dimensional value
  double _rho;///<reference density for non dimensional value
  double _T;///<reference temperature for non dimensional value

public:
	
  ///the project name
  char Project_name[25];

  ///\brief number of materials
  ///
  ///- the no. zero material is always the wall
  ///- therefore at least 2 materials should be included
  int number_of_materials;
  ///the global inputfile name: a *.cfg file
  char inputfile[25];

  /// \brief initial condition marker:
  ///
  ///- 0 initialize from the .cfg file; 
  ///- 1 read from the .rst file particle by particle with non-dimensional data
  int initial_condition;
  ///diagnose information maker: 1 output diagnose information
  int diagnose;
  ///artificial viscosity
  double art_vis;
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

  ///constructor
  ///\param *project_name: a pointer to the project name array (the project name is defined as a main-function argument and therefore given as an additional command line element when running the progam) 
  explicit Initiation(const char *project_name);
  ///non-dimensionalize initial condition and parameters
  void non_dimensionalize();
  ///show information on screen
  void show_information() const;
  ///predict the particle volume and mass
  void VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, Kernel &weight_function);

  //non-dimesionlize
  double non_dms_p(const double p) const ;///<a non dimensionalize method
  double non_dms_T(const double T) const ;///<a non dimensionalize method
  double non_dms_rho(const double rho) const ;///<a non dimensionalize method
  double non_dms_mass(const double mass) const ;///<a non dimensionalize method
  double non_dms_time(const double time) const ;///<a non dimensionalize method
  double non_dms_length(const double length) const;///<a non dimensionalize method
  Vec2d non_dms_box_size(const Vec2d box_size) const;///<a non dimensionalize method
  double non_dms_velocity(const double velocity) const;///<a non dimensionalize method
  double non_dms_kinetic_viscosity(const double nu) const;///<a non dimensionalize method
  Vec2d non_dms_velocity(const Vec2d velocity) const;///<a non dimensionalize method
  double non_dms_acceleration(const double acceleration) const ;///<a non dimensionalize method
  Vec2d non_dms_acceleration(const Vec2d acceleration) const ;///<a non dimensionalize method
  double non_dms_viscosity(const double mu) const ;///<a non dimensionalize method
  double non_dms_heat_ratio(const double cv) const ;///<a non dimensionalize method
  double non_dms_heat_conduction(const double kappa) const ;///<a non dimensionalize method
  double non_dms_Boltzmann(const double k_bltz) const ;///<a non dimensionalize method

  //re-dimesionlize
  double dms_p(const double p_non) const ;///<a re-dimensionalize method
  double dms_T(const double T_non) const ;///<a re-dimensionalize method
  double dms_rho(const double rho_non) const ;///<a re-dimensionalize method
  double dms_mass(const double mass_non) const ;///<a re-dimensionalize method
  double dms_time(const double time_non) const ;///<a re-dimensionalize method
  double dms_length(const double length_non) const ;///<a re-dimensionalize method
  Vec2d dms_box_size(const Vec2d box_size_non) const ;///<a re-dimensionalize method
  double dms_velocity(const double velocity_non) const ;///<a re-dimensionalize method
  Vec2d dms_velocity(const Vec2d velocity_non) const ;///<a re-dimensionalize method
  double dms_energy(const double energy_non) const ;///<a re-dimensionalize method
  double dms_acceleration(const double acceleration_non) const ;///<a re-dimensionalize method
  Vec2d dms_acceleration(const Vec2d acceleration_non) const ;///<a re-dimensionalize method
};
#endif
