/// \file glbfunc.cpp
/// \ author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Sergey Litvinov <slitvinov@gmail.com>
//      Define globle paremeters and functions
#include "glbfunc.h"
#include <algorithm>

double AMIN3(const double a, const double b, const double c) {
  return std::min(a, std::min(b, c)); 
}
