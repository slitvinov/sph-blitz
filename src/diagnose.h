#ifndef DIAGNOSE_H
#define DIAGNOSE_H

#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
#include "vec2d.h"
//#include "wiener.h"
#include "dllist.h"
//#include "hydrodynamics.h"
//#include "mls.h"
//#include "particlemanager.h"
class Hydrodynamics;
class Initiation;
class ParticleManager;
class QuinticSpline;
class Interaction;
class MLS;


//-----------------------------------------------------------------------
//					Output the diagnosal results
//-----------------------------------------------------------------------

/// diagnose of output results
class Diagnose {
	
	///the inital particle distance
	double delta;
	///cells matrix for real particles
	int x_cells, y_cells;
	///the ration between smoothing length and inital particle distance
	int hdelta; 

	///the project name
	char Project_name[25];
	int number_of_materials;

	///velocity, density, distributions
	double vx_dstrb[2][101], vy_dstrb[2][101], rho_dstrb[2][101];
	///list for states of a given particle
	Llist<double> vx_list, vy_list, rho_list; 

	///average profile mesh size
	int gridx, gridy;
	double ***U;
	int n_average; //the times of average

	///biuld distribution
	void BuildDistribution(Llist<double> &list, double dstrb[2][101]);

	///total mass, global average kinetic energy, material weight center position and velocity
	double ttl_m, *mtl_m, glb_ave_Ek;
	Vec2d *wght_cntr, *wght_v;

public:

	///constructor
	Diagnose(const Initiation* const ini, Hydrodynamics &hydro);

	///save the states of a particle
	void SaveStates(Hydrodynamics &hydro);
	///output distribution up to the time
	void OutputProfile(double Time, const Initiation* const ini);

	///calculate the average values
	void Average(ParticleManager &particles, MLS &mls, 
		     QuinticSpline &weight_function, const Initiation* const ini);
	///output the average values
	void OutputAverage(double Time, const Initiation* const ini);

	///track the globle average kinetic energy, weight center position and velocity
	void KineticInformation(double Time, const Initiation* const ini, Hydrodynamics &hydro);
};
#endif
