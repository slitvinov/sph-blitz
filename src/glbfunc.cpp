///\file glbfunc.cpp
///\ author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      Define globle paremeters and functions
//		glbfunc.h
//----------------------------------------------------------------------------------------
// ***** system includes *****
#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cmath>

// ***** localincludes *****
#include "glbfunc.h"

using namespace std;
//global parameters
const double pi=3.141592653589793; ///<Pi 

//----------------------------------------------------------------------------------------
//	a. Get the maximum
//----------------------------------------------------------------------------------------
double AMAX1(double a, double b){
	if(a > b) return a;
	return b;
}
//----------------------------------------------------------------------------------------
//	b. Get the minimum
//----------------------------------------------------------------------------------------
double AMIN1(double a, double b){
	if(a < b) return a;
	return b;
}
