/// \file glbfunc.cpp
/// \ author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 
//      Define globle paremeters and functions

// ***** localincludes *****
#include "glbfunc.h"

// a. Get the maximum
double AMAX1(const double a, const double b) {
  if (a > b) return a;
  return b;
}

// b. Get the minimum
double AMIN1(const double a, const double b) {
  if (a < b) return a;
  return b;
}
