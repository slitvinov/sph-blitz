#ifndef MATERIAL_H
#define MATERIAL_H

#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
//#include "vec2d.h"
//#include "wiener.h"
//#include "dllist.h"
//#include "initiation.h"
//#include "particle.h"

class Initiation;
class Particle;

/// \bref Material
/// Contains the properties of material
class Material {
	///total number of materials
	static int number_of_materials;
	 ///smoothinglenth
	static double smoothinglength, delta;

public:
	
	///material name string
	char material_name[25];
	///the material NO.
	int number; 

	///material type
	///0: solid; 1: liquid; 2: gas
	int material_type;

	///heat capacity
	double cv;
	double eta, zeta, kappa, gamma; //viscosity, heat conduction rate, heat ratio
	///kinetice viscosity
	double nu; 	
	double b0, rho0, a0; //reference pressure, reference density

	///constructor
	Material();
	Material(const Initiation* const ini);
	Material(char *material_name, const Initiation* const ini);
	
	///non-dimensionalize
	void non_dimensionalize(const Initiation* const ini);
	///show properties
	void show_properties();

	///obtain parameter b0
	void Get_b0(double sound);
	
	///equation of states
	double get_p(double rho);
	double get_rho(double p);
	double get_e(double T);
	double get_T(double e);
	double get_Cs(double p, double rho);

};
#endif
