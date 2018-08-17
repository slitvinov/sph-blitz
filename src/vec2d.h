#ifndef VEC2D_H
#define VEC2D_H
/// \file vec2d.h
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes
/// \brief Define 2-d vectors and associated operations


/// 2-d vector class
class Vec2d {
private:
    double D[2];
public:
        ///constructor
        Vec2d();
        Vec2d(double xval, double yval);
        Vec2d(double val);

        ///copy constructor
        Vec2d(const Vec2d &);

        ///reload arithmetics operaters
        inline Vec2d operator=(const Vec2d &); ///equality
        inline Vec2d operator-() const; ///minus
        inline Vec2d operator+(const Vec2d &) const; ///plus
        inline Vec2d operator+=(const Vec2d &); ///accumulate
        inline Vec2d operator-(const Vec2d &) const; ///subtract
        inline Vec2d operator-=(const Vec2d &); ///subtract to
        inline Vec2d operator/(double a) const; ///divide
        inline Vec2d operator*(double a) const; ///multiply

        ///reload bool operaters
        inline bool operator>(const Vec2d &) const; ///larger
        inline bool operator<(const Vec2d &) const;	///smaller
        inline bool operator==(const Vec2d &) const; ///equal
        inline bool operator!=(const Vec2d &) const; ///non-equal

        inline double  operator  [](int i) const { return D[i]; }
        inline double& operator  [](int i)       { return D[i]; }

        ///other operations
        inline Vec2d normalized() const; ///normalize
        inline void set_zero(); ///set zero
        inline double abs() const;
        inline double sq() const; ///square value
        inline double sqdiff() const; ///v[0]^2 - v[1]^2

};



///-----------------------------------------------------------------
///			define inline functions
///-----------------------------------------------------------------

/// Copies the values
inline Vec2d Vec2d::operator=(const Vec2d &v){
  enum {X, Y};
  D[X] = v[X];
  D[Y] = v[Y];
  return *this;
}

/// Inverses the vector value sign
inline Vec2d Vec2d::operator-() const{
  enum {X, Y};
  return Vec2d(-D[X], -D[Y]);
}

/// The sum of the vectors
inline Vec2d Vec2d::operator+(const Vec2d &v)const{
  enum {X, Y};
  return Vec2d(D[X] + v[X], D[Y] + v[Y]);
}

/// Adds the other vector to this vector
inline Vec2d Vec2d::operator+=(const Vec2d &v) {
  enum {X, Y};
  D[X] += v[X];
  D[Y] += v[Y];
  return *this;
}

/// The difference of the vectors
inline Vec2d Vec2d::operator-(const Vec2d &v) const{
  enum {X, Y};
  return Vec2d(D[X] - v[X], D[Y] - v[Y]);
}

/// Subtracts the other vector from this vector
inline Vec2d Vec2d::operator-=(const Vec2d &v) {
    enum {X, Y};
    D[X] -= v[X];
    D[Y] -= v[Y];
    return *this;
}

/// Divides this vector by a double and returns the value
inline Vec2d Vec2d::operator/(double a) const{
  enum {X, Y};
  return Vec2d(D[X]/a, D[Y]/a);
}

/// Multiplies this vector with a double and returns the value
inline Vec2d Vec2d::operator*(double a) const{
  enum {X, Y};    
  return Vec2d(D[X]*a, D[Y]*a);
}

inline double Vec2d::abs() const {
    enum {X, Y};
    return sqrt(D[X]*D[X] + D[Y]*D[Y]);
}

/// Returns this vector normalized
inline Vec2d Vec2d::normalized() const{
  enum {X, Y};
  double len=abs();
  double rlen=( len==0? 0: 1.0/len);
  return Vec2d(D[X]*rlen, D[Y]*rlen);
}

/// Vector comparison: smaller than
inline bool Vec2d::operator<(const Vec2d &v) const{
  enum {X, Y};
  return  ((D[X]<v[X])||(D[Y]<v[Y]));
}

/// Vector comparison: larger than
inline bool Vec2d::operator>(const Vec2d &v) const{
  enum {X, Y};
  return  ((D[X]>v[X])||(D[Y]>v[Y]));
}

/// Vector comparison: equal
inline bool Vec2d::operator==(const Vec2d &v) const{
  enum {X, Y};
  return  (D[X]==v[X])&&(D[Y]==v[Y]);
}

/// Vector comparison: unequal
inline bool Vec2d::operator!=(const Vec2d &v) const{
  enum {X, Y};    
  return  (D[X]!=v[X])||(D[Y]!=v[Y]);
}


/// Set this vector to 0
inline void Vec2d::set_zero(){
  enum {X, Y};
  D[X] = D[Y] = 0.0;
}


/// Return the absolute value of the vector (the length)
inline double v_abs(const Vec2d &v) {
  enum {X, Y};
  return sqrt(v[X]*v[X] + v[Y]*v[Y]);
}

/// Return the square sum of the vector values
inline double v_sq(const Vec2d &v) {
  enum {X, Y};
  return v[X]*v[X] + v[Y]*v[Y];
}

/// Return the square difference of the vector values
inline double v_sqdiff(const Vec2d &v) {
  enum {X, Y};
  return v[X]*v[X] - v[Y]*v[Y];
}


/// Return the dot product of two vectors
inline double dot(const Vec2d &va, const Vec2d &vb){
  enum {X, Y};
  return (va[X]*vb[X] + va[Y]*vb[Y]);
}

/// Return the distance of two points given as vectors
inline double v_distance(const Vec2d &va, const Vec2d &vb){
    return v_abs(va - vb);
}

inline double product(const Vec2d &v) {
    enum {X, Y};
    return v[X]*v[Y];
}

/// Return the perodic position
inline void perodic_position(Vec2d &va, const Vec2d &vb, const Vec2d &perodic)
{
        if(vb[0] < perodic[0]/2) va[0] = vb[0] + perodic[0];
        else va[0] = vb[0] - perodic[0];

        if(vb[1] < perodic[1]/2) va[1] = vb[1] + perodic[1];
        else va[1] = vb[1] - perodic[1];

}

#endif //VEC2D_H
