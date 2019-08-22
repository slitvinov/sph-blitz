///\file hydrodynamics.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>,

//----------------------------------------------------------------------------------------
//      Define materials and their hydrodynamical interactions
//		hydrodynamics.cpp
//----------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstring>

#include <cstdio>
#include <cstdlib>

class Hydrodynamics;
class ParticleManager;

// ***** localincludes *****
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

//----------------------------------------------------------------------------------------
//						constructor
//----------------------------------------------------------------------------------------
Hydrodynamics::Hydrodynamics(ParticleManager &particles, Initiation &ini) {
  int k, m;
  int l, n;

  //make materials
  char Key_word[FILENAME_MAX];
  char inputfile[FILENAME_MAX];

  ///<ul><li>copy properties from initiation class
  number_of_materials = ini.number_of_materials;
  gravity[X] = ini.g_force[X];
  gravity[Y] = ini.g_force[Y];
  smoothinglength = ini.smoothinglength;
  delta = ini.delta; delta2 = delta*delta; delta3 = delta2*delta;

  ///<li>create material matrix
  materials = new Material[number_of_materials];
  ///<li>create the force matrix
  forces = new Force*[number_of_materials];
  for(k = 0; k < number_of_materials; k++) forces[k] = new Force[number_of_materials];

  ///<li>check if inputfile exists
  strcpy(inputfile, ini.inputfile);
  ifstream fin(inputfile, ios::in);
  if (!fin) {
    cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
    std::cout << __FILE__ << ':' << __LINE__ << std::endl;
    exit(1);
  }
  else cout<<"\nMaterial: read the propeties of materials and interaction forces \n";

  ///<li>reading all key words and configuration data
  while(!fin.eof()) {

    //read a string block
    fin>>Key_word;

    //comparing the key words for the materials
    if(!strcmp(Key_word, "MATERIALS"))
      ///<li>if  key word material: read all materials (from .cfg file)
      for(k = 0; k < number_of_materials; k++) {
	//the material number
	///<ul><li>save each one of them in materials matrix
	materials[k].number = k;
	fin>>materials[k].material_name>>materials[k].material_type;
	fin>>materials[k].eta>>materials[k].zeta
	   >>materials[k].gamma>>materials[k].rho0>>materials[k].a0;
	Set_nu(&materials[k]);
      }

    //comparing the key words for the force matrix
    if(!strcmp(Key_word, "FORCES"))
   ///<li>if  key word forces: read all forces for all materials (from .cfg file)
      //read all materials
      ///<ul><li> save eahc one of them in forces matrix
      for(l = 0; l < number_of_materials; l++)
	for(n = 0; n < number_of_materials; n++) {
	  fin>>k>>m;
	  fin>>forces[k][m].epsilon>>forces[k][m].sigma
	     >>forces[k][m].shear_slip>>forces[k][m].bulk_slip;

	}
  }
  fin.close();

  ///<li>initialize parameters for time step and the artificial compressiblity
  viscosity_max = 0.0; surface_max = 0.0;
  for(k = 0; k < number_of_materials; k++) {
    viscosity_max = AMAX1(viscosity_max, materials[k].nu);
    for(l = 0; l < number_of_materials; l++) {
      surface_max = AMAX1(surface_max, forces[k][l].sigma);
    }
  }
  dt_g_vis = AMIN1(sqrt(delta/vv_abs(gravity)), 0.5*delta2/viscosity_max);
  dt_surf = 0.4*sqrt(delta3/surface_max);

  ///<li>determine the artificial compressiblity
  double sound;
  //g force and viscosity
  sound = AMAX1(vv_abs(ini.g_force), viscosity_max);
  //surface tension effects
  sound = AMAX1(surface_max, sound);
  for(k = 0; k < number_of_materials; k++)
    Set_b0(&materials[k], sound);

}

//----------------------------------------------------------------------------------------
//						Build new pairs
//----------------------------------------------------------------------------------------
void Hydrodynamics::BuildPair(ParticleManager &particles, QuinticSpline &weight_function)
{
  ///- obtain the interaction pairs by just calling the particles BuildInteraction method
  particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);

}
//----------------------------------------------------------------------------------------
//						update new parameters in pairs
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdatePair(QuinticSpline &weight_function)
{

  ///- iterate the interaction list
  for (LlistNode<Interaction> *p = interaction_list.first();
       !interaction_list.isEnd(p);
       p = interaction_list.next(p)) {
    ///- and for each interactionpair call RenewInteraction method
    //a interaction pair
    Interaction *pair = interaction_list.retrieve(p);
    //renew pair parameters
    pair->RenewInteraction(weight_function);
  }
}
//----------------------------------------------------------------------------------------
//		summation for pahse field gradient
//----------------------------------------------------------------------------------------
// not independant with UpdateDensity
void Hydrodynamics::UpdatePhaseGradient(Boundary &boundary)
{
  ///- initiate by callingZer_PhaseGradient()
  Zero_PhaseGradient(boundary);
  ///- iterate the interaction list
  for (LlistNode<Interaction> *p2 = interaction_list.first();
       !interaction_list.isEnd(p2);
       p2 = interaction_list.next(p2)) {

    //a interaction pair
    Interaction *pair = interaction_list.retrieve(p2);
    ///- calculate for each pair the pair forces or change rate
    pair->SummationPhaseGradient();
  }
}
//----------------------------------------------------------------------------------------
//		summation for particles density with updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateDensity(ParticleManager &particles, QuinticSpline &weight_function)
{

  ///- obtain the interaction pairs
  particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);

  ///- initiate by calling Zero_density method
  Zero_density();
  ///- iterate the interaction list
  for (LlistNode<Interaction> *p1 = interaction_list.first();
       !interaction_list.isEnd(p1);
       p1 = interaction_list.next(p1)) {

    //a interaction pair
    Interaction *pair = interaction_list.retrieve(p1);
    ///- calculate for each pair the pair forces or change rate by calling SummationDensity() method
    pair->SummationDensity();
  }

  ///- calulate new pressure by calling UpdateState() Method
  UpdateState();
}
//----------------------------------------------------------------------------------------
//		summation for particles density without updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateDensity()
{
  ///- initiate zero density
  Zero_density();
  ///- iterate the interaction list
  for (LlistNode<Interaction> *p1 = interaction_list.first();
       !interaction_list.isEnd(p1);
       p1 = interaction_list.next(p1)) {

    //a interaction pair
    Interaction *pair = interaction_list.retrieve(p1);
    ///- calculate for each pair the pair forces or change rate
    pair->SummationDensity();
  }

  ///- calulate new pressure by calling UpdateState()
  UpdateState();
}
//----------------------------------------------------------------------------------------
//				calculate interaction with updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateChangeRate(ParticleManager &particles, QuinticSpline &weight_function)
{
  ///- initiate change rate of each real particle by calling ZerpChangeRate()
  ZeroChangeRate();

  ///- obtain the interaction pairs
  particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);

  ///- iterate the interaction list
  for (LlistNode<Interaction> *p = interaction_list.first();
       !interaction_list.isEnd(p);
       p = interaction_list.next(p)) {

    //a interaction pair
    Interaction *pair = interaction_list.retrieve(p);
    ///- calculate for eahc pair the pair forces or change rate
    pair->UpdateForces();

  }

  ///- include the gravity effects by calling AddGravity()
  AddGravity();
}
//----------------------------------------------------------------------------------------
//				calculate interaction without updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateChangeRate()
{
  ///- initiate the change rate of each real particle by calling ZeroChangeRate()
  ZeroChangeRate();

    ///- iterate the interaction list
    for (LlistNode<Interaction> *p = interaction_list.first();
	 !interaction_list.isEnd(p);
	 p = interaction_list.next(p)) {
	//a interaction pair
	///- calculate for each pair the pair forces or change rate
	interaction_list.retrieve(p)->UpdateForces();
    }

  ///- include the gravity effects
  AddGravity();
}
//----------------------------------------------------------------------------------------
//			calculate random interaction without updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateRandom(double sqrtdt)
{
  //initiate the change rate of each real particle
  Zero_Random();

  //set a new random seed
  //	wiener.Ranils();

  //iterate the interaction list
  for (LlistNode<Interaction> *p = interaction_list.first();
       !interaction_list.isEnd(p);
       p = interaction_list.next(p)) {

    //a interaction pair
    Interaction *pair = interaction_list.retrieve(p);
    //calculate the pair forces or change rate
    pair->RandomForces(sqrtdt);
  }

}
//----------------------------------------------------------------------------------------
//						initiate particle change rate
//----------------------------------------------------------------------------------------
void Hydrodynamics::ZeroChangeRate()
{
    enum {X, Y};
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    //particle
    Particle *prtl = particle_list.retrieve(p);

    ///- set for each particle change rates to zero
    prtl->dedt = 0.0;
    prtl->drhodt = 0.0;
    prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
    prtl->_dU[X] = prtl->_dU[Y] = 0.0;

  }
}
//----------------------------------------------------------------------------------------
//							initiate particle density to zero
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_density()
{
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    //particle
    Particle *prtl = particle_list.retrieve(p);

    ///- set for each particle density to zero
    prtl->rho = 0.0;
  }
}
//----------------------------------------------------------------------------------------
//						initiate shear rate to zero
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_ShearRate()
{
    enum {X, Y};
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    //particle
    Particle *prtl = particle_list.retrieve(p);

    ///- set ShearRate to zero for each particle
    prtl->ShearRate_x[X] = prtl->ShearRate_x[Y] = 0.0;
    prtl->ShearRate_y[X] = prtl->ShearRate_y[Y] = 0.0;
  }
}
//----------------------------------------------------------------------------------------
//						initiate pahse gradient
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_PhaseGradient(Boundary &boundary)
{
    enum {X, Y};
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    //particle
    Particle *prtl = particle_list.retrieve(p);

    ///- set phase gradient to zeo for each of these particles
    prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
  }

  ///- iterate particles on the boundary particle list
  for (LlistNode<Particle> *p1 = boundary.boundary_particle_list.first();
       !boundary.boundary_particle_list.isEnd(p1);
       p1 = boundary.boundary_particle_list.next(p1)) {

    //particle
    Particle *prtl = boundary.boundary_particle_list.retrieve(p1);

     ///- set phase gradient to zeo for each of these particle
    prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
  }
}
//----------------------------------------------------------------------------------------
//						initiate random force
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_Random()
{
    enum {X, Y};
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    //particle
    Particle *prtl = particle_list.retrieve(p);

    ///- all random values to zero (so, _dU is random value???)
    prtl->_dU[X] = prtl->_dU[Y] = 0.0;
  }
}
//----------------------------------------------------------------------------------------
//							add the gravity effects
//----------------------------------------------------------------------------------------
void Hydrodynamics::AddGravity()
{
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    //a particle
    Particle *prtl = particle_list.retrieve(p);

    prtl->dUdt[X] += gravity[X];
    prtl->dUdt[Y] += gravity[Y];
  }
}
//----------------------------------------------------------------------------------------
//							calculate states from conservatives
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateState()
{
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    //a particle
    Particle *prtl = particle_list.retrieve(p);

    ///- calculate pressure for each particle
    prtl->p = get_p(prtl->mtl, prtl->rho);
    //			prtl->T = prtl->mtl->get_T(prtl->e);
  }

}
//----------------------------------------------------------------------------------------
//							calculate phase field matrix
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdatePahseMatrix(Boundary &boundary)
{
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    //a particle
    Particle *prtl = particle_list.retrieve(p);

    ///- all phase surface stress (currently no action is performed)
    for(int i = 0; i < number_of_materials; i++)
      for(int j = 0; j < number_of_materials; j++) {
	if( i != j) prtl->phi[i][j] = prtl->phi[i][j]; //prtl->phi[i][i]/(prtl->phi[i][i] + prtl->phi[j][j] + 1.0e-30);
      }
  }

  ///- iterate particles on the boundary particle list
  for (LlistNode<Particle> *p1 = boundary.boundary_particle_list.first();
       !boundary.boundary_particle_list.isEnd(p1);
       p1 = boundary.boundary_particle_list.next(p1)) {

    //particle
    Particle *prtl = boundary.boundary_particle_list.retrieve(p1);

    ///- all phase surface stress (currently no action is perforemd)
    for(int i = 0; i < number_of_materials; i++)
      for(int j = 0; j < number_of_materials; j++) {
	if( i != j) prtl->phi[i][j] = prtl->phi[i][j]; //prtl->phi[i][i]/(prtl->phi[i][i] + prtl->phi[j][j] + 1.0e-30);
      }
  }
}
//----------------------------------------------------------------------------------------
//							calculate Surface  Stress
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateSurfaceStress(Boundary &boundary)
{

  double epsilon =1.0e-30;
  double interm0, interm1, interm2;

  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    //a particle
    Particle *prtl = particle_list.retrieve(p);

    ///- update phase surface stress for all particles on this list
    interm0 = 1.0/(vv_abs(prtl->del_phi) + epsilon);
    interm1 = 0.5*vv_sqdiff(prtl->del_phi);
    interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
    prtl->del_phi[0] = interm1*interm0;
    prtl->del_phi[1] = interm2*interm0;
  }

  ///- iterate particles on the boundary particle list
  for (LlistNode<Particle> *p1 = boundary.boundary_particle_list.first();
       !boundary.boundary_particle_list.isEnd(p1);
       p1 = boundary.boundary_particle_list.next(p1)) {

    //particle
    Particle *prtl = boundary.boundary_particle_list.retrieve(p1);

    ///- update phase surface stress for all particles on this list
    interm0 = vv_abs(prtl->del_phi) + epsilon;
    interm1 = 0.5*vv_sqdiff(prtl->del_phi);
    interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
    prtl->del_phi[0] = interm1/interm0;
    prtl->del_phi[1] = interm2/interm0;
  }
}
//----------------------------------------------------------------------------------------
//							Calculate Surface Tension Coefficient
//----------------------------------------------------------------------------------------

double Hydrodynamics::SurfaceTensionCoefficient()
{
  double coefficient = 0.0; double totalvolume = 0.0;

  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    //a particle
    Particle *prtl = particle_list.retrieve(p);

    ///- calculate  phase surface stress for all particles
    double interm1 = prtl->m/prtl->rho;
    totalvolume += interm1;
    coefficient += vv_sq(prtl->del_phi)*interm1;
  }
  return coefficient/sqrt(totalvolume);
}
//----------------------------------------------------------------------------------------
//								calculate partilce volume
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateVolume(ParticleManager &particles, QuinticSpline &weight_function)
{
  double reciprocV; //the inverse of volume or volume

  ///<ul><li> iterate particles on the particle list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    ///<ul><li>take origin particle
    Particle *prtl_org = particle_list.retrieve(p);
    //<li>build the nearest particle list
    particles.BuildNNP(prtl_org->R);

    reciprocV = 0.0;
    //<li>iterate this Nearest Neighbor Particle list
    for (LlistNode<Particle> *p1 = particles.NNP_list.first();
	 !particles.NNP_list.isEnd(p1);
	 p1 = particles.NNP_list.next(p1)) {

      //get a particle
      Particle *prtl_dest = particles.NNP_list.retrieve(p1);

      ///<ul><li>sum the weights for all of these particles (because they are the inverse of a volume!?!)</ul>
      reciprocV += w(&weight_function, vv_distance(prtl_org->R, prtl_dest->R));
    }
    ///<li>calculate volume
    prtl_org->V = 1.0/reciprocV;

    ///<li>clear the NNP_list</ul></ul>
    particles.NNP_list.clear();
  }

}
//----------------------------------------------------------------------------------------
//							get the time step
//----------------------------------------------------------------------------------------
double Hydrodynamics::GetTimestep()
{
  //maximum sound speed, particle velocity and density
  double Cs_max = 0.0, V_max = 0.0, rho_min = 1.0e30, rho_max = 1.0;
  double dt;

  //predict the time step
  //iterate the partilce list
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
//----------------------------------------------------------------------------------------
//						the redictor and corrector method: predictor
//----------------------------------------------------------------------------------------
void Hydrodynamics::Predictor(double dt)
{
  ///<ul><li> iterate the real partilce list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    Particle *prtl = particle_list.retrieve(p);

    ///<ul><li>save values at step n
    prtl->R_I[X] = prtl->R[X];
    prtl->R_I[Y] = prtl->R[Y];

    prtl->rho_I = prtl->rho;
    prtl->U_I[X] = prtl->U[X];
    prtl->U_I[Y] = prtl->U[Y];

    ///<li>predict values at step n+1
    prtl->R[X] = prtl->R[X] + prtl->U[X]*dt;
    prtl->R[Y] = prtl->R[Y] + prtl->U[Y]*dt;

    prtl->rho = prtl->rho + prtl->drhodt*dt;
    prtl->U[X] = prtl->U[X] + prtl->dUdt[X]*dt;
    prtl->U[Y] = prtl->U[Y] + prtl->dUdt[Y]*dt;

    ///<li>calculate the middle values at step n+1/2</ul></ul>
    prtl->R[X] = (prtl->R[X] + prtl->R_I[X])*0.5;
    prtl->R[Y] = (prtl->R[Y] + prtl->R_I[Y])*0.5;

    prtl->rho = (prtl->rho + prtl->rho_I)*0.5;

    prtl->U[X] = (prtl->U[X] + prtl->U_I[X])*0.5;
    prtl->U[Y] = (prtl->U[Y] + prtl->U_I[Y])*0.5;
  }
}
//----------------------------------------------------------------------------------------
//							the redictor and corrector method: predictor
//----------------------------------------------------------------------------------------
void Hydrodynamics::Corrector(double dt)
{
  ///- iterate the real partilce list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    Particle *prtl = particle_list.retrieve(p);

    ///- for each particle: correction based on values on n step and change rate at n+1/2
    prtl->R[X] = prtl->R_I[X] + prtl->U[X]*dt;
    prtl->R[Y] = prtl->R_I[Y] + prtl->U[Y]*dt;

    prtl->rho = prtl->rho + prtl->drhodt*dt;

    prtl->U[X] = prtl->U_I[X] + prtl->dUdt[X]*dt;
    prtl->U[Y] = prtl->U_I[Y] + prtl->dUdt[Y]*dt;
  }
}
//----------------------------------------------------------------------------------------
//					the predictor and corrector method: predictor, no density updating
//----------------------------------------------------------------------------------------
void Hydrodynamics::Predictor_summation(double dt)
{
  ///<ul><li>iterate the real partilce list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    Particle *prtl = particle_list.retrieve(p);

    ///<ul><li>save values (R,U)  at step n in intermediate variables ._I
    prtl->R_I[X] = prtl->R[X];
    prtl->R_I[Y] = prtl->R[Y];

    prtl->U[X] += prtl->_dU[X];
    prtl->U[Y] += prtl->_dU[Y];

    prtl->U_I[X] = prtl->U[X];
    prtl->U_I[Y] = prtl->U[Y];

    ///<li>predict values at step n+1
    prtl->R[X] = prtl->R[X] + prtl->U[X]*dt;
    prtl->R[Y] = prtl->R[Y] + prtl->U[Y]*dt;

    prtl->U[X] = prtl->U[X] + prtl->dUdt[X]*dt;
    prtl->U[Y] = prtl->U[Y] + prtl->dUdt[Y]*dt;

    ///<li>calculate the middle values at step n+1/2 and save them in Particle objects prtl</ul></ul>
    prtl->R[X] = (prtl->R[X] + prtl->R_I[X])*0.5;
    prtl->R[Y] = (prtl->R[Y] + prtl->R_I[Y])*0.5;

    prtl->U[X] = (prtl->U[X] + prtl->U_I[X])*0.5;
    prtl->U[Y] = (prtl->U[Y] + prtl->U_I[Y])*0.5;
  }
}
//----------------------------------------------------------------------------------------
//			the predictor and corrector method: predictor, no density updating
//----------------------------------------------------------------------------------------
void Hydrodynamics::Corrector_summation(double dt)
{
  ///- iterate the real partilce list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    Particle *prtl = particle_list.retrieve(p);

    ///- for each particle: correction (advances R,U) based on values on n step and change rate at n+1/2
    prtl->U[X] += prtl->_dU[X];
    prtl->U[Y] += prtl->_dU[Y];
    
    prtl->R[X] = prtl->R_I[X] + prtl->U[X]*dt;
    prtl->R[Y] = prtl->R_I[Y] + prtl->U[Y]*dt;    
    
    prtl->U[X] = prtl->U_I[X] + prtl->dUdt[X]*dt;
    prtl->U[Y] = prtl->U_I[Y] + prtl->dUdt[Y]*dt;
  }
}
//----------------------------------------------------------------------------------------
//							including random effects
//----------------------------------------------------------------------------------------
void Hydrodynamics::RandomEffects()
{
  ///- iterate the real partilce list
  for (LlistNode<Particle> *p = particle_list.first();
       !particle_list.isEnd(p);
       p = particle_list.next(p)) {

    Particle *prtl = particle_list.retrieve(p);

    ///- for each particle: add random velocity _dU
    prtl->U[X] = prtl->U[X] + prtl->_dU[X];
    prtl->U[Y] = prtl->U[Y] + prtl->_dU[Y];    
  }
}
