///read netcdf file
#ifndef INPUT_H
#define INPUT_H

#include "netcdfcpp.h"
#include <string>
#include <iostream>

using namespace std;
class Particle;
class Material;

///restart information class
class Input {
public:
  ///consructor
  explicit Input(string filename, 
		 Material*);
  ///get a new particle form the input
  Particle* Next();
  ///are there more particles in the input
  bool isEnd() const;
  ///get tiem from the restart file
  double getTime() const;
  ~Input();
private:
  ///the finel time
  double ctime;
  ///particle types array
  double* typec;
  ///densities array
  double* rhoc;
  ///temperatures array
  double* Tc;
  ///radius vectors array
  double* Rc;
  ///velocity vectors array
  double* Uc;
  ///the number of particle
  long iparticle_;
  ///the maximum number of particle
  long maxiparticle_;

  ///material
  Material* mtl_;
  
  ///the number of dimensions
  int ndim;
};

#endif
