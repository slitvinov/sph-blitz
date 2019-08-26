#include <stdio.h>
#include <string.h>
#include <tgmath.h>
#include "particle.h"
#include "vv.h"
#include "list.h"
#include "quinticspline.h"
#include "manager.h"
#include "volume.h"
#include "macro.h"


void VolumeMass(struct List *particle_list, struct Manager *particles, struct QuinticSpline *weight_function)
{
    enum {X, Y};
    double reciprocV;
    double dstc;
    struct ListNode *p, *p1;
    struct Particle *prtl_org, *prtl_dest;
    LOOP_P(prtl_org, particle_list) {
	manager_build_nnp(particles, prtl_org->R);
	reciprocV = 0.0;
	LOOP1_P(prtl_dest, particles->NNP_list) {
	    dstc = vv_distance(prtl_org->R, prtl_dest->R);
	    reciprocV += w(weight_function, dstc);
 	}
	reciprocV = 1.0/reciprocV;
	prtl_org->V = reciprocV;
	prtl_org->m = prtl_org->rho*reciprocV;
	list_clear(particles->NNP_list);
    }
}
