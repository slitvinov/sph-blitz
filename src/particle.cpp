// particle.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: 

//-------------------------------------------------------------------
//				Particle data type definition
//				particle.cpp
//----------------------------------------------------------------

// ***** local includes *****
#include "glbcls.h"
#include "glbfunc.h"

long Particle::ID_max = 0;
int Particle::number_of_materials = 0;
//----------------------------------------------------------------------------------------
//							constructors
//							empty particle
//----------------------------------------------------------------------------------------
Particle::Particle(Initiation &ini)
{
	int i, j;

	//copy properties from initiation
	number_of_materials = ini.number_of_materials;

	//phase filed
	phi = new double*[number_of_materials];
	lap_phi = new double*[number_of_materials];
	for(i = 0; i < number_of_materials; i++) {
		phi[i] = new double[number_of_materials];
		lap_phi[i] = new double[number_of_materials];
	}
	for(i = 0; i < number_of_materials; i++)
		for(j = 0; j < number_of_materials; j++) {
			phi[i][j] = 0.0;
			lap_phi[i][j] = 0.0;
		}
}
//----------------------------------------------------------------------------------------
//	deconstructor particle
//----------------------------------------------------------------------------------------
Particle::~Particle()
{
	int i;

	//phase filed
	for(i = 0; i < number_of_materials; i++) {
		delete[] phi[i];
		delete[] lap_phi[i];
	}
	//pahse field gradient matrix
	delete[] phi;
	delete[] lap_phi;
}
//----------------------------------------------------------------------------------------
//							real particle
//		NOTE the particle mass and volume will be specified initiation::VolumeMass()
//----------------------------------------------------------------------------------------
Particle::Particle(Vec2d position, Vec2d velocity, double density, double pressure, double temperature, 
				   Material &material) : bd(0)
{
	int i, j;

	//increase the total particle number
	ID_max++;
	
	//give a new ID number
	ID = ID_max;

	//point to the material properties
	mtl = &material;
	//viscosity
	eta = mtl->eta; zeta = mtl->zeta;
	k_thermal = mtl->k_thermal;

	//set particle position
	R = position; 
	
	//set states
	rho = density; p = pressure; T = temperature; Cs = mtl->get_Cs(p, rho);
	U = velocity; U_I = U;
	
	//set conservative values and their  intermediate values
	m = 0.0; V = 0.0; energy = T; energy_I = energy;
	R_I = R; P_I = P; rho_I = rho;
	P_n = P; U_n = U; rho_n = rho; energy_n = energy; 

	//phase filed
	phi = new double*[number_of_materials];
	lap_phi = new double*[number_of_materials];
	for(i = 0; i < number_of_materials; i++) {
		phi[i] = new double[number_of_materials];
		lap_phi[i] = new double[number_of_materials];
	}
	for(i = 0; i < number_of_materials; i++)
		for(j = 0; j < number_of_materials; j++) {
			phi[i][j] = 0.0;
			lap_phi[i][j] = 0.0;
		}
}
//----------------------------------------------------------------------------------------
//								construct a wall particle
//----------------------------------------------------------------------------------------
Particle::Particle(double x, double y, double u, double v, 
				   double distance, double normal_x, double normal_y, Material &material) : bd(1), bd_type(0)
{

	//give a new ID number
	ID = 0;

	//point to the material properties
	mtl = &material;

	//set particle position
	R[0] = x; R[1] = y; 
	
	//set states
	U[0] = u; U[1] = v;
	
	//distance and normal directions to boundary
	bd_dst = distance;
	//nrml[0] = normal_x; nrml[1] = normal_y;

	//set states value to avoid error
	rho = 0.0, p = 0.0, T = 0.0;
}
//----------------------------------------------------------------------------------------
//						creat a ghost particle 
//----------------------------------------------------------------------------------------
Particle::Particle(Particle &RealParticle) : bd(1), bd_type(1)
{
	int i, j;
	
	//give a new ID number
	ID = 0;

	//point to its real particle
	rl_prtl = &RealParticle;

	//point to the material properties
	mtl = RealParticle.mtl;
	//viscosity
	eta = mtl->eta; zeta = mtl->zeta; 
	k_thermal = mtl->k_thermal;

	//set states
	R = RealParticle.R; rho = RealParticle.rho; p = RealParticle.p; T = RealParticle.T;
	Cs =RealParticle.Cs; U = RealParticle.U; U_I = RealParticle.U_I;
	ShearRate_x = RealParticle.ShearRate_x, ShearRate_y = RealParticle.ShearRate_y;
	
	//set conservative values and their  intermediate values
	m = RealParticle.m; V = RealParticle.V; energy = RealParticle.energy; 
	R_I = RealParticle.R_I;	energy_I = RealParticle.energy_I;
	P = RealParticle.P; P_I = RealParticle.P_I; rho_I = rho;
	P_n = RealParticle.P_n; U_n = RealParticle.U_n; rho_n = RealParticle.rho_n;
	energy_n = RealParticle.energy_n;
	
	//phase filed
	phi = new double*[number_of_materials];
	lap_phi = new double*[number_of_materials];
	for(i = 0; i < number_of_materials; i++) {
		phi[i] = new double[number_of_materials];
		lap_phi[i] = new double[number_of_materials];
	}
	for(i = 0; i < number_of_materials; i++)
		for(j = 0; j < number_of_materials; j++) {
			phi[i][j] = 0.0;
			lap_phi[i][j] = 0.0;
		}

}
//----------------------------------------------------------------------------------------
//							creat an image particle
//----------------------------------------------------------------------------------------
Particle::Particle(Particle &RealParticle, Material &material): bd(1), bd_type(0)
{
	int i, j;
	
	//give a new ID number
	ID = 0;

	//point to its real particle
	rl_prtl = &RealParticle;

	//point to the material properties
	mtl = &material;
	//viscosity
	eta = RealParticle.eta; zeta = RealParticle.zeta; 
	k_thermal = RealParticle.k_thermal;


	//set states
	R = RealParticle.R; rho = RealParticle.rho; p = RealParticle.p; T = RealParticle.T;
	Cs =RealParticle.Cs; U = RealParticle.U; U_I = RealParticle.U_I;
	ShearRate_x = RealParticle.ShearRate_x, ShearRate_y = RealParticle.ShearRate_y;
	
	//set conservative values and their  intermediate values
	m = RealParticle.m; V = RealParticle.V; energy = RealParticle.energy;
	R_I = RealParticle.R_I;	energy_I = RealParticle.energy_I;
	P = RealParticle.P; P_I = RealParticle.P_I; rho_I = rho;
	P_n = RealParticle.P_n; U_n = RealParticle.U_n; rho_n = RealParticle.rho_n;
	energy_n = RealParticle.energy_n;

	//phase filed
	phi = new double*[number_of_materials];
	lap_phi = new double*[number_of_materials];
	for(i = 0; i < number_of_materials; i++) {
		phi[i] = new double[number_of_materials];
		lap_phi[i] = new double[number_of_materials];
	}
	for(i = 0; i < number_of_materials; i++)
		for(j = 0; j < number_of_materials; j++) {
			phi[i][j] = 0.0;
			lap_phi[i][j] = 0.0;
		}

}
//----------------------------------------------------------------------------------------
//					particle states copier for boundary particles
//----------------------------------------------------------------------------------------
void Particle::StatesCopier(Particle &RealParticle, int type)
{
	int i, j;

	//copy states
	R = RealParticle.R; m = RealParticle.m;
	rho = RealParticle.rho; V = RealParticle.V;
	p = RealParticle.p; T = RealParticle.T;
	rho_I = RealParticle.rho_I;
	Cs =RealParticle.Cs; U = RealParticle.U; U_I = RealParticle.U_I;
	ShearRate_x = RealParticle.ShearRate_x, ShearRate_y = RealParticle.ShearRate_y;

	//perodic boundary
	if (type == 1 ) {
		del_phi = RealParticle.del_phi;
		for(i = 0; i < number_of_materials; i++) {
			for(j = 0; j < number_of_materials; j++) {
				phi[i][j] = RealParticle.phi[i][j];
				lap_phi[i][j] = RealParticle.lap_phi[i][j];
			}
		}
	}
	
	//wall boundary
	if (type == 0) {
		phi[0][0] = 0.0;
		for(i = 1; i < number_of_materials; i++) phi[0][0] += RealParticle.phi[i][i];
	}

}

void Particle::ChangePhase(Material &nm)
{
  mtl=(&nm);
  k_thermal = nm.k_thermal;
  eta=nm.eta;
  zeta=nm.zeta;
}
