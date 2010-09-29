#ifndef MATERIAL_H
#define MATERIAL_H
/// \file material.h 
/// \brief Material 

#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>

class Material;
class Initiation;

/// Material 
class Material {

public:
	///material name string
	std::string material_name;

	///\brief material type
	///
	///- 0: solid;
	///-  1: liquid;
	///-  2: gas
	int material_type;

	double cv;///<heat capacity
	double eta;///<(shear) viscosity
  	double zeta;///<bulk viscosity
	double gamma; ///<ratio of specific heats (adiabatic index)

	double nu; ///<kinetic viscosity
	double b0;///<reference pressure
	double rho0;///<reference density
	double a0; ///<reference <b>sound speed??? was not commented</b>

	///constructor
	/// imaterial is a number of material in input file
	Material(Initiation &ini, const int number);

	///show properties
	void show_properties();

	///obtain parameter b0
	void Set_b0(const double sound);
	
	//equation of states

	///get pressure
	double get_p(const double rho) const;// equation of state for liquids

  	///get pressure
	double get_p(const double rho, const double e) const;//equation of state for gas dynamics
	///get rho from pressure
	double get_rho(const double p) const ;// equation of state for liquids

	///get rho from pressure
	double get_rho(const double p, const double e) const;//equation of state for gas dynamics
	///get internal energy
	double get_e(const double T) const;
	///get temperature 
	double get_T(const double e) const;//(function is defined nowhere)

	///get temperature 
	double get_T(const double p, const double rho) const;
	///get sound speed
	double get_Cs(const double p, const double rho);

};
#endif //MATERIAL_H
