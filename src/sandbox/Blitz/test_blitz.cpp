#include <iostream>
#include <boost/foreach.hpp>
#include <blitz/tinyvec-et.h>
#include <blitz/tinymat.h>
#include <blitz/array.h>
#include <cstdlib>

#ifdef USE_UBLAST
#include <boost/numeric/ublas/lu.hpp>
namespace bnu = boost::numeric::ublas;

int determinant_sign(const bnu::permutation_matrix<std ::size_t>& pm)
{
    int pm_sign=1;
    std::size_t size = pm.size();
    for (std::size_t i = 0; i < size; ++i)
        if (i != pm(i))
            pm_sign *= -1.0; // swap_rows would swap a pair of rows here, so we change sign
    return pm_sign;
}
 
double determinant( bnu::matrix<double>& m ) {
    bnu::permutation_matrix<std ::size_t> pm(m.size1());
    double det = 1.0;
    if ( bnu::lu_factorize(m,pm) ) {
        det = 0.0;
    } else {
        for(int i = 0; i < m.size1(); i++) 
            det *= m(i,i); // multiply by elements on diagonal
        det = det * determinant_sign( pm );
    }
    return det;
}

bnu::matrix<double> TinyToBNU(const blitz::TinyMatrix<double, 3, 3> tm) {
  bnu::matrix<double> m(3, 3);
  for (int i=0; i<3; i++) {
    for (int j=0; j<3; j++) {
      m(i, j) = tm(i, j);
    }
  }
  return m;
}
#endif

blitz::TinyMatrix<double, 3, 3> RotMat(const blitz::TinyVector<double, 3> u, const double theta) {
  const double cost = cos(theta);
  const double sint = sin(theta);
  const double omcos = 1 - cos(theta);
  const double ux = u[0];
  const double uy = u[1];
  const double uz = u[2];
  blitz::TinyMatrix<double, 3, 3> R;
  R = 
    cost + ux*ux*omcos, ux*uy*omcos-uz*sint, ux*uz*omcos + uy*sint,
     uy*ux*omcos + uz*sint, cost+uy*uy*omcos, uy*uz*omcos - ux*sint,
     uz*ux*omcos - uy*sint, uz*uy*omcos+ux*sint, cost+uz*uz*omcos
    ;
  return R;
}

blitz::TinyMatrix<double, 3, 3> VelMat(const blitz::TinyVector<double, 3> u, const double theta, const double omega) {
  const double dcost = -sin(theta) * omega;
  const double dsint = cos(theta) * omega;
  const double domcos = sin(theta) * omega;
  const double ux = u[0];
  const double uy = u[1];
  const double uz = u[2];
  blitz::TinyMatrix<double, 3, 3> R;
  R = 
    dcost + ux*ux*domcos, ux*uy*domcos-uz*dsint, ux*uz*domcos + uy*dsint,
     uy*ux*domcos + uz*dsint, dcost+uy*uy*domcos, uy*uz*domcos - ux*dsint,
     uz*ux*domcos - uy*dsint, uz*uy*domcos+ux*dsint, dcost+uz*uz*domcos
    ;
  return R;
}

int main() {
  blitz::TinyVector<double, 2> x;
  blitz::TinyVector<double, 2> y;
  blitz::TinyMatrix<double, 2, 2> A;

  blitz::TinyVector<double, 3> x3;
  blitz::TinyVector<double, 3> y3;
  
  std::cerr << "blitz++\n";

  x = 1.0, 2.0;
  A = 1.0, 2.0,
    0.0, 0.0;
    
  std::cout << "x = " << x << '\n';
  std::cout << "A = " << A << '\n';
  y = product(A, x);
  std::cout << "A*x = " << y << '\n';

  const blitz::TinyVector<double, 2> q(1.0, 4.5);
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
  std::cout << "x - y = " << x - y << '\n';
  std::cout << "cross(x, y) = " << cross(x3, y3) << '\n';

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

#ifdef USE_UBLAST  
  bnu::matrix<double> m;
  m = TinyToBNU(R1);
  std::cerr << "det(m) = " << determinant(m) << '\n';

  m = TinyToBNU(R2);
  std::cerr << "det(m) = " << determinant(m) << '\n';
#endif
  
  return EXIT_SUCCESS;
}
