/// Quintic Spline test program 
#include "Kernel/quinticspline.h"
#include <boost/test/minimal.hpp>
#include <blitz/vector.h>
#include <blitz/array.h>
#include <numeric>

int test_main( int, char *[] )     {  
  const double eps  = 1e-3;
  const double supportlength = 0.3;
  const double pi = 3.141592653589793;
  QuinticSpline weight_function (supportlength);
  
  /// check "very big" x
  BOOST_CHECK( abs(weight_function.w( 2*supportlength)) < eps );
  BOOST_CHECK( abs(weight_function.w( 3*supportlength)) < eps );
  BOOST_CHECK( abs(weight_function.w( supportlength)) < eps );

  // create an array with kernel values
 const int numSamples = 2000;  // Number of samples
 const double dx = supportlength / numSamples; // step 
 firstIndex i;
 Array<double, 1> x(numSamples);
 x = dx * i;

 // integrate kernel 
 Array<double, 1> w(weight_function.w(x)*x);
 double s =  std::accumulate(w.begin(), w.end(), 0.0);
 s = s - 0.5*w(0) - 0.5*w(numSamples);
 s = 2.0 * pi * dx * s;
 BOOST_CHECK( abs(s - 1.0) < eps );


 // integrate the derivative of the kernel
 w = Array<double, 1>(weight_function.F(x)*x*x);
 s =  std::accumulate(w.begin(), w.end(), 0.0);
 s = s - 0.5*w(0) - 0.5*w(numSamples);
 s = pi * dx * s;
 BOOST_CHECK( abs(s - 1.0) < eps );

 // cumulative sum of the derivatives
 Array<double, 1> cumsum(numSamples);
 Array<double, 1> dw(weight_function.F(x));
 w = Array<double, 1>(weight_function.w(x));
 cumsum = 0.0;
 s = 0.0;
 for (int idx=0; idx<numSamples; idx++) {
   cumsum(numSamples-idx-1) = s * dx; 
   s += dw(numSamples - idx - 1);
 }
 w = Array<double, 1>(weight_function.w(x));
 for (int idx=0; idx<numSamples; idx++) {
   BOOST_REQUIRE( abs(cumsum(idx) - w(idx)) < eps*w(0.0) );
 }

  /// check integral of the kernel function
  /// use Trapezoidal Rule
  

  return EXIT_SUCCESS;
};
