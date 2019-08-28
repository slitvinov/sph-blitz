#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "vv.h"
#include "glbfunc.h"
#include "quinticspline.h"
#include "wiener.h"
#include "ini.h"
#include "particle.h"
#include "material.h"
#include "force.h"
#include "err.h"
#include "pair.h"
enum { X, Y };
static double k_bltz = 1.380662e-023 / 0.02 / 0.02 / 0.02;
double pair_art_vis;
double pair_delta;
struct Pair *
pair_ini(struct Particle *prtl_org, struct Particle *prtl_dest,
		struct Force **forces,
		struct QuinticSpline *weight_function, double dstc)
{
    struct Pair *q;
    struct Particle *Org, *Dest;
    double etai, etaj, rij, zetai, zetaj;
    int noi, noj;
    struct Force **frc_ij;

    q = malloc(sizeof(*q));
    if (q == NULL)
	ABORT(("can't allocate"));

    q->Org = Org = prtl_org;
    q->Dest = Dest = prtl_dest;
    q->noi = noi = Org->mtl->number;
    q->noj = noj = Dest->mtl->number;
    q->frc_ij = frc_ij = forces;
    q->mi = Org->m;
    q->mj = Dest->m;
    q->rmi = 1.0 / q->mi;
    q->rmj = 1.0 / q->mj;
    q->etai = etai = Org->eta;
    q->etaj = etaj = Dest->eta;
    q->zetai = zetai = Org->zeta;
    q->zetaj = zetaj = Dest->zeta;
    q->rij = rij = dstc;
    q->rrij = 1.0 / (rij + 1.0e-30);
    q->eij[X] = (Org->R[X] - Dest->R[X]) * q->rrij;
    q->eij[Y] = (Org->R[Y] - Dest->R[Y]) * q->rrij;
    q->Wij = w(weight_function, rij);
    q->Fij = F(weight_function, rij) * q->rrij;
    q->shear_rij =
	2.0 * etai * etaj * rij / (etai *
				   (rij +
				    2.0 * frc_ij[noj][noi].shear_slip)
				   + etaj * (rij +
					     2.0 *
					     frc_ij[noi][noj].shear_slip) +
				   1.0e-30);
    q->bulk_rij =
	2.0 * zetai * zetaj * rij / (zetai *
				     (rij +
				      2.0 * frc_ij[noj][noi].bulk_slip)
				     + zetaj * (rij +
						2.0 *
						frc_ij[noi][noj].bulk_slip)
				     + 1.0e-30);
    return q;
}

void
RenewPair(struct Pair *q,
		 struct QuinticSpline *weight_function)
{
    struct Particle *Org, *Dest;
    double *eij;
    double rij, rrij;
    double etai, etaj, zetai, zetaj;
    struct Force **frc_ij;
    int noi, noj;

    Org = q->Org;
    Dest = q->Dest;
    eij = q->eij;
    etai = q->etai;
    etaj = q->etaj;
    zetai = q->zetai;
    zetaj = q->zetaj;
    frc_ij = q->frc_ij;
    noi = q->noi;
    noj = q->noj;

    rij = q->rij = vv_distance(q->Org->R, q->Dest->R);
    rrij = q->rrij = 1.0 / (q->rij + 1.0e-30);

    eij[X] = (Org->R[X] - Dest->R[X]) * rrij;
    eij[Y] = (Org->R[Y] - Dest->R[Y]) * rrij;
    q->Wij = w(weight_function, rij);
    q->Fij = F(weight_function, rij) * rrij;
    q->shear_rij =
	2.0 * etai * etaj * q->rij / (etai *
				      (rij +
				       2.0 * frc_ij[noj][noi].shear_slip)
				      + etaj * (rij + 2.0 * frc_ij[noi]
						[noj].shear_slip) +
				      1.0e-30);
    q->bulk_rij =
	2.0 * zetai * zetaj * rij / (zetai *
				     (rij +
				      2.0 * frc_ij[noj][noi].bulk_slip)
				     + zetaj * (rij +
						2.0 *
						frc_ij[noi][noj].bulk_slip)
				     + 1.0e-30);
}

void
SummationDensity(struct Pair *q)
{
    struct Particle *Org, *Dest;
    double Wij;
    double mi, mj;

    Org = q->Org;
    Dest = q->Dest;
    Wij = q->Wij;
    mi = q->mi;
    mj = q->mj;

    Org->rho += mi * Wij;
    if (Org->ID != Dest->ID)
	Dest->rho += mj * Wij;
}

void
SummationPhaseGradient(struct Pair *q)
{
    struct Particle *Org, *Dest;
    double mi, mj;
    double c;
    double Vi, rVi, Vj, rVj;
    double dphi[2];
    double Fij;
    double rij;
    struct Force **frc_ij;
    int noi;
    int noj;
    double *eij;

    Org = q->Org;
    Dest = q->Dest;
    mi = q->mi;
    mj = q->mj;
    Fij = q->Fij;
    rij = q->rij;
    frc_ij = q->frc_ij;
    noi = q->noi;
    noj = q->noj;
    eij = q->eij;

    Vi = mi / Org->rho;
    Vj = mj / Dest->rho;
    rVi = 1.0 / Vi;
    rVj = 1.0 / Vj;
    double Vi2 = Vi * Vi, Vj2 = Vj * Vj;

    c = Fij * rij * frc_ij[noi][noj].sigma;
    dphi[X] = eij[X] * c;
    dphi[Y] = eij[Y] * c;
    Org->del_phi[X] += dphi[X] * rVi * Vj2;
    Org->del_phi[Y] += dphi[Y] * rVi * Vj2;
    Dest->del_phi[X] -= dphi[X] * rVj * Vi2;
    Dest->del_phi[Y] -= dphi[Y] * rVj * Vi2;
}

void
UpdateForces(struct Pair *q)
{
    struct Particle *Org, *Dest;
    double Wij;
    double mi, mj;
    double c;
    double Vi, rVi, Vj, rVj;
    double Fij;
    double rij;
    double *eij;
    double pi, rhoi, pj, rhoj, Uijdoteij, dx, dy;
    double Ui[2], Uj[2], Uij[2];
    double shear_rij;
    double bulk_rij;
    double rmi, rmj;

    Org = q->Org;
    Dest = q->Dest;
    Wij = q->Wij;
    mi = q->mi;
    mj = q->mj;
    Fij = q->Fij;
    rij = q->rij;
    eij = q->eij;
    shear_rij = q->shear_rij;
    bulk_rij = q->bulk_rij;
    rmi = q->rmi;
    rmj = q->rmj;

    rhoi = Org->rho;
    rhoj = Dest->rho;
    Vi = mi / rhoi;
    Vj = mj / rhoj;
    rVi = 1.0 / Vi;
    rVj = 1.0 / Vj;
    pi = Org->p;
    pj = Dest->p;
    Ui[X] = Org->U[X];
    Ui[Y] = Org->U[Y];
    Uj[X] = Dest->U[X];
    Uj[Y] = Dest->U[Y];
    Uij[X] = Ui[X] - Uj[X];
    Uij[Y] = Ui[Y] - Uj[Y];
    Uijdoteij = Uij[X] * eij[X] + Uij[Y] * eij[Y];
    double dPdti[2], dUi[2];
    double drhodti;
    double Vi2 = Vi * Vi, Vj2 = Vj * Vj;
    double theta, Csi, Csj, NR_vis;
    double delta = pair_delta;
    double art_vis = pair_art_vis;

    Csi = Org->Cs;
    Csj = Dest->Cs;
    theta = Uijdoteij * rij * delta / (rij * rij + 0.01 * delta * delta);
    NR_vis =
	Uijdoteij >
	0.0 ? 0.0 : art_vis * theta * (rhoi * Csi * mj +
				       rhoj * Csj * mi) / (mi + mj);
    c = theta * Wij * art_vis / (rhoi + rhoj);
    dUi[X] = -eij[X] * c;
    dUi[Y] = -eij[Y] * c;
    dx = Ui[X] * Vi2 - Uj[X] * Vj2;
    dy = Ui[Y] * Vi2 - Uj[Y] * Vj2;
    drhodti = -Fij * rij * (dx * eij[X] + dy * eij[Y]);
    dPdti[X] = eij[X] * Fij * rij * (pi * Vi2 + pj * Vj2)
	- ((Uij[X] - eij[X] * Uijdoteij) * shear_rij +
	   eij[X] * (Uijdoteij * 2.0 * bulk_rij + NR_vis))
	* Fij * (Vi2 + Vj2);
    dPdti[Y] = eij[Y] * Fij * rij * (pi * Vi2 + pj * Vj2)
	- ((Uij[Y] - eij[Y] * Uijdoteij) * shear_rij +
	   eij[Y] * (Uijdoteij * 2.0 * bulk_rij + NR_vis))
	* Fij * (Vi2 + Vj2);
    double Surfi[2], Surfj[2], SurfaceForcei[2], SurfaceForcej[2];

    Surfi[X] = Org->del_phi[X];
    Surfi[Y] = Org->del_phi[Y];
    Surfj[X] = Dest->del_phi[X];
    Surfj[Y] = Dest->del_phi[Y];
    SurfaceForcei[X] = Surfi[X] * eij[X] + Surfi[Y] * eij[Y];
    SurfaceForcei[Y] = Surfi[Y] * eij[X] - Surfi[X] * eij[Y];
    SurfaceForcej[X] = Surfj[X] * eij[X] + Surfj[Y] * eij[Y];
    SurfaceForcej[Y] = Surfj[Y] * eij[X] - Surfj[X] * eij[Y];
    dPdti[X] +=
	(SurfaceForcei[X] * Vi2 + SurfaceForcej[X] * Vj2) * rij * Fij;
    dPdti[Y] +=
	(SurfaceForcei[Y] * Vi2 + SurfaceForcej[Y] * Vj2) * rij * Fij;
    Org->_dU[X] += dUi[X] * mi;
    Org->_dU[Y] += dUi[Y] * mi;
    Dest->_dU[X] -= dUi[X] * mj;
    Dest->_dU[Y] -= dUi[Y] * mj;
    Org->drhodt += drhodti * rhoi * rVi;
    Dest->drhodt += drhodti * rhoj * rVj;
    Org->dUdt[X] += dPdti[X] * rmi;
    Org->dUdt[Y] += dPdti[Y] * rmi;
    Dest->dUdt[X] -= dPdti[X] * rmj;
    Dest->dUdt[Y] -= dPdti[Y] * rmj;
}

void
RandomForces(struct Pair *q, double sqrtdt)
{
    double Vi, Vj;
    double Ti, Tj;
    double v_eij[2];
    double Random_p, Random_v;
    struct Particle *Org, *Dest;
    double mi, mj;
    double shear_rij;
    double Fij;
    double *eij;
    double bulk_rij;
    double rmi, rmj;

    rmi = q->rmi;
    rmj = q->rmj;
    bulk_rij = q->bulk_rij;
    eij = q->eij;
    shear_rij = q->shear_rij;
    Fij = q->Fij;
    mi = q->mi;
    mj = q->mj;
    Org = q->Org;
    Dest = q->Dest;
    Ti = Org->T;
    Tj = Dest->T;
    if (Ti == 0 && Tj == 0)
	return;
    Vi = mi / Org->rho;
    Vj = mj / Dest->rho;
    wiener_gaussian(&Random_p, &Random_v);
    Random_p *= sqrtdt;
    Random_v *= sqrtdt;
    double _dUi[2];
    double Vi2 = Vi * Vi, Vj2 = Vj * Vj;

    v_eij[X] = v_eij[Y] = 0;
    _dUi[X] =
	v_eij[X] * Random_p * sqrt(16.0 * k_bltz * shear_rij * Ti * Tj /
				   (Ti + Tj) * (Vi2 + Vj2) * Fij) +
	eij[X] * Random_v * sqrt(16.0 * k_bltz * bulk_rij * Ti * Tj /
				 (Ti + Tj) * (Vi2 + Vj2) * Fij);
    _dUi[Y] =
	v_eij[Y] * Random_p * sqrt(16.0 * k_bltz * shear_rij * Ti * Tj /
				   (Ti + Tj) * (Vi2 + Vj2) * Fij) +
	eij[Y] * Random_v * sqrt(16.0 * k_bltz * bulk_rij * Ti * Tj /
				 (Ti + Tj) * (Vi2 + Vj2) * Fij);
    if (Dest->bd_type == 1) {
	Org->_dU[X] = Org->_dU[X] + _dUi[X] * rmi * 0.5;
	Org->_dU[Y] = Org->_dU[Y] + _dUi[Y] * rmi * 0.5;
	Dest->rl_prtl->_dU[X] =
	    Dest->rl_prtl->_dU[X] - _dUi[X] * rmj * 0.5;
	Dest->rl_prtl->_dU[Y] =
	    Dest->rl_prtl->_dU[Y] - _dUi[Y] * rmj * 0.5;
    } else {
	Org->_dU[X] = Org->_dU[X] + _dUi[X] * rmi;
	Org->_dU[Y] = Org->_dU[Y] + _dUi[Y] * rmi;
	Dest->_dU[X] = Dest->_dU[X] - _dUi[X] * rmj;
	Dest->_dU[Y] = Dest->_dU[Y] - _dUi[Y] * rmj;
    }
}

int
pair_fin(struct Pair *q)
{
    free(q);
    return 0;
}
