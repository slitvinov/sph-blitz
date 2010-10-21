///\file material.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//-------------------------------------------------------------------
//				Define material properties
//				material.cpp
//----------------------------------------------------------------
#include <glog/logging.h>

// ***** localincludes *****
#include "material.h"
#include "initiation.h"
#include <boost/format.hpp>

using namespace std;

//int Material::number_of_materials = 0;
//double Material::supportlength = 0.0; //smoothinglenth
//double Material::delta = 0.0; //smoothinglenth
//----------------------------------------------------------------------------------------
//					constructors
//----------------------------------------------------------------------------------------
Material::Material(Initiation &ini, const int number)
{
  LOG(INFO) << "Run constructor of Material class";
  // to have array in the return string for tcl
  // example [return A(1)]
  const std::string index = boost::str(boost::format("(%i)]") % number);
  // read material properties from .tcl input file
  material_name = std::string(ini.interp.eval("[return $material_name" + index));
  material_type = ini.interp.eval("[return $material_type"  + index);
  cv = ini.interp.eval("[return $material_cv"  + index);
  gamma = ini.interp.eval("[return $material_gamma"  + index);
  b0 = ini.interp.eval("[return $material_b0"  + index);
  rho0 = ini.interp.eval("[return $material_rho0"  + index);
  a0 = ini.interp.eval("[return $material_a0"  + index);
  //local copy of variable eta and k flag
  variableEtaAndK=ini.variableEtaAndK;
  if (ini.simu_mode == 2) {
    if(variableEtaAndK==0) {
      //read eta, zeta, k from .tcl file (are considered constant during simulation)
      eta = ini.interp.eval("[return $material_eta"  + index);
      zeta = ini.interp.eval("[return $material_zeta"  + index);
      k = ini.interp.eval("[return $material_k"  + index);
    }
    else {
      // read reference values for sutherland law
      // for viscosity
      eta_0=ini.interp.eval("[return $material_eta_0"  + index);
      T_0_eta=ini.interp.eval("[return $material_T_0_eta"  + index);
      S_eta=ini.interp.eval("[return $material_S_eta"  + index);
      // for thermal conductivity
      k_0=ini.interp.eval("[return $material_k_0"  + index);
      T_0_k=ini.interp.eval("[return $material_T_0_k"  + index);
      S_k=ini.interp.eval("[return $material_S_k"  + index);
    }
  }
  LOG(INFO) << "Material object is created";
}

//----------------------------------------------------------------------------------------
//			output the property parameters to the screen
//----------------------------------------------------------------------------------------
void Material::show_properties()
{
	//kinetic viscosity
	nu = eta/rho0;
	LOG(INFO)<<"Material: "<<material_name<<"\n";		
	LOG(INFO)<<"The heat capacity is  "<<cv<<" J/kg/K\n";
	LOG(INFO)<<"The (shear) viscosity is "<<eta<<" Pa.s \n";
	LOG(INFO)<<"The bulk viscosity is "<<zeta<<" Pa.s \n";
	LOG(INFO)<<"The thermal conductivity is "<<k<<" W/K/m \n";
	LOG(INFO)<<"The heat ratio is "<<gamma<<"\n";
	LOG(INFO)<<"The reference pressure b0 is "<<b0<<" Pa\n";
	LOG(INFO)<<"The reference density is "<<rho0<<" kg/m^3 \n";
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
  assert(rho>0.0);
  assert(p>=0.0);
  return sqrt(gamma*p/rho);
}
//----------------------------------------------------------------------------------------
//	       	get viscosity (either constant or f(T, depending on user settings)))
//---------------------------------------------------------------------------------------
double Material::get_eta(const double T)
{
  assert(T>=0.0);
  // set constant viscosity (as specified in .tcl file) if this option is choosen
  if(variableEtaAndK==0)    
    return eta;
  //if specified in .tcl file: calculate variable viscosity and conductivity
  else 
    //Sutherland law for eta, (1-36) from White1974 
    eta=eta_0*pow(T/T_0_eta,1.5)*(T_0_eta+S_eta)/(T+S_eta);  
}

//----------------------------------------------------------------------------------------
//	       	get conductivity (either constant or f(T, depending on user settings)))
//---------------------------------------------------------------------------------------
double Material::get_k(const double T)
{
  assert(T>=0.0);
  // set constant conductivity (as specified in .tcl file) if this option is choosen
  if(variableEtaAndK==0) 
    return k;
  //if specifide in .tcl file: calculate variable conductivity
  else 
    //Sutherland law for k, (1-44b) from White1974 
    return k_0*pow(T/T_0_k,1.5)*(T_0_k+S_k)/(T+S_k);
  ///TODO{think about cv(T) and bulk viscosity zeta (T) (for completeness)}
}

