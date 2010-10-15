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

using namespace std;

//int Material::number_of_materials = 0;
//double Material::supportlength = 0.0; //smoothinglenth
//double Material::delta = 0.0; //smoothinglenth
//----------------------------------------------------------------------------------------
//					constructors
//----------------------------------------------------------------------------------------
Material::Material(Initiation &ini, const int index):
  material_no(index)
{
  material_name = std::string(ini.interp->getat("material_name", index));
  material_type = ini.interp->getat("material_type",  index);
  cv = ini.interp->getat("material_cv",  index);
  gamma = ini.interp->getat("material_gamma",  index);
  // b0 = ini.interp->getat("material_b0",  index);
  rho0 = ini.interp->getat("material_rho0",  index);
  sound_speed = ini.interp->getat("material_sound_speed",  index);
  eta = ini.interp->getat("material_eta",  index);
  if (ini.simu_mode == 2) {
    zeta = ini.interp->getat("material_zeta",  index);
  }
  /// thermal condactivity simulation
  if (ini.simu_mode == 3) {
    k_thermal = ini.interp->getat("material_kthermal",  index);
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
	LOG(INFO)<<"The heat ratio is "<<gamma<<"\n";
	LOG(INFO)<<"The reference density is "<<rho0<<" kg/m^3 \n";
}

//----------------------------------------------------------------------------------------
//			obtain parameter b0
//----------------------------------------------------------------------------------------
void Material::Set_b0(const double)
{
  b0 = sound_speed * sound_speed * pow(rho0, 1.0 - gamma) / gamma;
}
//----------------------------------------------------------------------------------------
//					get pressure
//----------------------------------------------------------------------------------------
double Material::get_p(const double rho) const
{
  return b0*pow(rho, gamma);
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

double Material::get_Cs() const  {
  return sound_speed;
}

//----------------------------------------------------------------------------------------
// get sound speed
//----------------------------------------------------------------------------------------
double Material::get_Cs(const double p, const double rho) const {
  assert(rho>0.0);
  assert(p>0.0);
  return sqrt(gamma*p/rho);
}
