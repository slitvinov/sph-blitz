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

#include <cstdio>
#include <cstdlib>

// ***** localincludes *****
#include "glbcls.h"
#include "glbfunc.h"
#include "material.h"
#include "Kernel/kernel.h"

using namespace std;

//----------------------------------------------------------------------------------------
//						constructor
//----------------------------------------------------------------------------------------
Hydrodynamics::Hydrodynamics(ParticleManager &particles, Initiation &ini) {
	
  int k, m;
  int l, n;

  //make materials
  char Key_word[25];
  char inputfile[25];

  ///<ul><li>copy properties from initiation class
  number_of_materials = ini.number_of_materials;
  gravity = ini.g_force;
  supportlength = ini.supportlength;
  simu_mode=ini.simu_mode;
  delta = ini.delta; delta2 = delta*delta; delta3 = delta2*delta;

  ///<li>create material matrix
  Material sample_material(ini);  //set satatic numbers
  materials = new Material[number_of_materials];
  ///<li>create the force matrix
  Force sample_force(ini); //set satatic numbers
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
	fin>>materials[k].cv>>materials[k].eta>>materials[k].zeta>>materials[k].kappa
	   >>materials[k].gamma>>materials[k].b0>>materials[k].rho0>>materials[k].a0;
	///<li>output the material property parameters to the screen
	cout<<"The properties of the material No. "<<k<<"\n";		
	materials[k].show_properties();
	///<li>non-dimensionalize</ul>
	materials[k].non_dimensionalize(ini);
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
	     >>forces[k][m].shear_slip>>forces[k][m].bulk_slip
	     >>forces[k][m].heat_slip;
	  ///<li>copy smoothing length fro initiation
	  forces[k][m].supportlength = ini.supportlength;
	  ///<li>and non-dimensionalize</ul>
	  forces[k][m].non_dimensionalize(ini);
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
  dt_g_vis = AMIN1(sqrt(delta/v_abs(gravity)), 0.5*delta2/viscosity_max);
  dt_surf = 0.4*sqrt(delta3/surface_max);

  ///<li>determine the artificial compressiblity
  double sound;
  //g force and viscosity
  sound = AMAX1(v_abs(ini.g_force), viscosity_max);
  //surface tension effects
  sound = AMAX1(surface_max, sound);
  for(k = 0; k < number_of_materials; k++) materials[k].Set_b0(sound);

  ///<li>biuld the real particles
  particles.BiuldRealParticles(*this, ini);

}

//----------------------------------------------------------------------------------------
//						Build new pairs
//----------------------------------------------------------------------------------------
void Hydrodynamics::BuildPair(ParticleManager &particles, Kernel &weight_function)
{
  ///- obtain the interaction pairs by just calling the particles BuildInteraction method
  particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);
  cout<<"\n BuildPair done\n";
}
//----------------------------------------------------------------------------------------
//						update new parameters in pairs
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdatePair(Kernel &weight_function)
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
//		summation for shear rates with updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateShearRate(ParticleManager &particles, Kernel &weight_function)
{	

  ///- obtain the interaction pairs
  particles.BuildInteraction(interaction_list, particle_list, forces, weight_function);
	
  ///- initiate by calling  Zero_ShearRate Method
  Zero_ShearRate();
  ///- iterate the interaction list
  for (LlistNode<Interaction> *p2 = interaction_list.first(); 
       !interaction_list.isEnd(p2); 
       p2 = interaction_list.next(p2)) {
		
    //a interaction pair
    Interaction *pair = interaction_list.retrieve(p2);
    ///- calculate for each pair the pair forces or change rate
    pair->SummationShearRate();
  }

}
//----------------------------------------------------------------------------------------
//		summation for particles density with updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateDensity(ParticleManager &particles, Kernel &weight_function, Initiation &ini)
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
  UpdateState(ini);
}
//----------------------------------------------------------------------------------------
//		summation for shear rates without updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateShearRate()
{	
  ///- initiate by calling Zero_ShearRate(
  Zero_ShearRate();
  ///- iterate the interaction list
  for (LlistNode<Interaction> *p2 = interaction_list.first(); 
       !interaction_list.isEnd(p2); 
       p2 = interaction_list.next(p2)) {
		
    //a interaction pair
    Interaction *pair = interaction_list.retrieve(p2);
    ///- calculate for each pair the pair forces or change rate
    pair->SummationShearRate();
  }

}
//----------------------------------------------------------------------------------------
//		summation for particles density without updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateDensity(Initiation &ini)
{	
  ///- initiate zero density
  cout<<"\n AM in update density\n ";
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
  UpdateState(ini);
}
//----------------------------------------------------------------------------------------
//				calculate interaction with updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateChangeRate(ParticleManager &particles, Kernel &weight_function)
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

#ifdef _OPENMP
#pragma omp parallel
  {
    int current_thread = 0;
    int thread_num = omp_get_num_threads();
    int this_thread_num = omp_get_thread_num();
#endif
    ///- iterate the interaction list
    for (LlistNode<Interaction> *p = interaction_list.first(); 
	 !interaction_list.isEnd(p); 
	 p = interaction_list.next(p)) {
#ifdef _OPENMP
      if (current_thread == this_thread_num)
#endif
	//a interaction pair
	///- calculate for each pair the pair forces or change rate
	interaction_list.retrieve(p)->UpdateForces();
#ifdef _OPENMP
      current_thread++;
      if (current_thread == thread_num)
	current_thread = 0;
#endif
    }
#ifdef _OPENMP
  }

  for (LlistNode<Interaction> *p = interaction_list.first(); 
       !interaction_list.isEnd(p); 
       p = interaction_list.next(p)) {
		
    //a interaction pair
    Interaction *pair = interaction_list.retrieve(p);
    //calculate the pair forces or change rate
    pair->SummationUpdateForces();

  }
#endif
  //control output
  int q=0;
for (LlistNode<Particle> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {

					
    //particle
    Particle *prtl = particle_list.retrieve(p);
    if(q%30==0)  
  cout<<"\n dUdt0"<<prtl->dUdt[0]<<"dUdt1"<<prtl->dUdt[1];
    q++;
   
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
    pair->RandomForces(wiener, sqrtdt);		
  }
	
}
//----------------------------------------------------------------------------------------
//						initiate particle change rate
//----------------------------------------------------------------------------------------
void Hydrodynamics::ZeroChangeRate()
{
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
					
    //particle
    Particle *prtl = particle_list.retrieve(p);

    ///- set for each particle change rates to zero
    prtl->dedt = 0.0;
    prtl->drhodt = 0.0;
    (prtl->dUdt) = 0.0;
    (prtl->_dU) = 0.0;

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
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
					
    //particle
    Particle *prtl = particle_list.retrieve(p);

    ///- set ShearRate to zero for each particle
    (prtl->ShearRate_x) = 0.0;
    (prtl->ShearRate_y) = 0.0;
  }
}
//----------------------------------------------------------------------------------------
//					static solution: set velocity to zero
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_Velocity()
{
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
					
    //particle
    Particle *prtl = particle_list.retrieve(p);

    ///- all velocities to zero
    (prtl->U) = 0.0;
  }
}
//----------------------------------------------------------------------------------------
//						initiate random force
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_Random()
{
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
					
    //particle
    Particle *prtl = particle_list.retrieve(p);

    ///- all random values to zero (so, _dU is random value???)
    (prtl->_dU) = 0.0;
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

    ///- to each particles dUdt: add the gravity effects
    prtl->dUdt = prtl->dUdt + gravity;
  }
}
//----------------------------------------------------------------------------------------
//							calculate states from conservatives
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateState(Initiation &ini)
{
  ///- iterate particles on the real particle list
  for (LlistNode<Particle> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
					
    //a particle
    Particle *prtl = particle_list.retrieve(p);

    ///- calculate pressure for each particle
    if(ini.simu_mode==1)  //liquid mode equation of state
      prtl->p = prtl->mtl->get_p(prtl->rho);
    if(ini.simu_mode==2)//gas dynamics mode equation of state
      {
	prtl->p = prtl->mtl->get_p(prtl->rho,prtl->e);
	prtl->Cs = prtl->mtl->get_Cs(prtl->p, prtl->rho);
      }
    //calculate temperature for each particle
    prtl->T = prtl->mtl->get_T(prtl->e);
  }

}
//----------------------------------------------------------------------------------------
//								calculate partilce volume
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateVolume(ParticleManager &particles, Kernel &weight_function)
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
      reciprocV += weight_function.w(v_distance(prtl_org->R, prtl_dest->R));
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
    V_max = AMAX1(V_max, v_abs(prtl->U));
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
    prtl->R_I = prtl->R;
    prtl->rho_I = prtl->rho;
    prtl->U_I = prtl->U;
    prtl->e_I = prtl->e;
			
    ///<li>predict values at step n+1
    prtl->R = prtl->R + prtl->U*dt;
    prtl->rho = prtl->rho + prtl->drhodt*dt;
    prtl->U = prtl->U + prtl->dUdt*dt;
    prtl->e = prtl->e + prtl->dedt*dt;
			
    ///<li>calculate the middle values at step n+1/2</ul></ul>
    prtl->R = (prtl->R + prtl->R_I)*0.5;
    prtl->rho = (prtl->rho + prtl->rho_I)*0.5;
    prtl->U = (prtl->U + prtl->U_I)*0.5;
    prtl->e=(prtl->e + prtl->e_I)*0.5;
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
    prtl->R = prtl->R_I + prtl->U*dt;
    prtl->rho = prtl->rho + prtl->drhodt*dt;
    prtl->U = prtl->U_I + prtl->dUdt*dt;
    prtl->e = prtl->e_I + prtl->dedt*dt;
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
    prtl->R_I = prtl->R;
    prtl->U += prtl->_dU; //renormalize velocity
    prtl->U_I = prtl->U;
    prtl->e_I = prtl->e;
			
    ///<li>predict values at step n+1
    prtl->R = prtl->R + prtl->U*dt;
    prtl->U = prtl->U + prtl->dUdt*dt;
    prtl->e = prtl->e + prtl->dedt*dt;
			
    ///<li>calculate the middle values at step n+1/2 and save them in Particle objects prtl</ul></ul>
    prtl->R = (prtl->R + prtl->R_I)*0.5;
    prtl->U = (prtl->U + prtl->U_I)*0.5;
    prtl->e = (prtl->e + prtl->e_I)*0.5;
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

    if(simu_mode==1)
    prtl->U += prtl->_dU; //renormalize velocity
  
    prtl->R = prtl->R_I + prtl->U*dt;
    prtl->U = prtl->U_I + prtl->dUdt*dt;
    prtl->e = prtl->e_I + prtl->dedt*dt;

   
  }
  //control output
ofstream tx2tFile("changeRatesN1");
		if (tx2tFile.is_open())
		{

		
 for (LlistNode<Particle> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
	
    Particle *prtl = particle_list.retrieve(p);
  
    tx2tFile<<"\n R_x: "<<prtl->R[0]<<"  U_x: "<<prtl->U[0]<<"  e: "<<prtl->e<<"  dUdt: "<<prtl->dUdt[0]<<" dedt "<<prtl->dedt<<"  ID  "<<prtl->ID<<"\n";
    
 } 

	tx2tFile.close();
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
    prtl->U = prtl->U + prtl->_dU;
  }
}
//----------------------------------------------------------------------------------------
//					test assign random particle velocity, no density updating
//----------------------------------------------------------------------------------------
void Hydrodynamics::MovingTest()
{
  //a random double between 0.0 and 1.0
  Vec2d test_v;
  double f_rdmx = (float)RAND_MAX;
	
  //iterate the partilce list
  for (LlistNode<Particle> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
	
    Particle *prtl = particle_list.retrieve(p);
    if(prtl->bd == 0) {
      prtl->U_I = prtl->U;
      prtl->U =  prtl->U + prtl->U*0.1*((float)rand() - f_rdmx / 2.0) / f_rdmx;
    }
  }
}
//----------------------------------------------------------------------------------------
//								test the conservation properties
//----------------------------------------------------------------------------------------
double Hydrodynamics::ConservationTest()
{
  Vec2d sdU = 0.0;
  Vec2d sU = 0.0;
  Vec2d U = 0.0; 
  //iterate the partilce list
  for (LlistNode<Particle> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
    const Particle *prtl = particle_list.retrieve(p);
    sU = sU + prtl->dUdt;
    sdU = sdU + prtl->_dU;
    U = U + prtl->U;
  }

  return v_abs(U);
}
