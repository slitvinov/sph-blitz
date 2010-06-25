#ifndef MATERIAL_H
#define MATERIAL_H
/// \file material.h 
/// \brief Material 

#include <string>

/// Material 
class Material {

	///total number of materials
	static int number_of_materials;
	static double supportlength;///<smoothinglenth
	static double delta;

public:
	///material name string
	std::string material_name;
	int number; ///<the material NO.

	///\brief material type
	///
	///- 0: solid;
	///-  1: liquid;
	///-  2: gas
	int material_type;

	double cv;///<heat capacity
	double eta;///<viscosity
	double zeta;///<heat conduction rate
	double gamma; ///<???

	double nu; ///<kinetice viscosity
	double b0;///<reference pressure
	double rho0;///<reference density
	double a0; ///<reference <b>sound speed??? was not commented</b>

	///constructor
	Material();
	///constructor
	Material(Initiation &ini);
	
	///non-dimensionalize
	void non_dimensionalize(Initiation &ini);
	///show properties
	void show_properties();

	///obtain parameter b0
	void Set_b0(const double sound);
	
	//equation of states

	///get pressure
	double get_p(const double rho) const;// equation of state for liquids
	double get_p(const double rho, const double e) const;//equation of state for gasdynamics
	///get rho from pressure
	double get_rho(const double p) const ;// equation of state for liquids
	double get_rho(const double p, const double e) const;//equation of state for gasdynamics
	///get interal energy
	double get_e(const double T) const;
	///get temperature 
	double get_T(const double e) const;//(function is defined nowhere)
	double get_T(const double p, const double rho) const;
	///get sound speed
	double get_Cs(const double p, const double rho);

};

#endif //MATERIAL_H
