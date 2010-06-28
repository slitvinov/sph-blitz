///\file material.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//-------------------------------------------------------------------
//				Define material properties
//				material.cpp
//----------------------------------------------------------------
// ***** system includes *****
#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cmath>

// ***** localincludes *****
#include "glbfunc.h"
#include "material.h"
#include "initiation.h"

using namespace std;

//int Material::number_of_materials = 0;
//double Material::supportlength = 0.0; //smoothinglenth
//double Material::delta = 0.0; //smoothinglenth
//----------------------------------------------------------------------------------------
//					constructors
//----------------------------------------------------------------------------------------
Material::Material(Initiation &ini, const int number):
  number(number)
{
  material_name = std::string(ini.interp.eval("[return $material_name]"));
  material_type = ini.interp.eval("[return $material_type]");
  cv = ini.interp.eval("[return $material_cv]");
  gamma = ini.interp.eval("[return $material_gamma]");
  b0 = ini.interp.eval("[return $material_b0]");
  rho0 = ini.interp.eval("[return $material_rho0]");
  a0 = ini.interp.eval("[return $material_a0]");
}

//----------------------------------------------------------------------------------------
//			output the property parameters to the screen
//----------------------------------------------------------------------------------------
void Material::show_properties()
{
	//kinetic viscosity
	nu = eta/rho0;
	
	cout<<"Material: "<<material_name<<"\n";		
	cout<<"The heat capacity is  "<<cv<<" J/kg/K\n";
	cout<<"The viscosity is "<<eta<<" Pa.s \n";
	cout<<"The heat ratio is "<<gamma<<"\n";
	cout<<"The reference pressure b0 is "<<b0<<" Pa\n";
	cout<<"The reference density is "<<rho0<<" kg/m^3 \n";
}
//----------------------------------------------------------------------------------------
//			obtain parameter b0
//			after nondimensionlization finished
//----------------------------------------------------------------------------------------
void Material::Set_b0(const double sound)
{
	//compressiblity
	b0 = a0*sound/gamma;
}
//----------------------------------------------------------------------------------------
//					get pressure
//----------------------------------------------------------------------------------------
double Material::get_p(const double rho) const
{
	return b0*pow(rho/rho0,gamma);
}

double Material::get_p(const double rho, const double e) const
{
  return (gamma-1)*rho*e;
}

//----------------------------------------------------------------------------------------
//					get rho from pressure
//----------------------------------------------------------------------------------------
double Material::get_rho(const double p) const
{
	return rho0*pow(p/b0, 1.0/gamma);
}
double Material::get_rho(const double p, const double e) const
{
  return p/((gamma-1)*e);
}


//----------------------------------------------------------------------------------------
//				get temperaturey
//----------------------------------------------------------------------------------------
double Material::get_T(const double e) const
{
  return e/cv;
}

double Material::get_T(const double p, const double rho) const
{
  return p/((gamma-1)*rho*cv);
}



//----------------------------------------------------------------------------------------
//				get internal energy
//----------------------------------------------------------------------------------------
double Material::get_e(const double T) const
{
	return cv*T;
}
//----------------------------------------------------------------------------------------
//					get sound speed
//----------------------------------------------------------------------------------------
double Material::get_Cs(const double p, const double rho)
{
	return sqrt(gamma*p/rho);
}
