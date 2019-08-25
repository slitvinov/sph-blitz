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
#include "volume.h"
#include "macro.h"


void VolumeMass(List *particle_list, ParticleManager *particles, QuinticSpline *weight_function)
{
    enum {X, Y};
    double reciprocV;
    double dstc;
    double eij[2];
    ListNode *p, *p1;
    Particle *prtl_org, *prtl_dest;
    LOOP_P(prtl_org, particle_list) {
	particles->BuildNNP(prtl_org->R);
	reciprocV = 0.0;
	LOOP1_P(prtl_dest, particles->NNP_list) {
	    dstc = vv_distance(prtl_org->R, prtl_dest->R);
	    eij[X] = (prtl_org->R[X] - prtl_dest->R[X])/(dstc + 1.e-30);
	    eij[Y] = (prtl_org->R[Y] - prtl_dest->R[Y])/(dstc + 1.e-30);
	    reciprocV += w(weight_function, dstc);
	}
	reciprocV = 1.0/reciprocV;
	prtl_org->V = reciprocV;
	prtl_org->m = prtl_org->rho*reciprocV;
	list_clear(particles->NNP_list);
    }
}
