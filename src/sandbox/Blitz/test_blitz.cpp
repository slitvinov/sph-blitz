#include <iostream>
#include <boost/foreach.hpp>
#include <blitz/tinyvec-et.h>
#include <blitz/tinymat.h>
#include <blitz/array.h>
#include <cstdlib>

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

  return EXIT_SUCCESS;
}
