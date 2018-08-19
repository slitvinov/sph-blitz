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

class Particle;
class Force;
class Initiation;
class QuinticSpline;
class Material;
class ParticleManager;
class Boundary;

// ***** localincludes *****
#include "vec2d.h"
#include "kernel.h"
#include "dllist.h"
#include "interaction.h"
#include "hydrodynamics.h"
#include "initiation.h"
#include "force.h"
#include "glbfunc.h"

using namespace std;

//total number of materials
int Force::number_of_materials = 0;
//smoothinglenth
double Force::smoothinglength = 0.0;

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
	smoothinglength = ini.smoothinglength;
}

