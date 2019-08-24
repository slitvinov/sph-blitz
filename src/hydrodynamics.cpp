#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
class Hydrodynamics;
class ParticleManager;
#include "err.h"
#include "vv.h"
#include "glbfunc.h"
#include "quinticspline.h"
#include "particle.h"
#include "dllist.h"
#include "list.h"
#include "ilist.h"
#include "wiener.h"
#include "initiation.h"
#include "material.h"
#include "force.h"
#include "interaction.h"
#include "particlemanager.h"
#include "boundary.h"
#include "hydrodynamics.h"
#include "macro.h"

#define LIST ListNode
#define ILIST IListNode

using namespace std;
enum {X, Y};
Hydrodynamics::Hydrodynamics(Initiation *ini)
{
    int k, m;
    int l, n;
    char Key_word[FILENAME_MAX];
    double sound;
    number_of_materials = ini->number_of_materials;
    gravity[X] = ini->gravity[X];
    gravity[Y] = ini->gravity[Y];
    smoothinglength = ini->smoothinglength;
    delta = ini->delta;
    delta2 = ini->delta*ini->delta;
    delta3 = ini->delta*ini->delta*ini->delta;
    materials = new Material[number_of_materials];
    forces = new Force*[number_of_materials];
    for(k = 0; k < number_of_materials; k++)
	forces[k] = new Force[number_of_materials];
    ifstream fin(ini->inputfile, ios::in);
    if (!fin)
	ABORT(("can't open '%s'", ini->inputfile));
    else
	printf("Material: read the propeties of materials and interaction forces\n");
    while(!fin.eof()) {
	fin>>Key_word;
	if(!strcmp(Key_word, "MATERIALS"))
	    for(k = 0; k < number_of_materials; k++) {
		materials[k].number = k;
		fin>>materials[k].material_name>>materials[k].material_type;
		fin>>materials[k].eta>>materials[k].zeta
		   >>materials[k].gamma>>materials[k].rho0>>materials[k].a0;
		Set_nu(&materials[k]);
	    }
	if(!strcmp(Key_word, "FORCES"))
	    for(l = 0; l < number_of_materials; l++)
		for(n = 0; n < number_of_materials; n++) {
		    fin>>k>>m;
		    fin>>forces[k][m].epsilon>>forces[k][m].sigma
		       >>forces[k][m].shear_slip>>forces[k][m].bulk_slip;
		}
    }
    fin.close();
    viscosity_max = 0.0; surface_max = 0.0;
    for(k = 0; k < number_of_materials; k++) {
	viscosity_max = AMAX1(viscosity_max, materials[k].nu);
	for(l = 0; l < number_of_materials; l++) {
	    surface_max = AMAX1(surface_max, forces[k][l].sigma);
	}
    }
    dt_g_vis = AMIN1(sqrt(delta/vv_abs(gravity)), 0.5*delta2/viscosity_max);
    dt_surf = 0.4*sqrt(delta3/surface_max);
    sound = AMAX1(vv_abs(ini->gravity), viscosity_max);
    sound = AMAX1(surface_max, sound);
    for(k = 0; k < number_of_materials; k++)
	Set_b0(&materials[k], sound);
    particle_list = list_ini();
}
void Hydrodynamics::BuildPair(ParticleManager *particles, QuinticSpline *weight_function)
{
    particles->BuildInteraction(&interaction_list, particle_list, forces, weight_function);
}
void Hydrodynamics::UpdatePair(QuinticSpline *weight_function)
{
    ILIST *p;
    Interaction *pair;
    ILOOP(pair, interaction_list) {
	pair->RenewInteraction(weight_function);
    }
}
void Hydrodynamics::UpdatePhaseGradient(Boundary *boundary)
{
    ILIST *p;
    Interaction *pair;
    Zero_PhaseGradient(boundary);
    ILOOP(pair, interaction_list) {
	pair->SummationPhaseGradient();
    }
}
void Hydrodynamics::UpdateDensity()
{
    ILIST *p;
    Interaction *pair;
    Zero_density();
    for (p = interaction_list.first();
	 !interaction_list.isEnd(p);
	 p = interaction_list.next(p)) {
	pair = interaction_list.retrieve(p);
	pair->SummationDensity();
    }
    UpdateState();
}
void Hydrodynamics::UpdateChangeRate(ParticleManager *particles, QuinticSpline *weight_function)
{
    ILIST *p;
    Interaction *pair;
    ZeroChangeRate();
    particles->BuildInteraction(&interaction_list, particle_list, forces, weight_function);
    ILOOP(pair, interaction_list) {
	pair->UpdateForces();
    }
    AddGravity();
}
void Hydrodynamics::UpdateChangeRate()
{
    ILIST *p;
    Interaction *pair;
    ZeroChangeRate();
    ILOOP(pair, interaction_list) {
	pair->UpdateForces();
    }
    AddGravity();
}
void Hydrodynamics::UpdateRandom(double sqrtdt)
{
    ILIST *p;
    Interaction *pair;
    Zero_Random();
    ILOOP(pair, interaction_list) {
	pair->RandomForces(sqrtdt);
    }
}
void Hydrodynamics::ZeroChangeRate()
{
    LIST *p;
    Particle *prtl;
    LOOP(prtl, *particle_list) {
	prtl->dedt = 0.0;
	prtl->drhodt = 0.0;
	prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
	prtl->_dU[X] = prtl->_dU[Y] = 0.0;
    }
}
void Hydrodynamics::Zero_density()
{
    LIST *p;
    Particle *prtl;
    LOOP(prtl, *particle_list) {
	prtl->rho = 0.0;
    }
}
void Hydrodynamics::Zero_PhaseGradient(Boundary *boundary)
{
    LIST *p;
    Particle *prtl;
    LOOP(prtl, *particle_list) {
	prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
    LOOP(prtl, *boundary->b) {
	prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
}
void Hydrodynamics::Zero_Random()
{
    LIST *p;
    Particle *prtl;
    LOOP(prtl, *particle_list) {
	prtl->_dU[X] = prtl->_dU[Y] = 0.0;
    }
}
void Hydrodynamics::AddGravity()
{
    LIST *p;
    Particle *prtl;
    LOOP(prtl, *particle_list) {
	prtl->dUdt[X] += gravity[X];
	prtl->dUdt[Y] += gravity[Y];
    }
}
void Hydrodynamics::UpdateState()
{
    LIST *p;
    Particle *prtl;
    LOOP(prtl, *particle_list) {
	prtl->p = get_p(prtl->mtl, prtl->rho);
    }
}
void Hydrodynamics::UpdatePahseMatrix(Boundary *boundary)
{
    LIST *p;
    Particle *prtl;
    int i, j;
    LOOP(prtl, *particle_list) {
	for(i = 0; i < number_of_materials; i++)
	    for(j = 0; j < number_of_materials; j++) {
		if( i != j) prtl->phi[i][j] = prtl->phi[i][j];
	    }
    }
    LOOP(prtl, *boundary->b) {
	for(i = 0; i < number_of_materials; i++)
	    for(j = 0; j < number_of_materials; j++) {
		if( i != j) prtl->phi[i][j] = prtl->phi[i][j];
	    }
    }
}
void Hydrodynamics::UpdateSurfaceStress(Boundary *boundary)
{
    double epsilon =1.0e-30;
    double interm0, interm1, interm2;
    Particle *prtl;
    LIST *p;
    LOOP(prtl, *particle_list) {
	interm0 = 1.0/(vv_abs(prtl->del_phi) + epsilon);
	interm1 = 0.5*vv_sqdiff(prtl->del_phi);
	interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
	prtl->del_phi[0] = interm1*interm0;
	prtl->del_phi[1] = interm2*interm0;
    }
    LOOP(prtl, *boundary->b) {
	interm0 = vv_abs(prtl->del_phi) + epsilon;
	interm1 = 0.5*vv_sqdiff(prtl->del_phi);
	interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
	prtl->del_phi[0] = interm1/interm0;
	prtl->del_phi[1] = interm2/interm0;
    }
}
double Hydrodynamics::GetTimestep()
{
    Particle *prtl;
    LIST *p;
    double Cs_max = 0.0, V_max = 0.0, rho_min = 1.0e30, rho_max = 1.0;
    double dt;
    LOOP(prtl, *particle_list) {
	Cs_max = AMAX1(Cs_max, prtl->Cs);
	V_max = AMAX1(V_max, vv_abs(prtl->U));
	rho_min = AMIN1(rho_min, prtl->rho);
	rho_max = AMAX1(rho_max, prtl->rho);
    }
    dt = AMIN1(sqrt(0.5*(rho_min + rho_max))*dt_surf, dt_g_vis);
    return  0.25*AMIN1(dt, delta/(Cs_max + V_max));
}
void Hydrodynamics::Predictor_summation(double dt)
{
    LIST *p;
    Particle *prtl;
    LOOP(prtl, *particle_list) {
	prtl->R_I[X] = prtl->R[X];
	prtl->R_I[Y] = prtl->R[Y];
	prtl->U[X] += prtl->_dU[X];
	prtl->U[Y] += prtl->_dU[Y];
	prtl->U_I[X] = prtl->U[X];
	prtl->U_I[Y] = prtl->U[Y];
	prtl->R[X] = prtl->R[X] + prtl->U[X]*dt;
	prtl->R[Y] = prtl->R[Y] + prtl->U[Y]*dt;
	prtl->U[X] = prtl->U[X] + prtl->dUdt[X]*dt;
	prtl->U[Y] = prtl->U[Y] + prtl->dUdt[Y]*dt;
	prtl->R[X] = (prtl->R[X] + prtl->R_I[X])*0.5;
	prtl->R[Y] = (prtl->R[Y] + prtl->R_I[Y])*0.5;
	prtl->U[X] = (prtl->U[X] + prtl->U_I[X])*0.5;
	prtl->U[Y] = (prtl->U[Y] + prtl->U_I[Y])*0.5;
    }
}
void Hydrodynamics::Corrector_summation(double dt)
{
    LIST *p;
    Particle *prtl;    
    LOOP(prtl, *particle_list) {
	prtl->U[X] += prtl->_dU[X];
	prtl->U[Y] += prtl->_dU[Y];
	prtl->R[X] = prtl->R_I[X] + prtl->U[X]*dt;
	prtl->R[Y] = prtl->R_I[Y] + prtl->U[Y]*dt;    
	prtl->U[X] = prtl->U_I[X] + prtl->dUdt[X]*dt;
	prtl->U[Y] = prtl->U_I[Y] + prtl->dUdt[Y]*dt;
    }
}
void Hydrodynamics::RandomEffects()
{
    LIST *p;
    Particle *prtl;
    LOOP(prtl, *particle_list) {
	prtl->U[X] = prtl->U[X] + prtl->_dU[X];
	prtl->U[Y] = prtl->U[Y] + prtl->_dU[Y];    
    }
}

Hydrodynamics::~Hydrodynamics()
{
    list_fin(particle_list);
}
