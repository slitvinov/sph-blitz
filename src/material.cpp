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
#include "glbcls.h"
#include "glbfunc.h"

using namespace std;

int Material::number_of_materials = 0;
double Material::smoothinglength = 0.0; //smoothinglenth
double Material::delta = 0.0; //smoothinglenth
//----------------------------------------------------------------------------------------
//					constructors
//----------------------------------------------------------------------------------------
Material::Material()
{

}
//----------------------------------------------------------------------------------------
//					constructors
//----------------------------------------------------------------------------------------
Material::Material(Initiation &ini)
{
	//total number of materials
	number_of_materials = ini.number_of_materials;
	smoothinglength = ini.smoothinglength;
	delta = ini.delta;
}
//----------------------------------------------------------------------------------------
//					constructors
//----------------------------------------------------------------------------------------
Material::Material(char *material_name, Initiation &ini)
{

	char Key_word[25];
	char inputfile[25];

	strcpy(inputfile, ini.inputfile);
	
	///-check if inputfile exist
	ifstream fin(inputfile, ios::in);
	if (!fin) {
		cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
		std::cout << __FILE__ << ':' << __LINE__ << std::endl;
		exit(1);
	}
	else cout<<"\nMaterial: read material propeties of "<<material_name<<" from "<< inputfile <<" \n"; 

	  //- /reading key words and configuration data
	while(!fin.eof()) {
		
		//read a string block
		fin>>Key_word;
		  ///-read material properties from .cfg file
		//comparing the key words for the material name
		if(!strcmp(Key_word, material_name)) fin>>cv>>eta>>zeta>>kappa>>gamma>>b0>>rho0>>a0;

	}
	fin.close();

	  ///- output the property parameters to the screen
	show_properties();

	  //- /non-dimensionalize
	non_dimensionalize(ini);
}
//----------------------------------------------------------------------------------------
//					non-dimensionalize
//----------------------------------------------------------------------------------------
void Material::non_dimensionalize(Initiation &ini)
{
	cv = ini.non_dms_heat_ratio(cv);
	eta = ini.non_dms_viscosity(eta);
	zeta = ini.non_dms_viscosity(zeta);
	nu = ini.non_dms_viscosity(nu);
	kappa = ini.non_dms_heat_conduction(kappa);
	b0 =ini.non_dms_p(b0);
	rho0 = ini.non_dms_rho(rho0);
}
//----------------------------------------------------------------------------------------
//			output the property parameters to the screen
//----------------------------------------------------------------------------------------
void Material::show_properties()
{
	//kinetic viscosity
	nu = AMAX1(eta, zeta)/rho0;
	
	cout<<"Material: "<<material_name<<"\n";		
	cout<<"The heat capacity is  "<<cv<<" J/kg/K\n";
	cout<<"The viscosity is "<<eta<<" Pa.s \n";
	cout<<"The heat conduction coefficient is "<<kappa<<" J/s/m^2/T\n";
	cout<<"The heat ratio is "<<gamma<<"\n";
	cout<<"The reference pressure b0 is "<<b0<<" Pa\n";
	cout<<"The reference density is "<<rho0<<" kg/m^3 \n";
	cout<<"The premited compressibilty a0 is "<<1.0/a0*100.0<<" percent\n";
}
//----------------------------------------------------------------------------------------
//			obtain parameter b0
//			after nondimensionlization finished
//----------------------------------------------------------------------------------------
void Material::Get_b0(double sound)
{
	//compressiblity
	b0 = a0*sound/gamma;
}
//----------------------------------------------------------------------------------------
//					get pressure
//----------------------------------------------------------------------------------------
double Material::get_p(double rho)
{
	return b0*pow(rho/rho0,gamma);
}

double Material::get_p(double rho, double e)
{
  return (gamma-1)*rho*e;
}
//----------------------------------------------------------------------------------------
//					get rho from pressure
//----------------------------------------------------------------------------------------
double Material::get_rho(double p)
{
	return rho0*pow(p/b0, 1.0/gamma);
}
double Material::get_rho(double p, double e)
{
  return p/((gamma-1)*e);
}


//----------------------------------------------------------------------------------------
//				get temperaturey
//----------------------------------------------------------------------------------------
double Material::get_T(double e)
{
  return e/cv;
}

double Material::get_T(double p, double rho)
{
  return p/((gamma-1)*rho*cv);
}



//----------------------------------------------------------------------------------------
//				get internal energy
//----------------------------------------------------------------------------------------
double Material::get_e(double T)
{
	return cv*T;
}
//----------------------------------------------------------------------------------------
//					get sound speed
//----------------------------------------------------------------------------------------
double Material::get_Cs(double p, double rho)
{
	return sqrt(gamma*p/rho);
}
