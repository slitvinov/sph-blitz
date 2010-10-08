#include <iostream>
#include <boost/foreach.hpp>
#include <blitz/tinyvec-et.h>
#include <blitz/tinymat.h>
#include <blitz/array.h>
#include <cstdlib>

blitz::TinyMatrix<double, 3, 3> RotMat(const blitz::TinyVector<double, 3> u, const double theta) {
  const double cost = cos(theta);
  const double sint = sin(theta);
  const double omcos = 1 - cos(theta);
  blitz::TinyMatrix<double, 3, 3> R;
  R = 
    cost + u[0]*u[0]*omcos, u[0]*u[1]*omcos-u[2]*sint, u[0]*u[2]*(1-cost) + u[1]*sint,
     u[1]*u[0]*omcos + u[2]*sint, cost+u[1]*u[1]*omcos, u[1]*u[2]*omcos - u[0]*sin(theta),
     u[2]*u[0]*omcos - u[1]*sin(theta), u[2]*u[1]*omcos+u[0]*sint, cost+u[2]*u[2]*omcos
    ;
  return R;
}

int main() {
  const int ndim = 2;
  blitz::TinyVector<double, ndim> x;
  blitz::TinyVector<double, ndim> y;
  blitz::TinyMatrix<double, ndim, ndim> A;
  
  std::cerr << "blitz++\n";

  x = 1.0, 2.0;
  A = 1.0, 2.0,
    0.0, 0.0;
    
  std::cout << "x = " << x << '\n';
  std::cout << "A = " << A << '\n';
  y = product(A, x);
  std::cout << "A*x = " << y << '\n';

  const blitz::TinyVector<double, ndim> q(1.0, 4.5);
  ///q(1) = 1.0; /// compilation error
  
  /// does BOOST_FOREACH work for TinyVector?
  BOOST_FOREACH(const double x, q) {
    std::cout << "x = " <<  x << '\n';
  }

  //x(2) = 10.0; // runtime error if compiled with -DBZ_DEBUG

  // get raw data
  std::cout << "befor modification: x = " << x << '\n';
  double* p = x.data();
  p[0] = 7.0;
  p[1] = 42.0;
  std::cout << "after modification: x = " << x << '\n';

  std::cout << "x.length() = " << x.length() << '\n';
  x+=1.0;
  std::cout << "plus one: x = " << x << '\n';

  std::cout << "sum(x) = " << sum(x) << '\n';
  std::cout << "product(x) = " << product(x) << '\n';

  y = x;
  y(1) = 139.0;
  std::cout << "x = " << x << '\n';

  y = sin(x);
  std::cout << "sin(x) = " << y << '\n';

  // Rotation matrix 
  // http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_given_an_axis_and_an_angle
  // axis is given by unit vector
  const blitz::TinyVector<double, 3> u(1.0, 0.0, 0.0);
  const double theta = 0.5;
  blitz::TinyMatrix<double, 3, 3> R;

  R = RotMat(blitz::TinyVector<double, 3>(1.0, 0.0, 0.0), 0.0);
  std::cout << R << '\n';

  R = RotMat(blitz::TinyVector<double, 3>(0.0, 1.0, 0.0), 0.0);
  std::cout << R << '\n';

  R = RotMat(blitz::TinyVector<double, 3>(0.0, 0.0, 1.0), 0.0);
  std::cout << R << '\n';

  blitz::TinyMatrix<double, 3, 3> R1, R2, dR;
  R1 = RotMat(blitz::TinyVector<double, 3>(0.0, 1.0, 0.0), 0.1);
  R2 = RotMat(blitz::TinyVector<double, 3>(0.0, 1.0, 0.0), 0.1);
  R = RotMat(blitz::TinyVector<double, 3>(0.0, 1.0, 0.0), 0.2);

  // std::cout << R - R1 - R2 << '\n';

  return EXIT_SUCCESS;
}
