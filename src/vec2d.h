/// \file vec2d.h
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes
/// \brief Define 2-d vectors and associated operations

#ifndef VEC2D_H
#define VEC2D_H

#include <cmath>
#include <blitz/tinyvec.h>
#include <blitz/tinyvec-et.h>

using namespace blitz;

typedef TinyVector<double,2> Vec2d;
/*
/// 2-d vector class
class Vec2d {
	
public:
	//constructor
	Vec2d();
	Vec2d(double xval, double yval);

	//copy constructor
	Vec2d(const Vec2d &);  

	//reload arithmetics operaters
	inline Vec2d operator=(const Vec2d &); //equality
	inline Vec2d operator-() const; //minus
	inline Vec2d operator+(const Vec2d &) const; //plus
	inline Vec2d operator+=(const Vec2d &); //accumulate
	inline Vec2d operator-(const Vec2d &) const; //subtract
	inline Vec2d operator-=(const Vec2d &); //subtract to
	inline Vec2d operator/(double a) const; //divide
	inline Vec2d operator*(double a) const; //multiply
	
	//reload bool operaters
	inline bool operator>(const Vec2d &) const; //larger
	inline bool operator<(const Vec2d &) const;	//smaller
	inline bool operator==(const Vec2d &) const; //equal
	inline bool operator!=(const Vec2d &) const; //non-equal

	
	//other operations
	inline Vec2d normalized() const; //normalize
	inline void set_zero(); //set zero
	inline double abs() const; //absolute value
	inline double sq() const; //square value
	inline double sqdiff() const; //v[0]^2 - v[1]^2
	inline double xyprod() const; //product of x and y

	double x;     // coordinates
	double y;

public:
	//-----------------------------------------------------------------
	//other operations on vectors
	//-----------------------------------------------------------------
	static inline double dotprod(const Vec2d &va, const Vec2d &vb); //dot production
	//distance
	static inline double distance(const Vec2d &va, const Vec2d &vb);
	//perodic position
	static inline void perodic_position(Vec2d &va, const Vec2d &vb, const Vec2d &perodic);
};



//-----------------------------------------------------------------
//			define inline functions
//-----------------------------------------------------------------

/// Copies the values
inline Vec2d Vec2d::operator=(const Vec2d &v){
  x = v[0];
  y = v[1];
  return *this;
}

/// Inverses the vector value sign
inline Vec2d Vec2d::operator-() const{
  return Vec2d(-x, -y);
}

/// The sum of the vectors
inline Vec2d Vec2d::operator+(const Vec2d &v)const{
  return Vec2d(x + v[0], y + v[1]);
}

/// Adds the other vector to this vector
inline Vec2d Vec2d::operator+=(const Vec2d &v) {
	x += v[0];
	y += v[1];
	return *this;
}

/// The difference of the vectors
inline Vec2d Vec2d::operator-(const Vec2d &v) const{
  return Vec2d(x - v[0], y - v[1]);
}

/// Subtracts the other vector from this vector
inline Vec2d Vec2d::operator-=(const Vec2d &v) {
	x -= v[0];
	y -= v[1];
	return *this;
}

/// Divides this vector by a double and returns the value
inline Vec2d Vec2d::operator/(double a) const{
  return Vec2d(x/a, y/a);
}

/// Multiplies this vector with a double and returns the value
inline Vec2d Vec2d::operator*(double a) const{
  return Vec2d(x*a, y*a);
}

/// Returns this vector normalized
inline Vec2d Vec2d::normalized() const{
  double len=abs();
  double rlen=( len==0? 0: 1.0/len);
  return Vec2d(x*rlen, y*rlen);
}

/// Vector comparison: smaller than
inline bool Vec2d::operator<(const Vec2d &v) const{
  return  ((x<v[0])||(y<v[1]));
}

/// Vector comparison: larger than
inline bool Vec2d::operator>(const Vec2d &v) const{
  return  ((x>v[0])||(y>v[1]));
}

/// Vector comparison: equal
inline bool Vec2d::operator==(const Vec2d &v) const{
  return  (x==v[0])&&(y==v[1]);
}

/// Vector comparison: unequal
inline bool Vec2d::operator!=(const Vec2d &v) const{
  return  (x!=v[0])||(y!=v[1]);
}


/// Set this vector to 0
inline void Vec2d::set_zero(){
	x = y = 0.0;
}

*/

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
  //return v_abs(va-vb);
  //double dx=va[0]-vb[0];
  //double dy=va[1]-vb[1];
  return sqrt(sum(sqr(va-vb)));
}

/// Return the perodic position
inline void perodic_position(Vec2d &va, const Vec2d &vb, const Vec2d &perodic)
{
	if(vb[0] < perodic[0]/2) va[0] = vb[0] + perodic[0];
	else va[0] = vb[0] - perodic[0];

	if(vb[1] < perodic[1]/2) va[1] = vb[1] + perodic[1];
	else va[1] = vb[1] - perodic[1];

}

inline double sqr(double x) {
	return x*x;
}


#endif
