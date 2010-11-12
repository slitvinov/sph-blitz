#include "src/tools/SPHProbe/utils.h"
#include <boost/test/minimal.hpp>

int test_main(int, char *[]) {
  const double delta = 4.0;
  const int npoints=100;
  for (int i=1; i<npoints; i++) {
    const double x = 2.0*static_cast<double>(i)/npoints * delta;
    std::cout << x << ' ' << m4prime(x, delta) << '\n';
  }
  return EXIT_SUCCESS;
}
