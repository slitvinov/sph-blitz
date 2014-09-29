#ifndef INITIATION_H
#define INITIATION_H

#ifdef _OPENMP
#include <omp.h>
#endif

//for auto_ptr
#include <memory>
#include <cstdlib>

//#include "wiener.h"
#include "vec2d.h"
//#include "dllist.h"
//#include "hydrodynamics.h"
//#include "quinticspline.h"
//#include "particle.h"

class Particle;
class ParticleManager;
class QuinticSpline;
class Hydrodynamics;
class AbsPolymerCreator;
class DataCollector;
class Boundary;

/// \brief Initialize the progam.
/// Class to read from configuration file and store physical parameters, initial condition and
/// parameters of the simulation. Public methods and fields of this class are used to
/// initialize other classes. <BR>
/// Other class to read data from *.cfg file: <BR>
/// Material, Hydrodynamics, Boundary

class Initiation {	
  friend class Material;
  friend class Hydrodynamics;
  ///the static instances member to hold 
  ///the one and only one instance of Initiation class
  static Initiation* _instance;
  ///reference length \f$(\SI{}{\micro m})$\f
  double _length;
  ///reference velocity (m/s)
  double _v;
  ///reference density \f$(kg/m^3)\f$
  double _rho; 	
  ///reference temperature (K)
  double _T; 
  ///polymer creator
  AbsPolymerCreator* pcreator_;
  ///data collector
  DataCollector* datacollector_;
  ///boundary object
  Boundary* boundary_;

  ///polymer configuration file name
  const string poly_conf;
  
protected:
  /// \brief Initiation constructor
  ///
  /// This function creates a Initiation object according to the input file data.
  /// Reads the reference values:
  /// - length 
  /// - velocity
  /// - density
  /// - temperature 
  /// \param project_name the name of the project 	
  Initiation(const string& project_name, 
	     const string& poly_conf);  
public:	
  static Initiation* Instance(const string& project_name, 
			      const string& poly_conf="polymer.cfg");
  static Initiation* Instance();
  ///add polymer creator
  void addPolymerCreator(AbsPolymerCreator* newpcreator);
  ///add data collector
  void addDataCollector(DataCollector* newdatacollector);
  ///time step coefficient (default value: 1.0)
  /// used in hydrodynamics.GetTimestep()
  double timestep_co;
  ///the project name
  char Project_name[25];
  ///number of materials
  ///the materials number 0 denots the wall
  //therefore at least 2 materials should be included
  int number_of_materials;
  ///the global inputfile name: a *.cfg file 
  char inputfile[25];
  /// \brief initial condition marker: 
  /// initial condition marker
  ///0 initialize from the .cfg file; 
  ///1 read from the .rst file particle by particle with dimensionless data
  int initial_condition;
  ///diagnose information maker: 1 output diagnose information
	int diagnose;
  ///artificial viscosity
  double art_vis;
  ///smoothinglength
  double smoothinglength;
  ///the compuational domain size
  Vec2d box_size;
  ///cell size
  double cell_size;
  ///the inital particle distance
  double delta;
  ///the ration between smoothing length and inital particle distance
  int hdelta;
  ///cells matrix for real particles
  int x_cells;
  ///cells matrix for real particles
  int y_cells;
  ///g force on particles
  Vec2d g_force;
  ///\name Time steps parameters
  //@{
  ///start time
  double Start_time;
  ///end time
  double End_time;
  ///the output time interval
  double D_time;
  //@}
  ///inital flow velocity
  Vec2d U0;
  ///initial particle density
  double rho0;
  ///initial particle pressure
  double p0;
  ///initial particle temperature
  double T0;
  ///maximum clock time 
  double MAX_TIME;

  //boundary condition indicator
  //left, right, upper and bottom
  //0: wall boundary condition
  //1: periodic boundary condition
  //2: free slip wall boundary condition
  //3: symmetry boundary condition 
  int  xBl, xBr, yBd, yBu;
  Vec2d UxBl, UxBr, UyBd, UyBu; //boundary velocity


  ///output stream type
  ///maybe TEXT or CDF
  string outputstream;
  
  ///output directory
  string output_dir;
  
  ///space dimenshions (1D, 2D 3D)
  int spacedim_;
  
  ///MLS parameters
  /// \see MLS
  int MLS_MAX;
  
  ///returns the number of dimensions 
  int getDim() const;
  
  ///nondimensionalization  of the parameters and the initial conditions
  void non_dimensionalize();
  ///show information on the screen
	void show_information() const;
  ///predict the particle volume and mass
  void VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, 
		  QuinticSpline &weight_function) const;
  
  /// \name Dimensional physical parameters and constants
  //@{
  ///pressure \f$(\SI{}{Pa})\f$
  double dms_p(double p_non) const;

  ///position \f$(\SI{}{m})\f$
  Vec2d dms_R(Vec2d& R) const;
  ///temperature \f$(\SI{}{K})\f$
  double dms_T(double T_non) const;
  ///density \f$(\SI{}{kg/m^3})\f$
  double dms_rho(double rho_non) const;
  ///mass \f$(\SI{}{kg})\f$
  double dms_mass(double mass_non) const;
  ///time \f$(\SI{}{s})\f$
  double dms_time(double time_non) const;
  ///length \f$(\SI{}{m})\f$
  double dms_length(double length_non) const;	
  double dms_volume(double v) const;
  Vec2d dms_box_size(Vec2d box_size_non) const;
  ///velocity \f$(\SI{}{m/s})\f$
  double dms_velocity(double velocity_non) const;
  ///vector velocity \f$(\SI{}{m/s})\f$ 
  Vec2d dms_velocity(Vec2d velocity_non) const;
  ///energy \f$(\SI{}{kg.m^2/s^2})\f$
  double dms_energy(double energy_non) const;
  ///scalar acceleration \f$(\SI{}{m/s^2})\f$
  double dms_acceleration(double acceleration_non) const;
  ///vector acceleration \f$(\SI{}{m/s^2})\f$
  Vec2d dms_acceleration(Vec2d acceleration_non) const;
  ///viscosity \f$(\SI{}{kg/m.s})\f$
  double dms_viscosity(double mu_non) const;
  ///surface tension coefficient \f$(\SI{}{kg/s^2})\f$
  double dms_surface(double sigma_non) const;
  //@}
  /// \name Non-dimesionlize physical parameters and constants
  /// Functions return physical parameters and constants
  /// in dimensionless form. Those finctions do not change the members of 
  /// Initiation class.
  //@{
  double non_dms_p(double p) const;
  double non_dms_T(double T) const;
  double non_dms_rho(double rho) const;
  double non_dms_mass(double mass) const;
  double non_dms_time(double time) const;
  double non_dms_length(double length) const;
  Vec2d non_dms_box_size(Vec2d box_size) const;
  double non_dms_velocity(double velocity) const;
  double non_dms_kinetic_viscosity(double nu) const;
  Vec2d non_dms_velocity(Vec2d velocity) const;
  double non_dms_acceleration(double acceleration) const;
  Vec2d non_dms_acceleration(Vec2d acceleration) const;
  double non_dms_viscosity(double mu) const; 
  double non_dms_heat_ratio(double cv) const;
  double non_dms_heat_conduction(double kappa) const;
  double non_dms_Boltzmann(double k_bltz) const;
  double non_dms_surface(double sigma) const;
  double non_dms_elasticity(double k) const;
  //@}
  ///returns pointer to polymer creator
  AbsPolymerCreator* getPolymerCreator() const;
  ///returns polymer to data collector
  DataCollector* getDataCollector() const;

  ///return polymer to Boundary object
  Boundary* getBoundary() const;
  
  ///add Boundary pointer
  void setBoundary(Boundary*);
  
};
#endif
