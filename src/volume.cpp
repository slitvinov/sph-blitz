#include <stdio.h>
#include <string.h>
#include <math.h>
#include "particle.h"
#include "vv.h"
#include "dllist.h"
#include "ilist.h"
#include "list.h"
#include "quinticspline.h"
#include "particlemanager.h"
#include "hydrodynamics.h"
#include "volume.h"

#define LOOP(q, l) for (p = l.first();					\
    			!list_isEnd(&l, p) && (q = l.retrieve(p), 1);	\
			p = l.next(p))
#define LOOP1(q, l) for (p1 = l.first();				\
			 !list_isEnd(&l, p1) && (q = l.retrieve(p1), 1); \
			 p1 = l.next(p))

void VolumeMass(Hydrodynamics *hydro, ParticleManager *particles, QuinticSpline *weight_function)
{
    enum {X, Y};
    double reciprocV;
    double dstc;
    double eij[2], sumdw[2];
    ListNode *p, *p1;
    Particle *prtl_org, *prtl_dest;
    LOOP(prtl_org, hydro->particle_list) {
	particles->BuildNNP(prtl_org->R);
	reciprocV = 0.0; sumdw[X] = sumdw[Y] = 0.0;
	LOOP1(prtl_dest, particles->NNP_list) {
	    dstc = vv_distance(prtl_org->R, prtl_dest->R);
	    eij[X] = (prtl_org->R[X] - prtl_dest->R[X])/(dstc + 1.e-30);
	    eij[Y] = (prtl_org->R[Y] - prtl_dest->R[Y])/(dstc + 1.e-30);
	    reciprocV += w(weight_function, dstc);
	    sumdw[X] += eij[X]*F(weight_function, dstc);
	    sumdw[Y] += eij[Y]*F(weight_function, dstc);
	}
	reciprocV = 1.0/reciprocV;
	prtl_org->V = reciprocV;
	prtl_org->m = prtl_org->rho*reciprocV;
	particles->NNP_list.clear();
    }
}
