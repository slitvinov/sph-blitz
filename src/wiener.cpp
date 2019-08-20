// wiener.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//-----------------------------------------------------------------------
//			Wiener process in two dimensions
//			wiener2d.cpp
//-----------------------------------------------------------------------
// ***** system includes *****
#include <stdlib.h>
#include <tgmath.h>

// ***** localincludes *****
#include "wiener.h"

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
Wiener::Wiener()
{	
	dimension = 2;
	ntab = 32;
	Ranils();
}
//----------------------------------------------------------------------------------------
//						produce wiener process with Flekkoy's form
//----------------------------------------------------------------------------------------
void Wiener::get_wiener(const double sqrtdt)
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
void Wiener::get_wiener_Espanol(const double sqrtdt)
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
}
//----------------------------------------------------------------------------------------
//				set the random seed
//----------------------------------------------------------------------------------------
void Wiener::Ranils()
{
	int j, k;

	//for random number generator
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
	    fprintf(stderr, "%s:%d: iy = %d : Wiener failed",  __FILE__, __LINE__, iy);
	    exit(1);
	}

}
//----------------------------------------------------------------------------------------
//		get two random numbers y1, y2 with guassian distribution with zero mean and variance one
//		from random numbers uniform distributed in [0, 1]
//----------------------------------------------------------------------------------------
void  Wiener::Gaussian(double &y1, double &y2)
{
	double x1, x2, w;
 
	do {
		x1 = 2.0 * Ranuls() - 1.0;
		x2 = 2.0 * Ranuls() - 1.0;
		w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 || w == 0.0);

	w = sqrt( (-2.0 * log( w ) ) / w );
	y1 = x1 * w;
	y2 = x2 * w;
}
