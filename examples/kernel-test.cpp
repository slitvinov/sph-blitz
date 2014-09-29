#include <iostream>
#include <fstream>
#include "main.h"

using namespace std;
//double k_bltz  = 1.380662e-023; //[J/K]

int main() {
  ///Bltzmann constant
  /// will be non-dimensionalized in the program
  ofstream myfile;
  myfile.open ("output/kernel-test.dat");

  double smoothinglength = 0.1;
  int nstep = 50;
  double q;

  QuinticSpline Ke(smoothinglength);
  for (int istep=0; istep<nstep; istep++) {
    q = smoothinglength * istep / double(nstep);
    myfile << q << " " << Ke.w(q) << ' ' << Ke.F(q) << '\n';    
  }
  myfile.close();
  return 0;
}
