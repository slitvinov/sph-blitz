class Vec2d {
private:
    double D[2];
public:
    ///constructor
    Vec2d();
    Vec2d(double xval, double yval);

    ///copy constructor
    Vec2d(const Vec2d &);

    inline Vec2d operator-() const; ///minus
    inline Vec2d operator+(const Vec2d &) const; ///plus
    inline Vec2d operator+=(const Vec2d &); ///accumulate
    inline Vec2d operator-(const Vec2d &) const; ///subtract
    inline Vec2d operator-=(const Vec2d &); ///subtract to
    inline Vec2d operator/(double a) const; ///divide
    inline Vec2d operator*(double a) const; ///multiply

    inline double  operator  [](int i) const { return D[i]; }
    inline double& operator  [](int i)       { return D[i]; }
};

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

inline double vv_abs(double v[2]) {
    enum {X, Y};
    return sqrt(v[X]*v[X] + v[Y]*v[Y]);
}

/// Return the distance of two points given as vectors
inline double vv_distance(double a[2], double b[2]){
    enum {X, Y};
    double x, y;
    x = a[X] - b[X];
    y = a[Y] - b[Y];
    return sqrt(x*x + y*y);
}

/// Return the distance of two points given as vectors
inline double vv_sq_distance(double a[2], double b[2]){
    enum {X, Y};
    double x, y;
    x = a[X] - b[X];
    y = a[Y] - b[Y];
    return x*x + y*y;
}
