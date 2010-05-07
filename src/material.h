/// \file material.h 
/// \brief Material 

#ifndef MATERIAL_H
#define MATERIAL_H

class Initiation;

/// Material 
class Material {

	///total number of materials
	static int number_of_materials;
	static double smoothinglength, delta; ///smoothinglenth

public:
	
	///material name string
	char material_name[25];
	int number; ///the material NO.

	///material type
	///0: solid; 1: liquid; 2: gas
	int material_type;

	double cv, eta, zeta, kappa, gamma; ///heat capacity, viscosity, heat conduction rate, heat ratio
	double nu; ///kinetice viscosity
	double b0, rho0, a0; ///reference pressure, reference density

	///constructor
	Material();
	Material(Initiation &ini);
	Material(char *material_name, Initiation &ini);
	
	///non-dimensionalize
	void non_dimensionalize(Initiation &ini);
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
