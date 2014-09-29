// wiener.h
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

#ifndef WIENER_H
#define WIENER_H

//gsl random number generators
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
//#include <gsl_math.h>

//-----------------------------------------------------------------------
//		The class defining Wiener process in two dimensions
//-----------------------------------------------------------------------
class Wiener {

  int dimension;
  double **randoms;

  //for random number generator
  //variables
  long int idum, idum2, iy, ntab, iseed;
  long int *iv;
  //get the random number uniform distributed in [0, 1]
  double Ranuls();
  
  ///rundom number generator (gsl)
  ///http://www.gnu.org/software/gsl/manual/html_node/Random-Number-Generation.html#Random-Number-Generation
  gsl_rng * rgen;
  
public:

  double **sym_trclss;
  double trace_d;
  
  mutable double Random_p, Random_v;

  //get two random numbers y1, y2 with guassian distribution with zero mean and variance one
  //from random numbers uniform distributed in [0, 1]
  void Gaussian(double &y1, double &y2);
  //costructure
  Wiener();
  Wiener(int dimension);
  ~Wiener();
  //produce wiener vlaue matrix with symmetric tracless part, and the trace
  void get_wiener_Espanol(double sqrtdt); 
  //wiener process with Flekkoy's form
  void get_wiener(double sqrtdt);
  
  //set the random seed
  void Ranils();
};
#endif
