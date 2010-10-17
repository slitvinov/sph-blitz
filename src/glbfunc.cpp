/// \file glbfunc.cpp
/// \ author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 
//      Define global paremeters and functions

// ***** localincludes *****
#include "glbfunc.h"

// a. Get the maximum
double AMAX1(const double a, const double b) {
  if (a > b) return a;
  return b;
}

// b. Get the minimu (with 2 arguments)
double AMIN1(const double a, const double b) {
  if (a < b) return a;
  return b;
}

// c. Get the minimum with 3 arguments
double AMIN1(const double a, const double b, const double c) {
  double intermediateMin; 
  if (a < b)
    intermediateMin=a;
  else intermediateMin=b;
  if (intermediateMin<c)
    return intermediateMin;
  return c;
}

// d. Get the minimum with 4 arguments
double AMIN1(const double a, const double b, const double c, const double d) {
  double intermediateMin1; 
  double intermediateMin2;
  if (a < b)
    intermediateMin1=a;
  else  intermediateMin1=b;
  if (c<d)
    intermediateMin2=c;
  else  intermediateMin2=d;
  if (intermediateMin1<intermediateMin2)
    return intermediateMin1;
  return intermediateMin2;
}

