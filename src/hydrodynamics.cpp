/// \file hydrodynamics.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      Define materials and their hydrodynamical interactions
//		hydrodynamics.cpp
//----------------------------------------------------------------------------------------

//#include <iostream>
#include <fstream>
//#include <string>

#include <stdio.h>
#include <string.h>


// ***** localincludes *****
#include "hydrodynamics.h"
#include "initiation.h"
#include "material.h"
#include "quinticspline.h"
#include "glbfunc.h"
#include "interactionstate.h"
#include "boundary.h"
#include "force.h"
#include "particle.h"
#include "particlemanager.h"

using namespace std;
///functions deifined in particle.cpp
extern void hydroMovingTest(const Llist<Node>& particle_list);
extern double hydroConservationTest(const Llist<Node>& particle_list);

//----------------------------------------------------------------------------------------
//						constructor
//----------------------------------------------------------------------------------------
Hydrodynamics::Hydrodynamics(ParticleManager &particles, Initiation* ini):
  number_of_materials(ini->number_of_materials),
  gravity(ini->g_force),
  smoothinglength(ini->smoothinglength),
  delta(ini->delta)
{
	
  int k, m;
  int l, n;
  
  //make materials
  char Key_word[25];
  char inputfile[25];
  
  //copy properties from initiation class
  //  number_of_materials = ini->number_of_materials;
  //  gravity = ini->g_force;
  //  smoothinglength = ini->smoothinglength;
  //delta = ini->delta; 
  delta2 = delta*delta; delta3 = delta2*delta;
  
  //creat material matrix
  Material sample_material(ini);  //set satatic numbers
  materials.assign(2, sample_material);
  //creat the force matrix
  Force sample_force(ini); //set satatic numbers
  forces = new Force*[number_of_materials];
  for(k = 0; k < number_of_materials; k++) forces[k] = new Force[number_of_materials];
  
  //check if inputfile exist
  strcpy(inputfile, ini->inputfile);
  ifstream fin(inputfile, ios::in);
  if (!fin) {
    cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
    exit(1);
  }
  else cout<<"\nMaterial: read the propeties of materials and interaction forces \n"; 
  
  //reading key words and configuration data
  while(!fin.eof()) {
    
    //read a string block
    fin>>Key_word;
    
    //comparing the key words for the materials 
    if(!strcmp(Key_word, "MATERIALS")) 
      //read all materials
      for(k = 0; k < number_of_materials; k++) {
	//the material number
	materials.at(k).number = k;
	fin>>materials.at(k).material_name>>materials.at(k).material_type;
	fin>>materials.at(k).cv>>materials.at(k).eta>>materials.at(k).zeta>>materials.at(k).kappa
	   >>materials.at(k).gamma>>materials.at(k).b0>>materials.at(k).rho0>>materials.at(k).a0;
	//output the material property parameters to the screen
	cout<<"The properties of the material No. "<<k<<"\n";		
	materials.at(k).show_properties();
	//non-dimensionalize
	materials.at(k).non_dimensionalize(ini);
      }
    
    //comparing the key words for the force matrix 
    if(!strcmp(Key_word, "FORCES")) 
      //read all materials
      for(l = 0; l < number_of_materials; l++) 
	for(n = 0; n < number_of_materials; n++) {
	  fin>>k>>m;
	  fin>>forces[k][m].epsilon>>forces[k][m].sigma
	     >>forces[k][m].shear_slip>>forces[k][m].bulk_slip
	     >>forces[k][m].heat_slip;
	  cerr << "forces[" << k << "]" << 
	    "[" << l << "].sigma = " << forces[k][m].sigma <<
	    endl;	  
	  //smoothinglenth
	  forces[k][m].smoothinglength = ini->smoothinglength;
	  forces[k][m].non_dimensionalize(ini);
	}
	}
  fin.close();
  
  //for time step and the artificial compressiblity
  viscosity_max = 0.0; surface_max = 0.0;
  for(k = 0; k < number_of_materials; k++) {
    viscosity_max = AMAX1(viscosity_max, materials[k].nu);
    for(l = 0; l < number_of_materials; l++) {
      surface_max = AMAX1(surface_max, forces[k][l].sigma);
    }
  }
  dt_g_vis = AMIN1(sqrt(delta/v_abs(gravity)), 0.5*delta2/viscosity_max);
  dt_surf = 0.4*sqrt(delta3/surface_max);
  
  //determine the artificial compressiblity
  double sound;
  //g force and viscosity
  cout << "viscosity_max = " << viscosity_max << '\n';
  sound = AMAX1(v_abs(ini->g_force), viscosity_max);
  //surface tension effects
  sound = AMAX1(surface_max, sound);
  cerr << "surface_max =" << surface_max << '\n';
  cerr << "sound = " << sound << '\n';
  for(k = 0; k < number_of_materials; k++) materials[k].Get_b0(sound);
  
  //biuld the real particles
  particles.BuildRealParticles(*this, ini);
  
}

//----------------------------------------------------------------------------------------
//						Build new pairs
//----------------------------------------------------------------------------------------
void Hydrodynamics::BuildPair(ParticleManager &particles, QuinticSpline &weight_function)
{
  //obtain the interaction pairs
  particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);
  
}
//----------------------------------------------------------------------------------------
//						update new parameters in pairs
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdatePair(QuinticSpline &weight_function)
{
  
  //iterate the interaction list
  for (LlistNode<InteractionState> *p = interaction_list.first(); 
       !interaction_list.isEnd(p); 
       p = interaction_list.next(p)) {
    
    //a interaction pair
    InteractionState *pair = interaction_list.retrieve(p);
    //renew pair parameters
    pair->RenewInteraction(weight_function);
  }
}
//----------------------------------------------------------------------------------------
//		summation for particles density and shear rates with updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateShearRate(ParticleManager &particles, QuinticSpline &weight_function)
{	
  
  //obtain the interaction pairs
  particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);
  
  //initiate zero shear rate
  Zero_ShearRate();
  //iterate the interaction list
  for (LlistNode<InteractionState> *p2 = interaction_list.first(); 
       !interaction_list.isEnd(p2); 
       p2 = interaction_list.next(p2)) {
    
    //a interaction pair
    InteractionState *pair = interaction_list.retrieve(p2);
    //calculate the pair forces or change rate
    pair->SummationShearRate();
  }
  
}
//----------------------------------------------------------------------------------------
//		summation for pahse field gradient
//----------------------------------------------------------------------------------------
// not independant with UpdateDensity
void Hydrodynamics::UpdatePhaseGradient(Boundary &boundary)
{
  //initiate zero shear rate
  Zero_PhaseGradient(boundary);
  //iterate the interaction list
  for (LlistNode<InteractionState> *p2 = interaction_list.first(); 
       !interaction_list.isEnd(p2); 
       p2 = interaction_list.next(p2)) {
    
    //a interaction pair
    InteractionState *pair = interaction_list.retrieve(p2);
    //calculate the pair forces or change rate
    pair->SummationPhaseGradient();
  }
}
//----------------------------------------------------------------------------------------
//		summation Phase Divergen
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdatePhaseLaplacian(Boundary &boundary)
{
  //initiate zero shear rate
  Zero_PhaseLaplacian(boundary);
  //iterate the interaction list
  for (LlistNode<InteractionState> *p2 = interaction_list.first(); 
       !interaction_list.isEnd(p2); 
       p2 = interaction_list.next(p2)) {
    
    //a interaction pair
    InteractionState *pair = interaction_list.retrieve(p2);
    //calculate the pair forces or change rate
    pair->SummationPhaseLaplacian();
  }
}
//----------------------------------------------------------------------------------------
//		summation for pahse field gradient
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdatePhaseField(Boundary &boundary)
{
  //initiate zero shear rate
  Zero_PhaseField(boundary);
  //iterate the interaction list
  for (LlistNode<InteractionState> *p2 = interaction_list.first(); 
       !interaction_list.isEnd(p2); 
       p2 = interaction_list.next(p2)) {
    
    //a interaction pair
    InteractionState *pair = interaction_list.retrieve(p2);
    //calculate the pair forces or change rate
    pair->SummationPhaseField();
    //			pair->SummationCurvature();
  }
}
//----------------------------------------------------------------------------------------
//		summation for particles density and shear rates with updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateDensity(ParticleManager &particles, QuinticSpline &weight_function)
{	

  //obtain the interaction pairs
  particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);
  
  //initiate zero density
  Zero_density();
  //iterate the interaction list
  for (LlistNode<InteractionState> *p1 = interaction_list.first(); 
       !interaction_list.isEnd(p1); 
       p1 = interaction_list.next(p1)) {
    
    //a interaction pair
    InteractionState *pair = interaction_list.retrieve(p1);
    //calculate the pair forces or change rate
    pair->SummationDensity();	
  }
  
  //calulate new pressure
  UpdateState();
}
//----------------------------------------------------------------------------------------
//		summation for particles density and shear rates without updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateShearRate()
{	
  //initiate zero shear rate
  Zero_ShearRate();
  //iterate the interaction list
  for (LlistNode<InteractionState> *p2 = interaction_list.first(); 
       !interaction_list.isEnd(p2); 
       p2 = interaction_list.next(p2)) {
		
    //a interaction pair
    InteractionState *pair = interaction_list.retrieve(p2);
    //calculate the pair forces or change rate
    pair->SummationShearRate();
  }
  
}
//----------------------------------------------------------------------------------------
//		summation for particles density and shear rates without updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateDensity()
{	
	//initiate zero density
	Zero_density();
	//iterate the interaction list
	for (LlistNode<InteractionState> *p1 = interaction_list.first(); 
		!interaction_list.isEnd(p1); 
		p1 = interaction_list.next(p1)) {
		
			//a interaction pair
			InteractionState *pair = interaction_list.retrieve(p1);
			//calculate the pair forces or change rate
			pair->SummationDensity();	
	}

	//calulate new pressure
	UpdateState();
}
//----------------------------------------------------------------------------------------
//				calculate interaction with updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateChangeRate(ParticleManager &particles, 
				     QuinticSpline &weight_function,
				     double dt)
{
	//initiate the density each real particle
	ZeroChangeRate(dt);

	//obtain the interaction pairs
	particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);

	//iterate the interaction list
	for (LlistNode<InteractionState> *p = interaction_list.first(); 
		!interaction_list.isEnd(p); 
		p = interaction_list.next(p)) {
		
			//a interaction pair
			InteractionState *pair = interaction_list.retrieve(p);
			//calculate the pair forces or change rate
			pair->UpdateForces();

	}

	//include the gravity effects
	AddGravity();
}
//----------------------------------------------------------------------------------------
//				calculate interaction without updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateChangeRate(double dt)
{
	//initiate the change rate of each real particle
	ZeroChangeRate(dt);	

#ifdef _OPENMP
#pragma omp parallel
{
	int current_thread = 0;
	int thread_num = omp_get_num_threads();
	int this_thread_num = omp_get_thread_num();
#endif
	//iterate the interaction list
	for (LlistNode<InteractionState> *p = interaction_list.first(); 
		!interaction_list.isEnd(p); 
		p = interaction_list.next(p)) {
		#ifdef _OPENMP
		if (current_thread == this_thread_num)
		#endif
			//a interaction pair
			//calculate the pair forces or change rate
			interaction_list.retrieve(p)->UpdateForces();
		#ifdef _OPENMP
		current_thread++;
		if (current_thread == thread_num)
			current_thread = 0;
		#endif
	}
#ifdef _OPENMP
}

	for (LlistNode<InteractionState> *p = interaction_list.first(); 
		!interaction_list.isEnd(p); 
		p = interaction_list.next(p)) {
		
			//a interaction pair
			InteractionState *pair = interaction_list.retrieve(p);
			//calculate the pair forces or change rate
			pair->SummationUpdateForces();

	}
#endif

	//include the gravity effects
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
	wiener.Ranils();

	//iterate the interaction list
	for (LlistNode<InteractionState> *p = interaction_list.first(); 
	     !interaction_list.isEnd(p); 
	     p = interaction_list.next(p)) {
	  
	  //a interaction pair
	  InteractionState *pair = interaction_list.retrieve(p);
	  //calculate the pair forces or change rate
	  //
	  //	  pair->RandomForces(wiener, sqrtdt);		
	  pair->RandomForces_Espanol(wiener, sqrtdt);
	}
	
}
//----------------------------------------------------------------------------------------
//						initiate particle change rate
//----------------------------------------------------------------------------------------
void Hydrodynamics::ZeroChangeRate(double dt)
{
	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//particle
			Node *prtl = particle_list.retrieve(p);

			//all densities and conservqtives
			prtl->setAlldToZero(dt);
			//prtl->dedt = 0.0;
			//prtl->drhodt = 0.0;
			//prtl->dUdt = 0.0;
			//prtl->_dU = 0.0;
	}
}
//----------------------------------------------------------------------------------------
//							initiate particle density to zero
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_density()
{
	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//particle
			Node *prtl = particle_list.retrieve(p);

			//all densities and conservqtives
			prtl->rho() = 0.0;
	}
}
//----------------------------------------------------------------------------------------
//						initiate shear rate to zero
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_ShearRate()
{
	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//particle
			Node *prtl = particle_list.retrieve(p);

			//all shear rate
			prtl->setShearRatetoZero();
			//(prtl->ShearRate_x) = 0.0;
			//(prtl->ShearRate_y) = 0.0;
	}
}
//----------------------------------------------------------------------------------------
//						initiate pahse gradient
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_PhaseGradient(Boundary &boundary)
{
	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//particle
			Node *prtl = particle_list.retrieve(p);

			//all phase gradient
			(prtl->del_phi()) = 0.0;
		}

	//iterate particles on the boundary particle list
	for (LlistNode<Node> *p1 = boundary.boundary_particle_list.first(); 
		!boundary.boundary_particle_list.isEnd(p1); 
		p1 = boundary.boundary_particle_list.next(p1)) {
					
			//particle
			Node *prtl = boundary.boundary_particle_list.retrieve(p1);

			//all phase gradient
			(prtl->del_phi()) = 0.0;
		}
}
//----------------------------------------------------------------------------------------
//						initiate pahse Laplacian 
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_PhaseLaplacian(Boundary &boundary)
{
	int i, j;

	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
	  //particle
	  Node *prtl = particle_list.retrieve(p);
	  
	  //all phase Laplacian
	  for(i = 0; i < number_of_materials; i++)
	    for(j = 0; j < number_of_materials; j++) prtl->setLapPhiToZero(i, j);
	}
	
	//iterate particles on the boundary particle list
	for (LlistNode<Node> *p1 = boundary.boundary_particle_list.first(); 
	     !boundary.boundary_particle_list.isEnd(p1); 
	     p1 = boundary.boundary_particle_list.next(p1)) {
	  
	  //particle
	  Node *prtl = boundary.boundary_particle_list.retrieve(p1);
	  
	  //all phase Laplacian
	  for(i = 0; i < number_of_materials; i++)
	    for(j = 0; j < number_of_materials; j++) prtl->setLapPhiToZero(i, j);
	}

}
//----------------------------------------------------------------------------------------
//						initiate pahse field
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_PhaseField(Boundary &boundary)
{
	int i, j;

	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//particle
			Node *prtl = particle_list.retrieve(p);

			//all phases
			for(i = 0; i < number_of_materials; i++)
			  for(j = 0; j < number_of_materials; j++) prtl->setPhiToZero(i, j);
	}

	//iterate particles on the boundary particle list
	for (LlistNode<Node> *p1 = boundary.boundary_particle_list.first(); 
		!boundary.boundary_particle_list.isEnd(p1); 
		p1 = boundary.boundary_particle_list.next(p1)) {
					
			//particle
			Node *prtl = boundary.boundary_particle_list.retrieve(p1);

			//all phases
			for(i = 0; i < number_of_materials; i++)
			  for(j = 0; j < number_of_materials; j++) prtl->setPhiToZero(i, j);
	}

}
//----------------------------------------------------------------------------------------
//					satic solution: set velocity to zero
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_Velocity()
{
	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//particle
			Node *prtl = particle_list.retrieve(p);

			//all random values
			prtl->setUtoZero();
			//			prtl->U() = 0.0;
	}
}
//----------------------------------------------------------------------------------------
//						initiate random force
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_Random()
{
	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//particle
			Node *prtl = particle_list.retrieve(p);

			//all random values
			prtl->setRandomUtoZero();
			//(prtl->_dU) = 0.0;
	}
}
//----------------------------------------------------------------------------------------
//							add the gravity effects
//----------------------------------------------------------------------------------------
void Hydrodynamics::AddGravity()
{
	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//a particle
			Node *prtl = particle_list.retrieve(p);

			//add the gravity effects
			prtl->increasedUdt(gravity);
			//prtl->dUdt = prtl->dUdt + gravity;
	}
}
//----------------------------------------------------------------------------------------
//							calculate states from conservatives
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateState()
{
	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//a particle
			Node *prtl = particle_list.retrieve(p);

			//states
			//prtl->p = prtl->mtl->get_p(prtl->rho);
			prtl->updatePressure();
//			prtl->T = prtl->mtl->get_T(prtl->e);
	}

}
//----------------------------------------------------------------------------------------
//							calculate phase filed matrix
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdatePahseMatrix(Boundary &boundary)
{
	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
	     !particle_list.isEnd(p); 
	     p = particle_list.next(p)) {
	  
	  //a particle
	  //Node *prtl = particle_list.retrieve(p);	  
	  //all phase surface stress
	  for(int i = 0; i < number_of_materials; i++)
	    for(int j = 0; j < number_of_materials; j++) {
	      //Fix:
	      //if( i != j) prtl->phi[i][j] = prtl->phi[i][j]; //prtl->phi[i][i]/(prtl->phi[i][i] + prtl->phi[j][j] + 1.0e-30);
	    }
	}
	
	//iterate particles on the boundary particle list
	for (LlistNode<Node> *p1 = boundary.boundary_particle_list.first(); 
		!boundary.boundary_particle_list.isEnd(p1); 
		p1 = boundary.boundary_particle_list.next(p1)) {
					
			//particle
			//Node *prtl = boundary.boundary_particle_list.retrieve(p1);

			//all phase surface stress
			for(int i = 0; i < number_of_materials; i++)
				for(int j = 0; j < number_of_materials; j++) {
				  //if( i != j) prtl->phi[i][j] = prtl->phi[i][j]; //prtl->phi[i][i]/(prtl->phi[i][i] + prtl->phi[j][j] + 1.0e-30);
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

	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//a particle
			Node *prtl = particle_list.retrieve(p);

			//all phase surface stress
			interm0 = 1.0/(v_abs(prtl->del_phi()) + epsilon);
			interm1 = 0.5*v_sqdiff(prtl->del_phi());
			interm2 = product(prtl->del_phi());
			prtl->del_phi()[0] = interm1*interm0;
			prtl->del_phi()[1] = interm2*interm0;
	}

	//iterate particles on the boundary particle list
	for (LlistNode<Node> *p1 = boundary.boundary_particle_list.first(); 
		!boundary.boundary_particle_list.isEnd(p1); 
		p1 = boundary.boundary_particle_list.next(p1)) {
					
			//particle
			Node *prtl = boundary.boundary_particle_list.retrieve(p1);

			//all phase surface stress
			interm0 = v_abs(prtl->del_phi()) + epsilon;
			interm1 = 0.5*v_sqdiff(prtl->del_phi());
			interm2 = product(prtl->del_phi());
			prtl->del_phi()[0] = interm1/interm0;
			prtl->del_phi()[1] = interm2/interm0;
	}
}
//----------------------------------------------------------------------------------------
//							Calculate Surface Tension Coefficient
//----------------------------------------------------------------------------------------

double Hydrodynamics::SurfaceTensionCoefficient()
{
	double coefficient = 0.0; double totalvolume = 0.0;

	//iterate particles on the real particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//a particle
			Node *prtl = particle_list.retrieve(p);

			//all phase surface stress
			double interm1 = prtl->getMass()/prtl->rho();
			totalvolume += interm1;
			coefficient += v_sq(prtl->del_phi())*interm1;
	}
	return coefficient/sqrt(totalvolume);
}
//----------------------------------------------------------------------------------------
//								calculate partilce volume
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateVolume(ParticleManager &particles, QuinticSpline &weight_function)
{
	double reciprocV; //the inverse of volume or volume

	//iterate particles on the particle list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
					
			//origin particle
			Node *prtl_org = particle_list.retrieve(p);
			//build the nearest particle list
			particles.BuildNNP(prtl_org->R());

			reciprocV = 0.0; 
			//iterate this Nearest Neighbor Particle list
			for (LlistNode<Node> *p1 = particles.NNP_list.first(); 
			!particles.NNP_list.isEnd(p1); 
			p1 = particles.NNP_list.next(p1)) {
			
				//get a particle
				Node *prtl_dest = particles.NNP_list.retrieve(p1);
				
				//summation the weights
				reciprocV += weight_function.w(v_distance(prtl_org->R(), prtl_dest->R()));
			}
			//calculate volume
			prtl_org->setVolume(1.0/reciprocV);
		
			//clear the NNP_list
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
  for (LlistNode<Node> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
    
    Node *prtl = particle_list.retrieve(p);
    Cs_max = AMAX1(Cs_max, prtl->getCs());
    V_max = AMAX1(V_max, v_abs(prtl->U()));
    rho_min = AMIN1(rho_min, prtl->rho());
    rho_max = AMAX1(rho_max, prtl->rho());
  }
  dt = AMIN1(sqrt(0.5*(rho_min + rho_max))*dt_surf, dt_g_vis);
  
//   cout << "V_max = " << V_max << endl;
//   cout << "Cs_max = " << Cs_max << endl;
//   cout << "dt_g_vis = " << dt_g_vis << '\n' << endl;
  
  //return  0.25*AMIN1(dt, delta/(Cs_max + V_max));
  //Fix::
  Initiation* ini = Initiation::Instance();
  return  0.25*AMIN1(dt, delta/(Cs_max + V_max)) * ini->timestep_co;
}
//----------------------------------------------------------------------------------------
//						the redictor and corrector method: predictor
//----------------------------------------------------------------------------------------
void Hydrodynamics::Predictor(double dt)
{
	//iterate the real partilce list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {
		
			Node *prtl = particle_list.retrieve(p);
	
			prtl->saveRRU();

			//predict values at step n+1
// 			prtl->R() = prtl->R() + prtl->U*dt;
// 			prtl->rho = prtl->rho + prtl->drhodt*dt;
// 			prtl->U = prtl->U + prtl->dUdt*dt;

			prtl->setMiddleRRU();			
// 			//calculate the middle values at step n+1/2
// 			prtl->R() = (prtl->R() + prtl->R_I)*0.5;
// 			prtl->rho = (prtl->rho + prtl->rho_I)*0.5;
// 			prtl->U = (prtl->U + prtl->U_I)*0.5;

	}
}
//----------------------------------------------------------------------------------------
//							the redictor and corrector method: predictor
//----------------------------------------------------------------------------------------
void Hydrodynamics::Corrector(double dt)
{
	//iterate the real partilce list
	for (LlistNode<Node> *p = particle_list.first(); 
	     !particle_list.isEnd(p); 
	     p = particle_list.next(p)) {
	  
	  Node *prtl = particle_list.retrieve(p);
	  
	  //correction base on values on n step and change rate at n+1/2
	  prtl->correctRRU(dt);

// 	  prtl->R() = prtl->R_I + prtl->U*dt;
// 	  prtl->rho = prtl->rho + prtl->drhodt*dt;
// 	  prtl->U = prtl->U_I + prtl->dUdt*dt;
	}
}
//----------------------------------------------------------------------------------------
//					the predictor and corrector method: predictor, no density updating
//----------------------------------------------------------------------------------------
void Hydrodynamics::Predictor_summation(double dt)
{
  //iterate the real partilce list
  for (LlistNode<Node> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) 
    {    
      Node *prtl = particle_list.retrieve(p);
      prtl->predictorSummationStep(dt);
      //     //save values at step n
      //     prtl->R_I = prtl->R();
      //     prtl->U += prtl->_dU; //renormalize velocity
      //     prtl->U_I = prtl->U;
      
      //     //predict values at step n+1
      //     prtl->R() = prtl->R() + prtl->U*dt;
      //     prtl->U = prtl->U + prtl->dUdt*dt;
      
      //     //calculate the middle values at step n+1/2
      //     prtl->R() = (prtl->R() + prtl->R_I)*0.5;
      //     prtl->U = (prtl->U + prtl->U_I)*0.5;
    }
}
//----------------------------------------------------------------------------------------
//			the predictor and corrector method: predictor, no density updating
//----------------------------------------------------------------------------------------
void Hydrodynamics::Corrector_summation(double dt)
{
	//iterate the real partilce list
	for (LlistNode<Node> *p = particle_list.first(); 
		!particle_list.isEnd(p); 
		p = particle_list.next(p)) {	
	  Node *prtl = particle_list.retrieve(p);			
	  prtl->correctorSummationStep(dt);
	  //correction base on values on n step and change rate at n+1/2
	  //prtl->U += prtl->_dU; //renormalize velocity
	  //prtl->R() = prtl->R_I + prtl->U*dt;
	  //prtl->U = prtl->U_I + prtl->dUdt*dt;
	}
}
//----------------------------------------------------------------------------------------
//							including random effects
//----------------------------------------------------------------------------------------
void Hydrodynamics::RandomEffects()
{
  //iterate the real partilce list
  for (LlistNode<Node> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {  
    Node *prtl = particle_list.retrieve(p);
    
	  //correction base on values on n step and change rate at n+1/2
    prtl->correctU();
    //	  prtl->U = prtl->U + prtl->_dU;
  }
}
//----------------------------------------------------------------------------------------
//					test assign random particle velocity, no density updating
//----------------------------------------------------------------------------------------
void Hydrodynamics::MovingTest() const
{
	//a random double between 0.0 and 1.0
// 	Vec2d test_v;
// 	double f_rdmx = (float)RAND_MAX;
	
// 	//iterate the partilce list
// 	for (LlistNode<Node> *p = particle_list.first(); 
// 	     !particle_list.isEnd(p); 
// 	     p = particle_list.next(p)) {
	  
// 	  Node *prtl = particle_list.retrieve(p);
// 	  if(prtl->getbd() == 0) {
// 	    prtl->U_I = prtl->U;
// 	    prtl->U =  prtl->U + prtl->U*0.1*((float)rand() - f_rdmx / 2.0) / f_rdmx;
// 	  }
// 	}
  ///moving test

  hydroMovingTest(particle_list);
}

//----------------------------------------------------------------------------------------
//								test the conservation properties
//----------------------------------------------------------------------------------------
double Hydrodynamics::ConservationTest() const
{
  //Vec2d sdU, sU, U;
	
	//iterate the partilce list
// 	for (LlistNode<Node> *p = particle_list.first(); 
// 		!particle_list.isEnd(p); 
// 		p = particle_list.next(p)) {
	
// 			Node *prtl = particle_list.retrieve(p);
// 				sU = sU + prtl->dUdt;
// 				sdU = sdU + prtl->_dU;
// 				U = U + prtl->U;
// 	}

// 	return v_abs(U);

  //the function hydroConservationTest is a friend of Particle type
  return(hydroConservationTest(particle_list));
}


const Llist<InteractionState>* Hydrodynamics::getInteractionList() const {
  return &interaction_list;
}
