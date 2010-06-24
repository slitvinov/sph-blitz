// force.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//-------------------------------------------------------------------
//				Define force properties
//				force.cpp
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
#include "initiation.h"
#include "force.h"

using namespace std;

//total number of materials
int Force::number_of_materials = 0;
//smoothinglenth
double Force::supportlength = 0.0;

//----------------------------------------------------------------------------------------
//					constructor
//----------------------------------------------------------------------------------------
Force::Force()
{
}
//----------------------------------------------------------------------------------------
//					constructor
//----------------------------------------------------------------------------------------
Force::Force(Initiation &ini)
{
	//total number of materials
	number_of_materials = ini.number_of_materials;
	//smoothinglenth
	supportlength = ini.supportlength;
}
//----------------------------------------------------------------------------------------
//					non-dimensionalize
//----------------------------------------------------------------------------------------
void Force::non_dimensionalize(Initiation &ini)
{
		sigma = ini.non_dms_surface(sigma);
		shear_slip = ini.non_dms_length(shear_slip);
		bulk_slip = ini.non_dms_length(bulk_slip);
}

