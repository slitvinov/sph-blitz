#include <stdio.h>
#include <string.h>
#include <math.h>
#include "vv.h"
#include "dllist.h"
#include "quinticspline.h"
#include "particlemanager.h"
#include "hydrodynamics.h"
#include "particle.h"
#include "volume.h"

//----------------------------------------------------------------------------------------
//					predict the particle volume and mass
//----------------------------------------------------------------------------------------
void VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, QuinticSpline &weight_function)
{
    enum {X, Y};
    double reciprocV; //the inverse of volume or volume
    double dstc;
    double eij[2], sumdw[2];
    LlistNode<Particle> *p, p1;

    /// <ul><li>iterate particles on the particle list
    for (p = hydro.particle_list.first(); 
	 !hydro.particle_list.isEnd(p); 
	 p = hydro.particle_list.next(p)) {
					
	/// <ul><li> pick an origin particle
	Particle *prtl_org = hydro.particle_list.retrieve(p);
	/// <li> build the nearest neighbor particle list for chosen origin particle
	particles.BuildNNP(prtl_org->R);

	reciprocV = 0.0; sumdw[X] = sumdw[Y] = 0.0;
	/// <li>iterate this Nearest Neighbor Particle list
	for (p1 = particles.NNP_list.first(); 
	     !particles.NNP_list.isEnd(p1); 
	     p1 = particles.NNP_list.next(p1)) {
			
	    /// <ul><li> get a particle
	    Particle *prtl_dest = particles.NNP_list.retrieve(p1);
				
	    /// <li> calculate distance (origin<-> neighbor)
	    dstc = vv_distance(prtl_org->R, prtl_dest->R);
	    
	    eij[X] = (prtl_org->R[X] - prtl_dest->R[X])/(dstc + 1.e-30);
	    eij[Y] = (prtl_org->R[Y] - prtl_dest->R[Y])/(dstc + 1.e-30);
	    
	    /// <li> calculate weight function for given distance (w=0, if dist>supportlengtg) an summ it up </ul> 
	    reciprocV += w(&weight_function, dstc);
	    sumdw[X] += eij[X]*F(&weight_function, dstc);
	    sumdw[Y] += eij[Y]*F(&weight_function, dstc);	    
	}
	/// <li> calculate volume as reciprocal value of weight function
	reciprocV = 1.0/reciprocV;

	/// <li> save volume and mass in the respective particle list node (whih is each a Particle object with all the particle properties) 
	prtl_org->V = reciprocV;
	prtl_org->m = prtl_org->rho*reciprocV;
			
	/// <li> clear the NNP_list</ul> </ul>
	particles.NNP_list.clear();
    }
}
