#include <cmath>
#include <cstdio>
#include "vv.h"
#include "glbfunc.h"
#include "material.h"
#include "particle.h"

enum {X, Y};

long particle_ID_max;
int particle_number_of_materials;

Particle::~Particle()
{
    int i;
    for(i = 0; i < particle_number_of_materials; i++) {
	delete[] phi[i];
    }
    delete[] phi;
}

Particle::Particle(double position[2], double velocity[2], double density, double pressure, double temperature, Material *material)
{
    int i, j;
    bd = 0;
    particle_ID_max++;

    ID = particle_ID_max;
    mtl = material;
    eta = mtl->eta; zeta = mtl->zeta;
    R[X] = position[X];
    R[Y] = position[Y];
    rho = density;
    p = pressure;
    T = temperature;
    Cs = get_Cs(mtl, p, rho);
    U[X] = velocity[X];
    U[Y] = velocity[Y];
    U_I[X] = U[X];
    U_I[Y] = U[Y];
    m = 0.0;
    V = 0.0;
    R_I[X] = R[X];
    R_I[Y] = R[Y];
    P_I[X] = P[X];
    P_I[Y] = P[Y];
    rho_I = rho;
    P_n[X] = P[X];
    P_n[Y] = P[Y];
    U_n[X] = U[X];
    U_n[Y] = U[Y];
    rho_n = rho;
    phi = new double*[particle_number_of_materials];
    for(i = 0; i < particle_number_of_materials; i++) {
	phi[i] = new double[particle_number_of_materials];
    }
    for(i = 0; i < particle_number_of_materials; i++)
	for(j = 0; j < particle_number_of_materials; j++) {
	    phi[i][j] = 0.0;
	}
}

Particle::Particle(double x, double y, double u, double v, Material *material)
{
    bd = 1;
    bd_type = 0;
    ID = 0;
    mtl = material;
    R[0] = x;
    R[1] = y;
    U[0] = u;
    U[1] = v;
    rho = 0.0;
    p = 0.0;
    T = 0.0;
}

Particle::Particle(Particle &RealParticle)
{
    int i, j;
    bd = 1;
    bd_type = 1;
    ID = 0;
    rl_prtl = &RealParticle;
    mtl = RealParticle.mtl;
    eta = mtl->eta; zeta = mtl->zeta;
    R[X] = RealParticle.R[X];
    R[Y] = RealParticle.R[Y];
    rho = RealParticle.rho;
    p = RealParticle.p;
    T = RealParticle.T;
    Cs =RealParticle.Cs;
    U[X] = RealParticle.U[X];
    U[Y] = RealParticle.U[Y];
    U_I[X] = RealParticle.U_I[X];
    U_I[Y] = RealParticle.U_I[Y];
    ShearRate_x[X] = RealParticle.ShearRate_x[X];
    ShearRate_x[Y] = RealParticle.ShearRate_x[Y];
    ShearRate_y[X] = RealParticle.ShearRate_y[X];
    ShearRate_y[Y] = RealParticle.ShearRate_y[Y];
    m = RealParticle.m;
    V = RealParticle.V;
    e = RealParticle.e;
    R_I[X] = RealParticle.R_I[X];
    R_I[Y] = RealParticle.R_I[Y];
    P[X] = RealParticle.P[X];
    P[Y] = RealParticle.P[Y];
    P_I[X] = RealParticle.P_I[X];
    P_I[Y] = RealParticle.P_I[Y];
    rho_I = rho;
    P_n[X] = RealParticle.P_n[X];
    P_n[Y] = RealParticle.P_n[Y];
    U_n[X] = RealParticle.U_n[X];
    U_n[Y] = RealParticle.U_n[Y];
    rho_n = RealParticle.rho_n;
    phi = new double*[particle_number_of_materials];
    for(i = 0; i < particle_number_of_materials; i++) {
	phi[i] = new double[particle_number_of_materials];
    }
    for(i = 0; i < particle_number_of_materials; i++)
	for(j = 0; j < particle_number_of_materials; j++) {
	    phi[i][j] = 0.0;
	}
}

Particle::Particle(Particle &RealParticle, Material *material)
{
    int i, j;
    bd = 1;
    bd_type = 0;
    ID = 0;
    rl_prtl = &RealParticle;
    mtl = material;
    eta = RealParticle.eta;
    zeta = RealParticle.zeta;
    R[X] = RealParticle.R[X];
    R[Y] = RealParticle.R[Y];
    rho = RealParticle.rho;
    p = RealParticle.p;
    T = RealParticle.T;
    Cs =RealParticle.Cs;
    U[X] = RealParticle.U[X];
    U[Y] = RealParticle.U[Y];
    U_I[X] = RealParticle.U_I[X];
    U_I[Y] = RealParticle.U_I[Y];
    ShearRate_x[X] = RealParticle.ShearRate_x[X];
    ShearRate_x[Y] = RealParticle.ShearRate_x[Y];
    ShearRate_y[X] = RealParticle.ShearRate_y[X];
    ShearRate_y[Y] = RealParticle.ShearRate_y[Y];
    m = RealParticle.m;
    V = RealParticle.V;
    e = RealParticle.e;
    R_I[X] = RealParticle.R_I[X];
    R_I[Y] = RealParticle.R_I[Y];
    P[X] = RealParticle.P[X];
    P[Y] = RealParticle.P[Y];
    P_I[X] = RealParticle.P_I[X];
    P_I[Y] = RealParticle.P_I[Y];
    rho_I = rho;
    P_n[X] = RealParticle.P_n[X];
    P_n[Y] = RealParticle.P_n[Y];
    U_n[X] = RealParticle.U_n[X];
    U_n[Y] = RealParticle.U_n[Y];
    rho_n = RealParticle.rho_n;
    phi = new double*[particle_number_of_materials];
    for(i = 0; i < particle_number_of_materials; i++) {
	phi[i] = new double[particle_number_of_materials];
    }
    for(i = 0; i < particle_number_of_materials; i++)
	for(j = 0; j < particle_number_of_materials; j++) {
	    phi[i][j] = 0.0;
	}
}

void Particle::StatesCopier(Particle &RealParticle, int type)
{
    int i, j;

    R[X] = RealParticle.R[X];
    R[Y] = RealParticle.R[Y];
    m = RealParticle.m;
    rho = RealParticle.rho;
    V = RealParticle.V;
    p = RealParticle.p;
    T = RealParticle.T;
    rho_I = RealParticle.rho_I;
    Cs =RealParticle.Cs;
    U[X] = RealParticle.U[X];
    U[Y] = RealParticle.U[Y];
    U_I[X] = RealParticle.U_I[X];
    U_I[Y] = RealParticle.U_I[Y];
    ShearRate_x[X] = RealParticle.ShearRate_x[X];
    ShearRate_x[Y] = RealParticle.ShearRate_x[Y];
    ShearRate_y[X] = RealParticle.ShearRate_y[X];
    ShearRate_y[Y] = RealParticle.ShearRate_y[Y];
    if (type == 1 ) {
	del_phi[X] = RealParticle.del_phi[X];
	del_phi[Y] = RealParticle.del_phi[Y];
	for(i = 0; i < particle_number_of_materials; i++) {
	    for(j = 0; j < particle_number_of_materials; j++) {
		phi[i][j] = RealParticle.phi[i][j];
	    }
	}
    }
    if (type == 0) {
	phi[0][0] = 0.0;
	for(i = 1; i < particle_number_of_materials; i++)
	    phi[0][0] += RealParticle.phi[i][i];
    }
}
