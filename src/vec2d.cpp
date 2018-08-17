// vec2d.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>,

//----------------------------------------------------------------------------------------
//      Define 2-d vectors and associated operations
//		Vec2d.cpp
//----------------------------------------------------------------------------------------

#include <cmath>
#include "vec2d.h"


Vec2d::Vec2d(){
    enum {X, Y};
    D[X] = D[Y] = 0.0;
}

Vec2d::Vec2d(double xval , double yval){
    enum {X, Y};
    D[X] = xval;
    D[Y] = yval;
}

Vec2d::Vec2d(const Vec2d &v){
  enum {X, Y};
  D[X] = v[X];
  D[Y] = v[Y];
}

Vec2d::Vec2d(double a) {
    enum {X, Y};
    D[X] = D[Y] = 0.0;
}
