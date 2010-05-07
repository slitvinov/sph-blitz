// glbfunc.h
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

#ifndef GLBFUNC_H
#define GLBFUNC_H

//----------------------------------------------------------------------------------------
//      Define globle paremeters and functions
//		glbfunc.h
//----------------------------------------------------------------------------------------

//globle parameters
const double pi=3.141592653589793; // Pai 
//	a. Get the maximum
double AMAX1(double a, double b);
//	b. Get the minimum
double AMIN1(double a, double b);
//	c. Get the absolute
//double ABS(double a);
inline double ABS(double a) { return fabs(a); }
//	d. Sign of the first value is determined by the secomax_species_number value's sign
double SIGN(double a, double b);
//	e. Get the maximum from four
double AMAX4(double a, double b, double c, double d);
//	f. Get the inverse of symmetric array
int SymmetricInverse3x3(double M[3][3]);
//	g. Kronecker delta
double Kronecker(int a, int b);
//	h. Sign function
double K_sign(int a, int b);
//	h. comparing
double compare(int a, int b);
//  i. square
double sq(double a);

#endif
