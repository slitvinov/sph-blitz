#ifndef OUTPUT_H
#define OUTPUT_H

#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
#include "vec2d.h"
//#include "wiener.h"
#include "dllist.h"
//#include "initiation.h"
//#include "hydrodynamics.h"
//#include "boundary.h"
//#include "particlemanager.h"
//#include "mls.h"
//#include "quinticspline.h"
class Node;
class QuinticSpline;
class MLS;
class ParticleManager;
class Boundary;
class Initiation;
class Hydrodynamics;


//-----------------------------------------------------------------------
//					Output the computational results
//-----------------------------------------------------------------------

/// output computational results class
class Output {
	
	///the project name
	char Project_name[25];
	
	///the number of materials
	int number_of_materials;

	///the inital particle distance
	double delta;

	///cells matrix for real particles
	int x_cells, y_cells;

	///the ration between smoothing length and inital particle distance
	int hdelta; 

public:

  ///constructor
  Output(const Initiation* const ini);
  
  ///output particle positions respected different materials
  void OutputParticles(Hydrodynamics &hydro, Boundary &boundary, 
		       double Time, const Initiation* const ini);
  ///output interactions
  void OutputInteractions(const Hydrodynamics &hydro,
			  double Time) const;
  ///output material states on uniform grid
  void OutputStates(ParticleManager &particles, MLS &mls, QuinticSpline &weight_function, 
		    double Time, const Initiation* const ini);
  ///Output data for restart
  void OutRestart(Hydrodynamics &hydro, double Time, const Initiation* const ini);
  ///a movie for particle motion
  void CreatParticleMovie();
  void WriteParticleMovie(Hydrodynamics &hydro, double Time, const Initiation* const ini);
  ///avergaed values for Poiseuille and Couette flows
  void OutAverage(ParticleManager &particles, MLS &mls, QuinticSpline &weight_function, 
		  double Time, const Initiation* const ini);
  ///output polymer information
  void OutPolymer(Hydrodynamics &hydro, double Time) const;
};
#endif
