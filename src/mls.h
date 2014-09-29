#ifndef MLS_H
#define MLS_H

#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
#include "vec2d.h"
//#include "wiener.h"
#include "dllist.h"
//#include "initiation.h"
//#include "particle.h"
//#include "quinticspline.h"

class QuinticSpline;
class Initiation;
//class Particle;
class Node;
//-----------------------------------------------------------------------
//			Using Moving Least Squares Approximation
//			2D and linear aproximation
//			based on (Liu GR, Mesh Free Methods->Moving beyond the finite element method, 
//			CRC press, London, 2003, p79-87)
//-----------------------------------------------------------------------

/// Moving Least Squares Approximation class
class MLS {
        ///numbers and maximum number of reference points
	int N, MLS_MAX;
	///weighted moment matrix
	double A[3][3], **B;
	double p[3], **pi; //ploynomial basis matrix
	///weights
	double *Wi; 

	///calculate the shape function and its derivatives
	void MLS_Solver(int order); 
	
public:	
	///shape function
	double *phi;

	///derivatives: have not been implemented!
	Vec2d *dphi;

	///constructor
	MLS(const Initiation* const ini);
	///MLS Mapping to grid points
	void MLSMapping(Vec2d &point, Llist<Node> &NNP_list, QuinticSpline &weight_function, int order);

};

#endif
