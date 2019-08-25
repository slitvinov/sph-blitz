#include <stdio.h>
#include <stdlib.h>
#include "particle.h"
#include "list.h"
#include "vv.h"
#include "glbfunc.h"
#include "quinticspline.h"
#include "mls.h"
#include "macro.h"
#include "err.h"

struct MLS *mls_ini(int MLS_MAX)
{
    struct MLS *q;
    int k;
    q = (struct MLS*)malloc(sizeof(*q));
    if (q == NULL)
	return NULL;
    
    q->MLS_MAX = MLS_MAX;
    q->Wi = (double*)malloc(MLS_MAX*sizeof(*q->Wi));
    q->phi =(double*)malloc(MLS_MAX*sizeof(*q->phi)); 
    for(k = 0; k < 3; k++)
	q->B[k] = (double*)malloc(MLS_MAX*sizeof(double));
    for(k = 0; k < 3; k++)
	q->pi[k] = (double*)malloc(MLS_MAX*sizeof(double));
    return q;
}

int mls_fin(struct MLS *q)
{
    int k;
    free(q->Wi);
    free(q->phi);
    for(k = 0; k < 3; k++)
	free(q->B[k]);
    for(k = 0; k < 3; k++)
	free(q->pi[k]);
    free(q);
    return 0;
}

int mls_solve(struct MLS *q, int order)
{
    int i, k, m;
    double inter1, inter[3]; 
    int ord;
    double *A;
    double **B;
    double *p;
    double *phi;
    double **pi;
    double *Wi;
    int N;

    A = q->A;
    B = q->B;
    p = q->p;
    phi = q->phi;
    pi = q->pi;
    Wi = q->Wi;
    N = q->N;
  
    for(k = 0; k < 3; k++) 
	for(m = 0; m < 3; m++) {
	    A[3*k+m] = 0.0;
	    for(i = 0; i < N; i++) A[3*k+m] += pi[k][i]*pi[m][i]*Wi[i];
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
	    for(m = 0; m < 3; m++) inter[k] += p[m]*A[3*m+k];
	}
	for(i = 0; i < N; i++) {
	    phi[i] = 0.0;
	    for(k = 0; k < 3; k++)	phi[i] += inter[k]*B[k][i];
	}
    }
    return 0;
}
int mls_map(struct MLS *q, double point[2], struct List *NNP_list, struct QuinticSpline *weight_function, int order)
{
    struct Particle *prtl;
    struct ListNode *p1;
    double **B;
    double *p;
    double **pi;
    double *Wi;
    int N;
    int MLS_MAX;

    B = q->B;
    p = q->p;
    pi = q->pi;
    Wi = q->Wi;
    MLS_MAX = q->MLS_MAX;
    
    N = 0; 
    p[0] = 1.0; p[1] = point[0]; p[2] = point[1];
    LOOP1_P(prtl, NNP_list) {
	Wi[N] = w(weight_function, vv_distance(point, prtl->R));
	pi[0][N] = 1.0;
	pi[1][N] = prtl->R[0];
	pi[2][N] = prtl->R[1];
	B[0][N] = pi[0][N]*Wi[N];
	B[1][N] = pi[1][N]*Wi[N];
	B[2][N] = pi[2][N]*Wi[N];
	N ++;
    }
    if(N >= MLS_MAX)
	ABORT(("the reference particle number larger than largest permited"));
    q->N = N;
    return mls_solve(q, order);
}
