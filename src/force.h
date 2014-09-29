#ifndef FORCE_H
#define FORCE_H

#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
#include "vec2d.h"
//#include "wiener.h"
//#include "dllist.h"
//
class Initiation;

/// force definition class
class Force {

	friend class Hydrodynamics;
	
	///total number of materials
	static int number_of_materials;
	///smoothinglenth
	static double smoothinglength;

	///interactive force parameters
	double epsilon;

	///heat conduction slip length
	double heat_slip; 

public:
	///surface tension parameters, its dimension is rho*u^2*L 
	double sigma; 
	///shear and bulk slip length
	double shear_slip, bulk_slip; 

	///constructor
	Force();
	Force(const Initiation* const ini);

	///non-dimensionalize
	void non_dimensionalize(const Initiation* const ini);
	
};
#endif
