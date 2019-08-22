#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstring>

#include <cstdio>
#include <cstdlib>

class Hydrodynamics;
class ParticleManager;
#include "vv.h"
#include "glbfunc.h"
#include "quinticspline.h"
#include "dllist.h"
#include "wiener.h"
#include "initiation.h"
#include "material.h"
#include "force.h"
#include "interaction.h"
#include "particlemanager.h"
#include "particle.h"
#include "boundary.h"
#include "hydrodynamics.h"

using namespace std;
enum {X, Y};

Hydrodynamics::Hydrodynamics(ParticleManager &particles, Initiation &ini)
{
    int k, m;
    int l, n;
    char Key_word[FILENAME_MAX];
    char inputfile[FILENAME_MAX];
    double sound;

    number_of_materials = ini.number_of_materials;
    gravity[X] = ini.g_force[X];
    gravity[Y] = ini.g_force[Y];
    smoothinglength = ini.smoothinglength;
    delta = ini.delta; delta2 = delta*delta; delta3 = delta2*delta;
    materials = new Material[number_of_materials];
    forces = new Force*[number_of_materials];
    for(k = 0; k < number_of_materials; k++) forces[k] = new Force[number_of_materials];

    strcpy(inputfile, ini.inputfile);
    ifstream fin(inputfile, ios::in);
    if (!fin) {
	cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
	std::cout << __FILE__ << ':' << __LINE__ << std::endl;
	exit(1);
    }
    else cout<<"\nMaterial: read the propeties of materials and interaction forces \n";
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
    sound = AMAX1(vv_abs(ini.g_force), viscosity_max);
    sound = AMAX1(surface_max, sound);
    for(k = 0; k < number_of_materials; k++)
	Set_b0(&materials[k], sound);
}

void Hydrodynamics::BuildPair(ParticleManager &particles, QuinticSpline &weight_function)
{
    particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);
}

void Hydrodynamics::UpdatePair(QuinticSpline &weight_function)
{
    LlistNode<Interaction> *p;
    Interaction *pair;
    for (p = interaction_list.first();
	 !interaction_list.isEnd(p);
	 p = interaction_list.next(p)) {
	pair = interaction_list.retrieve(p);
	pair->RenewInteraction(weight_function);
    }
}

void Hydrodynamics::UpdatePhaseGradient(Boundary &boundary)
{
    LlistNode<Interaction> *p;
    Interaction *pair;
    Zero_PhaseGradient(boundary);
    for (p = interaction_list.first();
	 !interaction_list.isEnd(p);
	 p = interaction_list.next(p)) {
	pair = interaction_list.retrieve(p);
	pair->SummationPhaseGradient();
    }
}

void Hydrodynamics::UpdateDensity(ParticleManager &particles, QuinticSpline &weight_function)
{
    LlistNode<Interaction> *p;
    Interaction *pair;
    particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);
    Zero_density();
    for (p = interaction_list.first();
	 !interaction_list.isEnd(p);
	 p = interaction_list.next(p)) {
	pair = interaction_list.retrieve(p);
	pair->SummationDensity();
    }
    UpdateState();
}

void Hydrodynamics::UpdateDensity()
{
    Zero_density();
    for (LlistNode<Interaction> *p1 = interaction_list.first();
	 !interaction_list.isEnd(p1);
	 p1 = interaction_list.next(p1)) {
	Interaction *pair = interaction_list.retrieve(p1);
	pair->SummationDensity();
    }
    UpdateState();
}

void Hydrodynamics::UpdateChangeRate(ParticleManager &particles, QuinticSpline &weight_function)
{
    ZeroChangeRate();
    particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);
    for (LlistNode<Interaction> *p = interaction_list.first();
	 !interaction_list.isEnd(p);
	 p = interaction_list.next(p)) {
	Interaction *pair = interaction_list.retrieve(p);
	pair->UpdateForces();
    }
    AddGravity();
}

void Hydrodynamics::UpdateChangeRate()
{
    ZeroChangeRate();
    for (LlistNode<Interaction> *p = interaction_list.first();
	 !interaction_list.isEnd(p);
	 p = interaction_list.next(p)) {
	interaction_list.retrieve(p)->UpdateForces();
    }
    AddGravity();
}

void Hydrodynamics::UpdateRandom(double sqrtdt)
{
    Zero_Random();
    for (LlistNode<Interaction> *p = interaction_list.first();
	 !interaction_list.isEnd(p);
	 p = interaction_list.next(p)) {
	Interaction *pair = interaction_list.retrieve(p);
	pair->RandomForces(sqrtdt);
    }

}

void Hydrodynamics::ZeroChangeRate()
{
    enum {X, Y};
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	Particle *prtl = particle_list.retrieve(p);
	prtl->dedt = 0.0;
	prtl->drhodt = 0.0;
	prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
	prtl->_dU[X] = prtl->_dU[Y] = 0.0;

    }
}

void Hydrodynamics::Zero_density()
{
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	Particle *prtl = particle_list.retrieve(p);
	prtl->rho = 0.0;
    }
}

void Hydrodynamics::Zero_ShearRate()
{
    enum {X, Y};
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	Particle *prtl = particle_list.retrieve(p);
	prtl->ShearRate_x[X] = prtl->ShearRate_x[Y] = 0.0;
	prtl->ShearRate_y[X] = prtl->ShearRate_y[Y] = 0.0;
    }
}

void Hydrodynamics::Zero_PhaseGradient(Boundary &boundary)
{
    enum {X, Y};
    Particle *prtl;
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	prtl = particle_list.retrieve(p);
	prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
    for (LlistNode<Particle> *p1 = boundary.b.first();
	 !boundary.b.isEnd(p1);
	 p1 = boundary.b.next(p1)) {
	Particle *prtl = boundary.b.retrieve(p1);
	prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
}

void Hydrodynamics::Zero_Random()
{
    enum {X, Y};
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	Particle *prtl = particle_list.retrieve(p);
	prtl->_dU[X] = prtl->_dU[Y] = 0.0;
    }
}

void Hydrodynamics::AddGravity()
{
    Particle *prtl;
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	prtl = particle_list.retrieve(p);
	prtl->dUdt[X] += gravity[X];
	prtl->dUdt[Y] += gravity[Y];
    }
}

void Hydrodynamics::UpdateState()
{
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	Particle *prtl = particle_list.retrieve(p);
	prtl->p = get_p(prtl->mtl, prtl->rho);
    }
}

void Hydrodynamics::UpdatePahseMatrix(Boundary &boundary)
{
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	Particle *prtl = particle_list.retrieve(p);
	for(int i = 0; i < number_of_materials; i++)
	    for(int j = 0; j < number_of_materials; j++) {
		if( i != j) prtl->phi[i][j] = prtl->phi[i][j];
	    }
    }
    for (LlistNode<Particle> *p1 = boundary.b.first();
	 !boundary.b.isEnd(p1);
	 p1 = boundary.b.next(p1)) {
	Particle *prtl = boundary.b.retrieve(p1);
	for(int i = 0; i < number_of_materials; i++)
	    for(int j = 0; j < number_of_materials; j++) {
		if( i != j) prtl->phi[i][j] = prtl->phi[i][j];
	    }
    }
}

void Hydrodynamics::UpdateSurfaceStress(Boundary &boundary)
{

    double epsilon =1.0e-30;
    double interm0, interm1, interm2;
    Particle *prtl;
    LlistNode<Particle> *p;

    for (p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	prtl = particle_list.retrieve(p);
	interm0 = 1.0/(vv_abs(prtl->del_phi) + epsilon);
	interm1 = 0.5*vv_sqdiff(prtl->del_phi);
	interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
	prtl->del_phi[0] = interm1*interm0;
	prtl->del_phi[1] = interm2*interm0;
    }

    for (p = boundary.b.first();
	 !boundary.b.isEnd(p);
	 p = boundary.b.next(p)) {
	prtl = boundary.b.retrieve(p);
	interm0 = vv_abs(prtl->del_phi) + epsilon;
	interm1 = 0.5*vv_sqdiff(prtl->del_phi);
	interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
	prtl->del_phi[0] = interm1/interm0;
	prtl->del_phi[1] = interm2/interm0;
    }
}

double Hydrodynamics::SurfaceTensionCoefficient()
{
    double coefficient = 0.0;
    double totalvolume = 0.0;
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	Particle *prtl = particle_list.retrieve(p);
	double interm1 = prtl->m/prtl->rho;
	totalvolume += interm1;
	coefficient += vv_sq(prtl->del_phi)*interm1;
    }
    return coefficient/sqrt(totalvolume);
}

void Hydrodynamics::UpdateVolume(ParticleManager &particles, QuinticSpline &weight_function)
{
    double reciprocV;
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	Particle *prtl_org = particle_list.retrieve(p);
	particles.BuildNNP(prtl_org->R);
	reciprocV = 0.0;
	for (LlistNode<Particle> *p1 = particles.NNP_list.first();
	     !particles.NNP_list.isEnd(p1);
	     p1 = particles.NNP_list.next(p1)) {
	    Particle *prtl_dest = particles.NNP_list.retrieve(p1);
	    reciprocV += w(&weight_function, vv_distance(prtl_org->R, prtl_dest->R));
	}
	prtl_org->V = 1.0/reciprocV;
	particles.NNP_list.clear();
    }
}

double Hydrodynamics::GetTimestep()
{
    double Cs_max = 0.0, V_max = 0.0, rho_min = 1.0e30, rho_max = 1.0;
    double dt;
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	Particle *prtl = particle_list.retrieve(p);
	Cs_max = AMAX1(Cs_max, prtl->Cs);
	V_max = AMAX1(V_max, vv_abs(prtl->U));
	rho_min = AMIN1(rho_min, prtl->rho);
	rho_max = AMAX1(rho_max, prtl->rho);
    }

    dt = AMIN1(sqrt(0.5*(rho_min + rho_max))*dt_surf, dt_g_vis);
    return  0.25*AMIN1(dt, delta/(Cs_max + V_max));
}

void Hydrodynamics::Predictor(double dt)
{
    LlistNode<Particle> *p;
    Particle *prtl;
    for (p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	prtl = particle_list.retrieve(p);
	prtl->R_I[X] = prtl->R[X];
	prtl->R_I[Y] = prtl->R[Y];

	prtl->rho_I = prtl->rho;
	prtl->U_I[X] = prtl->U[X];
	prtl->U_I[Y] = prtl->U[Y];

	prtl->R[X] = prtl->R[X] + prtl->U[X]*dt;
	prtl->R[Y] = prtl->R[Y] + prtl->U[Y]*dt;

	prtl->rho = prtl->rho + prtl->drhodt*dt;
	prtl->U[X] = prtl->U[X] + prtl->dUdt[X]*dt;
	prtl->U[Y] = prtl->U[Y] + prtl->dUdt[Y]*dt;

	prtl->R[X] = (prtl->R[X] + prtl->R_I[X])*0.5;
	prtl->R[Y] = (prtl->R[Y] + prtl->R_I[Y])*0.5;

	prtl->rho = (prtl->rho + prtl->rho_I)*0.5;

	prtl->U[X] = (prtl->U[X] + prtl->U_I[X])*0.5;
	prtl->U[Y] = (prtl->U[Y] + prtl->U_I[Y])*0.5;
    }
}

void Hydrodynamics::Corrector(double dt)
{
    LlistNode<Particle> *p;
    Particle *prtl;    
    for (p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	prtl = particle_list.retrieve(p);
	prtl->R[X] = prtl->R_I[X] + prtl->U[X]*dt;
	prtl->R[Y] = prtl->R_I[Y] + prtl->U[Y]*dt;
	prtl->rho = prtl->rho + prtl->drhodt*dt;
	prtl->U[X] = prtl->U_I[X] + prtl->dUdt[X]*dt;
	prtl->U[Y] = prtl->U_I[Y] + prtl->dUdt[Y]*dt;
    }
}

void Hydrodynamics::Predictor_summation(double dt)
{
    LlistNode<Particle> *p;
    Particle *prtl;
    for (p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	prtl = particle_list.retrieve(p);
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
    LlistNode<Particle> *p;
    Particle *prtl;    
    for (p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	prtl = particle_list.retrieve(p);
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
    LlistNode<Particle> *p;
    Particle *prtl;
    for (p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
	prtl = particle_list.retrieve(p);
	prtl->U[X] = prtl->U[X] + prtl->_dU[X];
	prtl->U[Y] = prtl->U[Y] + prtl->_dU[Y];    
    }
}
