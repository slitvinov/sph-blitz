//#define GSL_GAUSSIAN
#define GSL_USE
#define GSL_NORMAL


// wiener.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//-----------------------------------------------------------------------
//			Wiener process in two dimensions
//			wiener2d.cpp
//-----------------------------------------------------------------------
// ***** system includes *****
#include <iostream>
#include <cstdlib>
#include <cmath>



// ***** localincludes *****
#include "wiener.h"


using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
Wiener::Wiener()
{	
	int k;

	dimension = 2;

	//creat the Wiener matrix
	randoms = new double*[dimension];
	for(k = 0; k < dimension; k++) randoms[k] = new double[dimension];

	sym_trclss = new double*[dimension];
	for(k = 0; k < dimension; k++) sym_trclss[k] = new double[dimension];

	ntab = 32;
	iv = new long int[ntab];
	
	Ranils();

}
//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
Wiener::Wiener(int dimension)
{	
	int k;

	this->dimension = dimension;

	//creat the Wiener matrix
	randoms = new double*[dimension];
	for(k = 0; k < dimension; k++) randoms[k] = new double[dimension];

	sym_trclss = new double*[dimension];
	for(k = 0; k < dimension; k++) sym_trclss[k] = new double[dimension];
}
//----------------------------------------------------------------------------------------
//						produce wiener process with Flekkoy's form
//----------------------------------------------------------------------------------------
void Wiener::get_wiener(double sqrtdt)
{	
	double rd1, rd2;

	//two random numbers with Gaussian distribution
	Gaussian(rd1, rd2);
	
	//increments of Wieneir process
	Random_p = sqrtdt * rd1;
	Random_v = sqrtdt * rd2;

}
//----------------------------------------------------------------------------------------
//	produce wiener vlaue matrix with symmetric tracless part, and the trace/dimension
//	Please refer to Espanol's paper
//----------------------------------------------------------------------------------------
void Wiener::get_wiener_Espanol(double sqrtdt) 
{
	int i, j;
 	double rd1, rd2;

	Gaussian(rd1, rd2);
   
	//Wiener processe matrix
	for (i = 0; i < dimension; i++) {	
		Gaussian(rd1, rd2);
		randoms[i][0] = sqrtdt * rd1; randoms[i][1] = sqrtdt * rd2;
	}

	//trace/dimension
	trace_d = 0.0;
	for (i = 0; i < dimension; i++) trace_d += randoms[i][i];
	trace_d = trace_d/dimension;

	//symmeteric matrix
	for (i = 0; i < dimension; i++) 
		for (j = 0; j < dimension; j++) sym_trclss[i][j] = 0.5*(randoms[i][j] + randoms[j][i]);

	//tracless symmeteric matrix
	for (i = 0; i < dimension; i++) sym_trclss[i][i] -= trace_d;
}

//----------------------------------------------------------------------------------------
//			get the random number with uniform distribution in [0, 1]
//----------------------------------------------------------------------------------------
double Wiener::Ranuls() 
{
  //  double num;
  //  num = gsl_rng_uniform(rgen);
  //  cout << "num = " << num << endl;
#ifdef GSL_NORMAL
  return gsl_rng_uniform(rgen);
#else

	int j, k;
	
	//parameters
	long int in1 = 2147483563; 
	long int ik1 = 40014;
	long int iq1 = 53668;
	long int ir1 = 12211;
	long int in2 = 2147483399;
	long int ik2 = 40692;
	long int iq2 = 52774;
	long int ir2 = 3791;
	long int inm1 = in1 - 1;
	long int ndiv = 1 + inm1/ntab;
	double an = 1.0/(double)in1;

//	Linear congruential generactor 1

	k = idum/iq1;
	idum = ik1*(idum - k*iq1) - k*ir1;
	if(idum < 0) idum += in1;

//	Linear congruential generator 2

	k = idum2/iq2;
	idum2 = ik2*(idum2 - k*iq2) - k*ir2;
	if(idum2 < 0) idum2 += in2;

//	Shuffling and subtracting

	j = iy/ndiv;
	iy = iv[j] - idum2;
	iv[j] = idum;

	if(iy < 1) iy += inm1;

	return an*iy;
#endif
}
//----------------------------------------------------------------------------------------
//				set the random seed
//----------------------------------------------------------------------------------------
void Wiener::Ranils() 
{
#ifdef GSL_USE
	///set random number generator
	const gsl_rng_type * T;
	//	  gsl_rng * rgen;
	//	gsl_rng_env_setup();
	T = gsl_rng_taus;
	rgen = gsl_rng_alloc (T);
	gsl_rng_set(rgen, (unsigned)time( NULL ));
#else
	//for random number generator
	int j, k;
	long int in = 2147483563; 
	long int ik = 40014; 
	long int iq = 53668; 
	long int ir = 12211; 

	iseed = rand();

	//	Initial seeds for two random number generators
	idum = iseed + 123456789;
	idum2 = idum;

	//	Load the shuffle table (after 8 warm-ups)
	for( j = ntab+7; j>=0; j--) {
	  k = idum/iq;
	  idum = ik*(idum - k*iq) - k*ir;
	  if(idum < 0) idum = idum + in;
	  if(j < ntab) iv[j] = idum;
	}
	iy = iv[0];
	if(iy < 0) {
		cout<<"iy ="<<iy<<"   Wiener: Random number fails \n"; 
		exit(1);
	}
#endif
}
//----------------------------------------------------------------------------------------
//		get two random numbers y1, y2 with guassian distribution with zero mean and variance one
//		from random numbers uniform distributed in [0, 1]
//----------------------------------------------------------------------------------------
void  Wiener::Gaussian(double &y1, double &y2)  
{
#ifdef GSL_GAUSSIAN
  y1 = gsl_ran_gaussian(rgen, 1.0);
  y2 = gsl_ran_gaussian(rgen, 1.0);
#else
  double x1, x2, w;
  do {
    x1 = 2.0 * Ranuls() - 1.0;
    x2 = 2.0 * Ranuls() - 1.0;
    w = x1 * x1 + x2 * x2;
  } while ( w >= 1.0 || w == 0.0);
  w = sqrt( (-2.0 * log( w ) ) / w );
  y1 = x1 * w;
  y2 = x2 * w;
#endif
}

Wiener::~Wiener() {
#ifdef GSL_USE
  gsl_rng_free (rgen);
#endif
}
