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
	double k;///<thermal conductivity

	double gamma; ///<ratio of specific heats (adiabatic index)
	double eta_0; ///<parameter for Sutherland-law for variable viscosity
	double T_0_eta; ///<parameter for Sutherland-law for variable viscosity
	double S_eta; ///<parameter for Sutherland-law for variable viscosity
	double k_0; ///<parameter for Sutherland-law for variable condictivity
	double T_0_k; ///<parameter for Sutherland-law for variable condictivity
	double S_k; ///<parameter for Sutherland-law for variable  condictivity

	double nu; ///<kinetice viscosity
	double b0;///<reference pressure
	double rho0;///<reference density
	double a0; ///<reference <b>sound speed??? was not commented</b>
	int variableEtaAndK;///< local copy of variable eta/k variable from Initiation class

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
	double get_p(const double rho, const double e) const;//equation of state for gasdynamics
	///get rho from pressure
	double get_rho(const double p) const ;// equation of state for liquids

	///get rho from pressure
	double get_rho(const double p, const double e) const;//equation of state for gasdynamics
	///get interal energy
	double get_e(const double T) const;
	///get temperature 
	double get_T(const double e) const;//(function is defined nowhere)

	///get temperature 
	double get_T(const double p, const double rho) const;
	///get sound speed
	double get_Cs(const double p, const double rho);
	///get viscosity (returen either constant viscosity or eta(T), depending on teh selected settings
	double get_eta(const double T);
	///get conductivity (returen either constant viscosity or eta(T), depending on teh selected settings
	double get_k(const double T);

};

#endif //MATERIAL_H
