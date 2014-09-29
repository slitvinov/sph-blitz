#include <iostream>
#include <fstream>
#include <cmath>
#include <gsl/gsl_histogram.h>
#include "main.h"

using namespace std;
//double k_bltz  = 1.380662e-023; //[J/K]

int main() {
  double x;
  double y;
  Wiener wi;
  gsl_histogram * h = gsl_histogram_alloc (100);
  gsl_histogram_set_ranges_uniform(h, -3.0, 3.0);

  wi.Ranils();

  //  fstream fout("gaussian.dat", ios::out);  
  FILE* fout;
  fout = fopen ("gaussian.dat", "w");
  for (int i=0; i<100000; i++) {
    wi.Gaussian(x, y);
    gsl_histogram_increment(h, y);
    //    fout << x << ' ' << y << '\n';
  }
  gsl_histogram_fprintf(fout, h, "%e", "%e");
  fclose(fout);
  gsl_histogram_free (h);
  return 0;

}
