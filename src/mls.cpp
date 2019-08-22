#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "particle.h"
#include "list.h"
#include "vv.h"
#include "glbfunc.h"
#include "quinticspline.h"
#include "initiation.h"
#include "dllist.h"
#include "mls.h"
using namespace std;
MLS::MLS(int MLS_MAX_)
{
  int k;
  MLS_MAX = MLS_MAX_;
  B = new double *[3];
  for(k = 0; k < 3; k++) B[k] = new double[MLS_MAX];
  pi = new double*[3];
  for(k = 0; k < 3; k++) pi[k] = new double[MLS_MAX];
  Wi = new double[MLS_MAX]; 
  phi = new double[MLS_MAX]; 
}
void MLS::MLS_Solver(int order)
{
  int i, k, m;
  double inter1, inter[3]; 
  int ord; 
  for(k = 0; k < 3; k++) 
    for(m = 0; m < 3; m++) {
      A[k][m] = 0.0;
      for(i = 0; i < N; i++) A[k][m] += pi[k][i]*pi[m][i]*Wi[i];
    }
  for(k = 0; k < 3; k++) 
    for(i = 0; i < N; i++) B[k][i] = pi[k][i]*Wi[i];
  ord = SymmetricInverse3x3(A);
  if(order < ord) ord = order;
  if(ord == 0) {
    inter1 = 0.0;
    for(i = 0; i < N; i++) 	inter1 += Wi[i];
    for(i = 0; i < N; i++) 	phi[i] = Wi[i]/inter1;
  }
  else {
    for(k = 0; k < 3; k++) {
      inter[k] = 0.0;
      for(m = 0; m < 3; m++) inter[k] += p[m]*A[m][k];
    }
    for(i = 0; i < N; i++) {
      phi[i] = 0.0;
      for(k = 0; k < 3; k++)	phi[i] += inter[k]*B[k][i];
    }
  }
}
void MLS::MLSMapping(double point[2], List &NNP_list, QuinticSpline &weight_function, int order)
{
  N = 0; 
  p[0] = 1.0; p[1] = point[0]; p[2] = point[1];
  for (ListNode *pstn = NNP_list.first(); 
       !NNP_list.isEnd(pstn); 
       pstn = NNP_list.next(pstn)) {
    Particle *prtl = NNP_list.retrieve(pstn);
    Wi[N] = w(&weight_function, vv_distance(point, prtl->R));
    pi[0][N] = 1.0;
    pi[1][N] = prtl->R[0];
    pi[2][N] = prtl->R[1];
    B[0][N] = pi[0][N]*Wi[N];
    B[1][N] = pi[1][N]*Wi[N];
    B[2][N] = pi[2][N]*Wi[N];
    N ++;
  }
  if(N >= MLS_MAX) {
    cout << "\n Moving Least Squares: the reference particle number larger than largest promitted! \n";
    std::cout << __FILE__ << ':' << __LINE__ << std::endl;
    exit(1);
  }
  MLS_Solver(order);
}
