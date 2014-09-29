#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

// ***** local includes *****
#include "glbfunc.h"
#include "main.h"

using namespace std;

int main() {
  ///Bltzmann constant
  /// will be non-dimensionalized in the program
  ofstream myfile;
  myfile.open ("out-test");

  double smoothinglength;
  int nstep = 50;
  double q;


  for (smoothinglength=0.05; smoothinglength<0.1; smoothinglength+=0.03) {
    myfile << "# smoothinglength = " << smoothinglength << "\n";
    QuinticSpline Ke(smoothinglength);
    for (int istep=0; istep<nstep; istep++) {
      q = smoothinglength * istep / double(nstep);
      myfile << q << " " << Ke.w(q) << "\n";    
    }    
    myfile << "\n";
  }
  myfile.close();
  return 0;
}
