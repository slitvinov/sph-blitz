/// \file vec2d.h
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes
/// \brief Define 2-d vectors and associated operations

#ifndef VEC2D_H
#define VEC2D_H
#include <blitz/tinyvec-et.h>

/// A type for two dimensional vector
typedef blitz::TinyVector<double,2> Vec2d;

/// defines the null-vector (0,0)
const Vec2d null_vector(0,0);
/// Return the absolute value of the vector (the length)
inline double v_abs(const Vec2d &v) {
  return sqrt(v[0]*v[0] + v[1]*v[1]);
}

/// Return the square sum of the vector values
inline double v_sq(const Vec2d &v) {
  return v[0]*v[0] + v[1]*v[1];
}

/// Return the square difference of the vector values
inline double v_sqdiff(const Vec2d &v) {
  return v[0]*v[0] - v[1]*v[1];
}/*
/// Return the product of the vector values
inline double Vec2d::xyprod() const {
  return x*y;
}

/// Return the dot product of two vectors
inline double Vec2d::dotprod(const Vec2d &va, const Vec2d &vb){
  return (va[0]*vb[0] + va[1]*vb[1]);
}
*/

/// Return the distance of two points given as vectors
inline double v_distance(const Vec2d &va, const Vec2d &vb){
  return sqrt(sum(sqr(va-vb)));
}

/// Return the perodic position
inline void perodic_position(Vec2d &va, const Vec2d &vb, const Vec2d &perodic)
{
  if(vb[0] < perodic[0]/2) {
    va[0] = vb[0] + perodic[0];
  } else {
    va[0] = vb[0] - perodic[0];
  }

  if (vb[1] < perodic[1]/2) {
    va[1] = vb[1] + perodic[1];
  } else {
    va[1] = vb[1] - perodic[1];
  }
}
#endif
