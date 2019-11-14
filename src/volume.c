#include "particle.h"
#include "vv.h"
#include "list.h"
#include "kernel.h"
#include "manager.h"
#include "volume.h"
#include "macro.h"

void
VolumeMass(struct List *particle_list, struct Manager *manager,
           struct Kernel *kernel)
{
    double reciprocV;
    double dstc;
    struct ListNode *p, *p1;
    struct Particle *prtl_org, *prtl_dest;

    LOOP_P(prtl_org, particle_list) {
        manager_build_nnp(manager, prtl_org->R);
        reciprocV = 0.0;
        LOOP1_P(prtl_dest, manager->NNP_list) {
            dstc = vv_distance(prtl_org->R, prtl_dest->R);
            reciprocV += w(kernel, dstc);
        }
        reciprocV = 1.0 / reciprocV;
        prtl_org->V = reciprocV;
        prtl_org->m = prtl_org->rho * reciprocV;
        list_clear(manager->NNP_list);
    }
}
