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
	static double smoothinglength;

	///interactive force parameters
	double epsilon;
public:

	double sigma; ///surface tension parameters, its dimension is rho*u^2*L
	double shear_slip, bulk_slip; ///shear and bulk slip length

	///constructor
	Force();
	explicit Force(Initiation &ini);
};

#endif //FORCE_H
