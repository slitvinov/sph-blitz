///\file mls.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      The Moving Least Squares Approximation
//		mls.cpp
//----------------------------------------------------------------------------------------
// ***** system includes *****
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

// ***** localincludes *****
#include "vv.h"
#include "glbfunc.h"
#include "quinticspline.h"
#include "initiation.h"
#include "particle.h"

#include "dllist.h"
#include "mls.h"

using namespace std;

//----------------------------------------------------------------------------------------
//								constructor
//----------------------------------------------------------------------------------------
MLS::MLS(int MLS_MAX_)
{
  int k;
  MLS_MAX = MLS_MAX_;
  ///- declares the weighted moment matrix and assigns it to corresponding pointer
  B = new double *[3];
  for(k = 0; k < 3; k++) B[k] = new double[MLS_MAX];

  ///- declares the ploynomial basis matrix and assigns it to corresponding pointer
  pi = new double*[3];
  for(k = 0; k < 3; k++) pi[k] = new double[MLS_MAX];

  ///- declares the weights and assigns it to corresponding pointer
  Wi = new double[MLS_MAX]; 

  ///- declares shape function matrix and assigns it to corresponding pointer
  phi = new double[MLS_MAX]; 

}
//----------------------------------------------------------------------------------------
//						calculate the shape function 
//----------------------------------------------------------------------------------------
void MLS::MLS_Solver(int order)
{
  int i, k, m;
  double inter1, inter[3]; //temporary variables
  int ord; //avalible order of accuracy

  // calculate the weighted moment matrix
  for(k = 0; k < 3; k++) 
    for(m = 0; m < 3; m++) {
      A[k][m] = 0.0;
      for(i = 0; i < N; i++) A[k][m] += pi[k][i]*pi[m][i]*Wi[i];
    }

  // calculate the B matrix 
  for(k = 0; k < 3; k++) 
    for(i = 0; i < N; i++) B[k][i] = pi[k][i]*Wi[i];
	
  //calculate the inverse of the weighted moment matrix
  //if there is singularity, the accuracy order is degenerated
  ord = SymmetricInverse3x3(A);
	
  //acuracy given by user
  if(order < ord) ord = order;

  if(ord == 0) {
    //intermediate values
    inter1 = 0.0;
    for(i = 0; i < N; i++) 	inter1 += Wi[i];
    //the shape function
    for(i = 0; i < N; i++) 	phi[i] = Wi[i]/inter1;
  }
  else {
    //intermediate values
    for(k = 0; k < 3; k++) {
      inter[k] = 0.0;
      for(m = 0; m < 3; m++) inter[k] += p[m]*A[m][k];
    }
    //the shape function
    for(i = 0; i < N; i++) {
      phi[i] = 0.0;
      for(k = 0; k < 3; k++)	phi[i] += inter[k]*B[k][i];
    }
  }

}
//----------------------------------------------------------------------------------------
//				set up the enviroment for MLS calculation and run MLS solver
//----------------------------------------------------------------------------------------
void MLS::MLSMapping(double point[2], Llist<Particle> &NNP_list, QuinticSpline &weight_function, int order)
{
  N = 0; //numbers of reference points
  p[0] = 1.0; p[1] = point[0]; p[2] = point[1];
		
  //iterate this cell list
  for (LlistNode<Particle> *pstn = NNP_list.first(); 
       !NNP_list.isEnd(pstn); 
       pstn = NNP_list.next(pstn)) {
				
    //get particle data
    Particle *prtl = NNP_list.retrieve(pstn);
    Wi[N] = w(&weight_function, vv_distance(point, prtl->R));
    //assign values
    pi[0][N] = 1.0;
    pi[1][N] = prtl->R[0];
    pi[2][N] = prtl->R[1];
    B[0][N] = pi[0][N]*Wi[N];
    B[1][N] = pi[1][N]*Wi[N];
    B[2][N] = pi[2][N]*Wi[N];

    N ++;
  }

  //check if N is too big!
  if(N >= MLS_MAX) {
    cout << "\n Moving Least Squares: the reference particle number larger than largest promitted! \n";
    std::cout << __FILE__ << ':' << __LINE__ << std::endl;
    exit(1);
  }

  //calculate the shape function 
  MLS_Solver(order);
}

