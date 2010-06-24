#ifndef FORCE_H
#define FORCE_H
/// \file force.h
/// \brief The class defining force on or between particles

/// The class defining force on or between particles
class Force {

	friend class Hydrodynamics;
	
	///total number of materials
	static int number_of_materials;
	///smoothinglenth
	static double supportlength;

	///interactive force parameters
	double epsilon;
	double heat_slip; ///heat conduction slip length 

public:

	double sigma; ///surface tension parameters, its dimension is rho*u^2*L
	double shear_slip, bulk_slip; ///shear and bulk slip length

	///constructor
	Force();
	Force(Initiation &ini);

	///non-dimensionalize
	void non_dimensionalize(Initiation &ini);
	
};

#endif //FORCE_H
