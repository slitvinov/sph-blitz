#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "boundary.h"
#include "err.h"
#include "force.h"
#include "glbfunc.h"
#include "initiation.h"
#include "interaction.h"
#include "list.h"
#include "macro.h"
#include "material.h"
#include "particle.h"
#include "quinticspline.h"
#include "vv.h"
#include "hydrodynamics.h"

enum { X, Y };

Hydrodynamics::Hydrodynamics(struct Initiation *ini)
{
    int k, m;
    int l, n;
    char Key_word[FILENAME_MAX];
    double sound;
    FILE *f;
    struct Material *mtl;
    struct Force *force;

    interaction_list = list_ini();
    number_of_materials = ini->number_of_materials;
    gravity[X] = ini->gravity[X];
    gravity[Y] = ini->gravity[Y];
    smoothinglength = ini->smoothinglength;
    delta = ini->delta;
    delta2 = ini->delta * ini->delta;
    delta3 = ini->delta * ini->delta * ini->delta;
    materials =
	(struct Material *) malloc(number_of_materials *
				   sizeof(*materials));
    forces =
	(struct Force **) malloc(number_of_materials * sizeof(*force));
    for (k = 0; k < number_of_materials; k++)
	forces[k] =
	    (struct Force *) malloc(number_of_materials *
				    sizeof(*forces[k]));

    f = fopen(ini->inputfile, "r");
    if (!f)
	ABORT(("can't open '%s'", ini->inputfile));
    else
	printf("read the propeties of materials and forces\n");
    while (fscanf(f, "%s", Key_word) == 1) {
	if (!strcmp(Key_word, "MATERIALS"))
	    for (k = 0; k < number_of_materials; k++) {
		mtl = &materials[k];
		mtl->number = k;
		if (fscanf
		    (f, "%s %d", mtl->material_name, &mtl->material_type)
		    != 2)
		    ABORT(("can't read material from '%s'",
			   ini->inputfile));
		if (fscanf
		    (f, "%lf %lf %lf %lf %lf", &mtl->eta, &mtl->zeta,
		     &mtl->gamma, &mtl->rho0, &mtl->a0) != 5)
		    ABORT(("can't read materal parameters from '%s'",
			   ini->inputfile));
		Set_nu(mtl);
	    }
	if (!strcmp(Key_word, "FORCES"))
	    for (l = 0; l < number_of_materials; l++)
		for (n = 0; n < number_of_materials; n++) {
		    if (fscanf(f, "%d %d", &k, &m) != 2)
			ABORT(("can't read materal from '%s'",
			       ini->inputfile));
		    force = &forces[k][m];
		    if (fscanf(f, "%lf %lf %lf %lf",
			       &force->epsilon, &force->sigma,
			       &force->shear_slip, &force->bulk_slip) != 4)
			ABORT(("can't read force from '%s'",
			       ini->inputfile));
		}
    }
    fclose(f);
    viscosity_max = 0.0;
    surface_max = 0.0;
    for (k = 0; k < number_of_materials; k++) {
	viscosity_max = AMAX1(viscosity_max, materials[k].nu);
	for (l = 0; l < number_of_materials; l++) {
	    surface_max = AMAX1(surface_max, forces[k][l].sigma);
	}
    }
    dt_g_vis =
	AMIN1(sqrt(delta / vv_abs(gravity)), 0.5 * delta2 / viscosity_max);
    dt_surf = 0.4 * sqrt(delta3 / surface_max);
    sound = AMAX1(vv_abs(ini->gravity), viscosity_max);
    sound = AMAX1(surface_max, sound);
    for (k = 0; k < number_of_materials; k++)
	Set_b0(&materials[k], sound);
    particle_list = list_ini();
}

void
UpdatePair(struct Hydrodynamics *q, struct QuinticSpline *weight_function)
{
    struct ListNode *
	p;
    struct Interaction *
	pair;

    ILOOP_P(pair, q->interaction_list) {
	RenewInteraction(pair, weight_function);
    }
}

void
UpdatePhaseGradient(struct Hydrodynamics *q, struct Boundary *boundary)
{
    struct ListNode *
	p;
    struct Interaction *
	pair;

    Zero_PhaseGradient(q, boundary);
    ILOOP_P(pair, q->interaction_list) {
	SummationPhaseGradient(pair);
    }
}

void
UpdateDensity(struct Hydrodynamics *q)
{
    struct ListNode *
	p;
    struct Interaction *
	pair;

    Zero_density(q);
    ILOOP_P(pair, q->interaction_list) {
	SummationDensity(pair);
    }
    UpdateState(q);
}

void
 UpdateChangeRate(struct Hydrodynamics *q)
{
    struct ListNode *
	p;
    struct Interaction *
	pair;

    ZeroChangeRate(q);
    ILOOP_P(pair, q->interaction_list) {
	UpdateForces(pair);
    }
    AddGravity(q);
}

void
UpdateRandom(struct Hydrodynamics *q, double sqrtdt)
{
    struct ListNode *
	p;
    struct Interaction *
	pair;

    Zero_Random(q);
    ILOOP_P(pair, q->interaction_list) {
	RandomForces(pair, sqrtdt);
    }
}

void
ZeroChangeRate(struct Hydrodynamics *q)
{
    struct ListNode *
	p;
    struct Particle *
	prtl;

    LOOP_P(prtl, q->particle_list) {
	prtl->dedt = 0.0;
	prtl->drhodt = 0.0;
	prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
	prtl->_dU[X] = prtl->_dU[Y] = 0.0;
    }
}

void
Zero_density(struct Hydrodynamics *q)
{
    struct ListNode *
	p;
    Particle *
	prtl;

    LOOP_P(prtl, q->particle_list) {
	prtl->rho = 0.0;
    }
}

void Zero_PhaseGradient(struct Hydrodynamics *q, Boundary * boundary)
{
    struct ListNode *
	p;
    struct Particle *
	prtl;

    LOOP_P(prtl, q->particle_list) {
	prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
    LOOP_P(prtl, boundary->b) {
	prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
}

void
Zero_Random(Hydrodynamics *q)
{
    struct ListNode *
	p;
    struct Particle *
	prtl;

    LOOP_P(prtl, q->particle_list) {
	prtl->_dU[X] = prtl->_dU[Y] = 0.0;
    }
}

void
AddGravity(struct Hydrodynamics *q)
{
    struct ListNode *
	p;
    struct Particle *
	prtl;

    LOOP_P(prtl, q->particle_list) {
	prtl->dUdt[X] += q->gravity[X];
	prtl->dUdt[Y] += q->gravity[Y];
    }
}

void
UpdateState(struct Hydrodynamics *q)
{
    struct ListNode *
	p;
    struct Particle *
	prtl;

    LOOP_P(prtl, q->particle_list) {
	prtl->p = get_p(prtl->mtl, prtl->rho);
    }
}

void
UpdatePahseMatrix(struct Hydrodynamics *q, Boundary * boundary)
{
    struct ListNode *
	p;
    struct Particle *
	prtl;
    int
     i,
	j, number_of_materials;

    number_of_materials = q->number_of_materials;
    LOOP_P(prtl, q->particle_list) {
	for (i = 0; i < number_of_materials; i++)
	    for (j = 0; j < number_of_materials; j++) {
		if (i != j)
		    prtl->phi[i][j] = prtl->phi[i][j];
	    }
    }
    LOOP_P(prtl, boundary->b) {
	for (i = 0; i < number_of_materials; i++)
	    for (j = 0; j < number_of_materials; j++) {
		if (i != j)
		    prtl->phi[i][j] = prtl->phi[i][j];
	    }
    }
}

void
UpdateSurfaceStress(struct Hydrodynamics *q, Boundary * boundary)
{
    double
     epsilon = 1.0e-30;
    double
     interm0,
	interm1,
	interm2;
    struct Particle *
	prtl;
    struct ListNode *
	p;

    LOOP_P(prtl, q->particle_list) {
	interm0 = 1.0 / (vv_abs(prtl->del_phi) + epsilon);
	interm1 = 0.5 * vv_sqdiff(prtl->del_phi);
	interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
	prtl->del_phi[0] = interm1 * interm0;
	prtl->del_phi[1] = interm2 * interm0;
    }
    LOOP_P(prtl, boundary->b) {
	interm0 = vv_abs(prtl->del_phi) + epsilon;
	interm1 = 0.5 * vv_sqdiff(prtl->del_phi);
	interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
	prtl->del_phi[0] = interm1 / interm0;
	prtl->del_phi[1] = interm2 / interm0;
    }
}

double
GetTimestep(struct Hydrodynamics *q)
{
    struct Particle *
	prtl;
    struct ListNode *
	p;
    double
     Cs_max = 0.0, V_max = 0.0, rho_min = 1.0e30, rho_max = 1.0;
    double
     dt;

    LOOP_P(prtl, q->particle_list) {
	Cs_max = AMAX1(Cs_max, prtl->Cs);
	V_max = AMAX1(V_max, vv_abs(prtl->U));
	rho_min = AMIN1(rho_min, prtl->rho);
	rho_max = AMAX1(rho_max, prtl->rho);
    }
    dt = AMIN1(sqrt(0.5 * (rho_min + rho_max)) * q->dt_surf, q->dt_g_vis);
    return 0.25 * AMIN1(dt, q->delta / (Cs_max + V_max));
}

void
Predictor_summation(struct Hydrodynamics *q, double dt)
{
    struct ListNode *
	p;
    struct Particle *
	prtl;

    LOOP_P(prtl, q->particle_list) {
	prtl->R_I[X] = prtl->R[X];
	prtl->R_I[Y] = prtl->R[Y];
	prtl->U[X] += prtl->_dU[X];
	prtl->U[Y] += prtl->_dU[Y];
	prtl->U_I[X] = prtl->U[X];
	prtl->U_I[Y] = prtl->U[Y];
	prtl->R[X] = prtl->R[X] + prtl->U[X] * dt;
	prtl->R[Y] = prtl->R[Y] + prtl->U[Y] * dt;
	prtl->U[X] = prtl->U[X] + prtl->dUdt[X] * dt;
	prtl->U[Y] = prtl->U[Y] + prtl->dUdt[Y] * dt;
	prtl->R[X] = (prtl->R[X] + prtl->R_I[X]) * 0.5;
	prtl->R[Y] = (prtl->R[Y] + prtl->R_I[Y]) * 0.5;
	prtl->U[X] = (prtl->U[X] + prtl->U_I[X]) * 0.5;
	prtl->U[Y] = (prtl->U[Y] + prtl->U_I[Y]) * 0.5;
    }
}

void
Corrector_summation(struct Hydrodynamics *q, double dt)
{
    struct ListNode *
	p;
    struct Particle *
	prtl;

    LOOP_P(prtl, q->particle_list) {
	prtl->U[X] += prtl->_dU[X];
	prtl->U[Y] += prtl->_dU[Y];
	prtl->R[X] = prtl->R_I[X] + prtl->U[X] * dt;
	prtl->R[Y] = prtl->R_I[Y] + prtl->U[Y] * dt;
	prtl->U[X] = prtl->U_I[X] + prtl->dUdt[X] * dt;
	prtl->U[Y] = prtl->U_I[Y] + prtl->dUdt[Y] * dt;
    }
}

void
RandomEffects(struct Hydrodynamics *q)
{
    struct ListNode *
	p;
    struct Particle *
	prtl;

    LOOP_P(prtl, q->particle_list) {
	prtl->U[X] = prtl->U[X] + prtl->_dU[X];
	prtl->U[Y] = prtl->U[Y] + prtl->_dU[Y];
    }
}

Hydrodynamics::~Hydrodynamics()
{
    int i;

    for (i = 0; i < number_of_materials; i++)
	free(forces[i]);
    free(forces);
    free(materials);
    list_fin(interaction_list);
    list_fin(particle_list);
}
