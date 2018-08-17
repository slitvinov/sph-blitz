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

	Force(Initiation &ini);

	///non-dimensionalize
	void non_dimensionalize(Initiation &ini);
	
};

#endif //FORCE_H
