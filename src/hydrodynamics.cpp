/// \file hydrodynamics.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>

//-----------------------------------------------------------------------------------
//      Define materials and their hydrodynamical interactions
//		hydrodynamics.cpp
//-----------------------------------------------------------------------------------
#include "hydrodynamics.h"
#include <fstream>
#include <list>
#include <glog/logging.h>
#include <boost/foreach.hpp>
#include <boost/smart_ptr/make_shared.hpp>
// ***** localincludes *****
#include "glbfunc.h"
#include "Kernel/kernel.h"
#include "particlemanager.h"
#include "interaction.h"
#include "initiation.h"
using namespace std;

Hydrodynamics::Hydrodynamics(ParticleManager &particles, Initiation &ini) {
  LOG(INFO) << "Run constructor of Hydrodynamics class";
  /// <ul><li>copy properties from initiation class
  /// <li>create material matrix
  assert(ini.number_of_materials > 0);
  materials.resize(ini.number_of_materials);
  /// <li>if  key word material: read all materials (from .cfg file)
  for (int k = 0; k < ini.number_of_materials; k++) {
    // the material number
    /// <ul><li>save each one of them in materials matrix
    /// create a new Material object
    materials[k] = spMaterial(new Material(ini, k));
    materials[k]->show_properties();
  }
  LOG(INFO) << "Materials are ready";
  /// <li>initialize parameters for time step and the artificial compressiblity
  double viscosity_max = 0.0;
  for (int k = 0; k < ini.number_of_materials; k++) {
    viscosity_max = AMAX1(viscosity_max, materials[k]->nu);
  }

  /// <li>determine the artificial compressiblity
  const double sound = AMAX1(v_abs(ini.g_force), viscosity_max);
  LOG(INFO) << "sound speed is ready: " << sound;
  for(int k = 0; k < ini.number_of_materials; k++) {
    materials[k]->Set_b0(sound);
  }
  LOG(INFO) << "update of b0 is finished";

  ///<li>biuld the real particles
  // particles.BuildRealParticle(materials, particle_list, ini);
particles.BuildRealParticleGasDyn(materials, particle_list, ini);
  LOG(INFO) << "Hydrodynamics object is created";
}

//----------------------------------------------------------------------------------------
//						Build new interactions
//----------------------------------------------------------------------------------------
void Hydrodynamics::BuildInteractions(ParticleManager &particles, 
				      spKernel weight_function,
				      const Initiation& ini) {
  ///- obtain the interaction pairs by just calling the particles BuildInteraction method
  particles.BuildInteraction(interaction_list, particle_list, weight_function, ini);
  LOG(INFO) << " BuildInteraction done";
  LOG(INFO) << "size of interaction_list: " << interaction_list.size();
}
//----------------------------------------------------------------------------------------
// update new parameters in pairs interaction_list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateInteractions(spKernel weight_function) {
  LOG(INFO) << "Hydrodynamics::UpdateInteractions";
  ///- iterate the interaction list
  BOOST_FOREACH(spInteraction pair, interaction_list) {
    //renew pair parameters
    pair->RenewInteraction(weight_function);
  }
}

//----------------------------------------------------------------------------------------
//		summation for particles density with updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateDensity(ParticleManager &particles, 
				  spKernel weight_function, 
				  const Initiation &ini) {
  ///- obtain the interaction pairs
  particles.BuildInteraction(interaction_list, particle_list, weight_function, ini);
  ///- initiate by calling Zero_density method
  Self_density(weight_function);
  ///- iterate the interaction list
  BOOST_FOREACH(spInteraction pair, interaction_list) {
    pair->SummationDensity();	
  };

  LOG(INFO)<<"density after smoothing";

  BOOST_FOREACH(spParticle prtl, particle_list){
    LOG(INFO) << setprecision (20)<<::setw( 7 )<<prtl->ID<< ::setw( 25 )<<prtl->rho<<::setw( 7 )<<endl;
  }
		
  ///- calulate new pressure by calling UpdateState() Method
  UpdateState(ini);
}

//----------------------------------------------------------------------------------------
//		summation for particles density without updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateDensity(const Initiation &ini, spKernel  weight_function) {
  ///- initiate zero density
  LOG(INFO)<<"Hydrodynamics::UpdateDensity";
  Self_density(weight_function);
  ///- iterate the interaction list
  BOOST_FOREACH(spInteraction pair, interaction_list) {
    pair->SummationDensity();	
  }
  LOG(INFO)<<"density after smoothing";

  BOOST_FOREACH(spParticle prtl, particle_list){
    LOG_EVERY_N(INFO,10000) << setprecision (9)<<prtl->ID<<"    "<<prtl->rho<<endl;
  }

  ///- calulate new pressure by calling UpdateState()
  UpdateState(ini);
}
//----------------------------------------------------------------------------------------
//				calculate interaction with updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateChangeRate(ParticleManager &particles, spKernel weight_function, 
				     const Initiation& ini) {
  LOG(INFO) << " Hydrodynamics::UpdateChangeRate(particles, weight_function, ini)";
  ///- initiate change rate of each real particle by calling ZerpChangeRate()
  ZeroChangeRate();

  ///- obtain the interaction pairs
  particles.BuildInteraction(interaction_list, particle_list, weight_function, ini);

  ///- iterate the interaction list
  BOOST_FOREACH(spInteraction pair, interaction_list) {
    ///- calculate for eahc pair the pair forces or change rate
    pair->UpdateForces();
  }
  
  ///- include the gravity effects by calling AddGravity()
  AddGravity(ini);
}
//----------------------------------------------------------------------------------------
//				calculate interaction without updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateChangeRate(const Initiation& ini) {
  LOG(INFO) << " Hydrodynamics::UpdateChangeRate(ini)";
  ///- initiate the change rate of each real particle by calling ZeroChangeRate()
  ZeroChangeRate();	

  if(ini.pure_conduction==1)// only heat conduction, no particle movement
    ///- iterate the interaction list
    BOOST_FOREACH(spInteraction aux_interaction, interaction_list) {
      aux_interaction->UpdateEnergyPureConduction();
    }
  else //update velocity change rates etc.  as well...
    BOOST_FOREACH(spInteraction aux_interaction, interaction_list) {
      aux_interaction->UpdateForces();
    }
  //control output
  BOOST_FOREACH(spParticle prtl, particle_list) {
    LOG_EVERY_N(INFO, 1000) <<"dUdt: "<<prtl->dUdt[0] << " dUdt1: "<<prtl->dUdt[1];
  }
    
  // ofstream tx2tFile("DerivativesDataN1");
  // 	if (tx2tFile.is_open())
  //         {
  //         BOOST_FOREACH(spParticle prtl, particle_list) {
  
  // 	  tx2tFile <<setprecision (9)<< ::setw( 5 )<<prtl->ID<< ::setw(20)<<prtl->dUdt[0]<<::setw(20)<<prtl->dUdt[1]<<::setw(20)<<prtl->dedt<<endl;
  
  // 	  }
  // 	tx2tFile.close();
  // 	}
  // 		else cout << "Unable to open/create file";
  
  
  ///- include the gravity effects
  AddGravity(ini);
}
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateChangeRateInclRho(const Initiation& ini) {
  LOG(INFO) << " Hydrodynamics::UpdateChangeRateInclRho(ini)";
  ///- initiate the change rate of each real particle by calling ZeroChangeRate()
  ZeroChangeRate();	

    ///- iterate the interaction list
  BOOST_FOREACH(spInteraction aux_interaction, interaction_list) {
      aux_interaction->UpdateForcesAndRho();
  }
  //control output
  BOOST_FOREACH(spParticle prtl, particle_list) {
    LOG_EVERY_N(INFO, 1000) <<"dUdt: "<<prtl->dUdt[0] << " dUdt1: "<<prtl->dUdt[1];
  }

  ///- include the gravity effects
  AddGravity(ini);
}
//						initiate particle change rate
//----------------------------------------------------------------------------------------
void Hydrodynamics::ZeroChangeRate() {
  ///- iterate particles on the real particle list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ///- set for each particle change rates to zero
    prtl->dedt = 0.0;
    prtl->drhodt = 0.0;
    (prtl->dUdt) = 0.0;

  }
}
//----------------------------------------------------------------------------------------
//							initiate particle density to zero
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_density() {
  ///- iterate particles on the real particle list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ///- set for each particle density to zero
    prtl->rho = 0.0;
  }
}

/// initiate particle density to the contributions of the 
/// particle itself
void Hydrodynamics::Self_density(spKernel  weight_function) {
  ///- iterate particles on the real particle list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    prtl->rho = weight_function->w(0.0) * prtl->m;
  }
}


//----------------------------------------------------------------------------------------
//					static solution: set velocity to zero
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_Velocity() {
  ///- iterate particles on the real particle list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ///- all velocities to zero
    prtl->U = 0.0;
  }
}

//----------------------------------------------------------------------------------------
//					 set mue_ab_max to zero
//----------------------------------------------------------------------------------------
void Hydrodynamics::Zero_mue_ab_max() {
  ///- iterate particles on the real particle list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ///- all velocities to zero
    prtl->mue_ab_max = 0.0;
  }
}

//----------------------------------------------------------------------------------------
//							add the gravity effects
//----------------------------------------------------------------------------------------
void Hydrodynamics::AddGravity(const Initiation &ini) {
  LOG(INFO) << "Hydrodynamics::AddGravity starts";
  LOG(INFO) << "ini.gravity = " << ini.g_force;
  ///- iterate particles on the real particle list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ///- to each particles dUdt: add the gravity effects
    prtl->dUdt = prtl->dUdt + ini.g_force;
  }
}
//----------------------------------------------------------------------------------------
//							calculate states from conservatives
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateState(const Initiation &ini) {
  LOG(INFO) << "Hydrodynamics::UpdateState()";
  ///- iterate particles on the real particle list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ///- calculate pressure for each particle
    if(ini.simu_mode==1)  //liquid mode equation of state
      prtl->p = prtl->mtl->get_p(prtl->rho);
    if(ini.simu_mode==2)//gas dynamics mode equation of state
      {
	prtl->p = prtl->mtl->get_p(prtl->rho,prtl->e);
	//	prtl->Cs = prtl->mtl->get_Cs(prtl->p, prtl->rho);
      }
    //calculate temperature for each particle
    prtl->T = prtl->mtl->get_T(prtl->e);
  }

}
//----------------------------------------------------------------------------------------
//								calculate partilce volume
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateVolume(ParticleManager &particles, spKernel weight_function) {
  double reciprocV; //the inverse of volume or volume
  ///<ul><li> iterate particles on the particle list
  BOOST_FOREACH(spParticle prtl_org, particle_list) {
    //<li>build the nearest particle list
    const std::list<spParticle> NNP_list = particles.BuildNNP(prtl_org->R);
    reciprocV = 0.0; 
    //<li>iterate this Nearest Neighbor spParticle list
    BOOST_FOREACH(spParticle prtl_dest ,NNP_list) {
      ///<ul><li>sum the weights for all of these particles (because they are the inverse of a volume!)</ul>
      reciprocV += weight_function->w(v_distance(prtl_org->R, prtl_dest->R));
    }
    ///<li>calculate volume
    prtl_org->V = 1.0/reciprocV;
		
    ///<li>clear the NNP_list</ul></ul>
  }

}


//----------------------------------------------------------------------------------------
//							get the time step (gasdynamics)
//----------------------------------------------------------------------------------------

double Hydrodynamics::GetTimestepGas(const Initiation& ini) {
  
  double dt_f=1.0e30;//time step due to force consideration 
  double dt_cv=1.0e30;//time step due to Courant and (artificial) Viscosity consideration (viscous diffusion)
  double dt_v_real=1.0e30;//time step due physical viscosity (viscous diffusion)
  double dt_therm=1.0e30;// time step due to thermal conduction
  double beta_therm=0.1;// factor for dt_therm (see Cleary1999)
  
  //predict the time step
  //iterate the partilce list, calculate theoretical max admissible time step
  //for each particle and retain the smallest of all
  BOOST_FOREACH(spParticle prtl, particle_list) {
    assert(prtl != NULL);
    //dt_f according to Monaghan 1992 ("smoothed particle hydrodynamics") (sec.10.3)
    dt_f=AMIN1(dt_f, sqrt(ini.supportlength/2/(v_abs(prtl->dUdt)+1e-35)));//to prevent singularity
    //dt_cv according to Monaghan 1992 ("smoothed particle hydrodynamics") (sec.10.3)
    dt_cv=AMIN1(dt_cv,ini.supportlength/2/(prtl->Cs+0.6*(ini.alpha_artVis*prtl->Cs+ini.beta_artVis*prtl->mue_ab_max)));
    assert(dt_cv>0.0);
    // dt_v_real according to HuAdams2007 (and Litvinov2010: "A splitting scheme for highly dissipative smoothed particle dynamics")
    dt_v_real=AMIN1(dt_v_real,0.25*pow(ini.supportlength/2,2)/(prtl->eta+1e-35));
    assert(dt_v_real>0.0);
    // dt_therm according to Cleary1999 
    dt_therm=AMIN1(dt_therm,beta_therm*prtl->rho*prtl->cv*pow(ini.supportlength/2,2)/(prtl->k+1e-35));
    assert(dt_therm>0.0);
  }
  
  // reset mue_ab to zero (for next iteration)
  Zero_mue_ab_max();
  
  //find globally minimal admissible time step
  double dt;
  if(ini.pure_conduction==1)//if pure conduction problem (without prtl. mouvement)
    dt=dt_therm;
  else// if flow problem (including particle mouvement etc...)
    dt = AMIN1(0.25*dt_f, 0.25*dt_cv,dt_v_real,dt_therm);
  
  assert(dt>0.0);
  LOG(INFO) << "dt: " << dt; 
  return dt;
}


//----------------------------------------------------------------------------------------
//							get the time step (hydro)
//----------------------------------------------------------------------------------------
double Hydrodynamics::GetTimestep(const Initiation& ini) const {
  //maximum sound speed, particle velocity and density
  double Cs_max = 0.0, V_max = 0.0, rho_min = 1.0e30, rho_max = -1.0;

  //predict the time step
  //iterate the partilce list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    assert(prtl != NULL);
    Cs_max = AMAX1(Cs_max, prtl->Cs);
    V_max = AMAX1(V_max, v_abs(prtl->U));
    rho_min = AMIN1(rho_min, prtl->rho);
    rho_max = AMAX1(rho_max, prtl->rho);
  }

  ///<li>initialize parameters for time step and the artificial compressiblity
  double viscosity_max = 0.0; 
  for(int k = 0; k < ini.number_of_materials; k++) {
    viscosity_max = AMAX1(viscosity_max, materials[k]->nu);
  }
  LOG(INFO) << "viscosity_max is ready";

  const Vec2d gravity = ini.g_force;
  const double dt_g_vis = 
    AMIN1(sqrt(ini.delta/v_abs(gravity)), 0.5*ini.delta*ini.delta/viscosity_max);

  assert(dt_g_vis>0.0);
  LOG(INFO) << "dt_g_vis: " << dt_g_vis;

  const double dt = 0.25*AMIN1(dt_g_vis, ini.delta/(Cs_max + V_max));
  assert(dt>0.0);
  /// \todo{verify automatic calculation of time step} 
  return 0.5*dt;
}
//----------------------------------------------------------------------------------------
//						the redictor and corrector method: predictor
//----------------------------------------------------------------------------------------
void Hydrodynamics::Predictor(const double dt) {
  ///<ul><li> iterate the real partilce list
  BOOST_FOREACH(spParticle prtl, particle_list) {
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
void Hydrodynamics::Corrector(const double dt) {
  ///- iterate the real partilce list
  BOOST_FOREACH(spParticle prtl, particle_list) {
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
void Hydrodynamics::Predictor_summation(const double dt) {
  ///<ul><li>iterate the real partilce list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ///<ul><li>save values (R,U)  at step n in intermediate variables ._I
    prtl->R_I = prtl->R;
    prtl->U_I = prtl->U;
    prtl->e_I = prtl->e;
			
    ///<li>predict values at step n+1
    prtl->R = prtl->R + prtl->U*dt;
    prtl->U = prtl->U + prtl->dUdt*dt;
    prtl->e = prtl->e + prtl->dedt*dt;
			
    ///<li>calculate the middle values at step n+1/2 and save 
    ///them in spParticle objects prtl</ul></ul>
    prtl->R = (prtl->R + prtl->R_I)*0.5;
    prtl->U = (prtl->U + prtl->U_I)*0.5;
    prtl->e = (prtl->e + prtl->e_I)*0.5;
  }
}
//----------------------------------------------------------------------------------------
//			the predictor and corrector method: predictor, no density updating
//----------------------------------------------------------------------------------------
void Hydrodynamics::Corrector_summation(const double dt) {
  LOG(INFO) << " Hydrodynamics::Corrector_summation()";
  LOG(INFO) << " moving particles";
  ///- iterate the real partilce list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ///- for each particle: correction (advances R,U) based on values on n step and change rate at n+1/2
    prtl->R = prtl->R_I + prtl->U*dt;
    prtl->U = prtl->U_I + prtl->dUdt*dt;
    prtl->e = prtl->e_I + prtl->dedt*dt;
  }
  //control output
  // ofstream tx2tFile("changeRatesN1");
  // if (tx2tFile.is_open()) {
  //   BOOST_FOREACH(spParticle prtl, particle_list) {
  //     tx2tFile<<"\n R_x: "<<prtl->R[0]<<"  U_x: "<<prtl->U[0]<<"  e: "<<prtl->e<<"  dUdt: "<<prtl->dUdt[0]<<" dedt "<<prtl->dedt<<"  ID  "<<prtl->ID<<"\n";
  //   } 
    
  // }
  // tx2tFile.close();
}

//everything that comes below is new:
void Hydrodynamics::AdvanceFirstStep(const double dt) {
 ///<ul><li>iterate the real partilce list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    prtl->U = prtl->U + prtl->dUdt*0.5*dt;
    prtl->e = prtl->e + prtl->dedt*0.5*dt;
    prtl->R = prtl->R + prtl->U*dt;
  }

  // control output:

  // ofstream t2x2tFile("PositionsVeloN1");
  // if (t2x2tFile.is_open()) {
  //   BOOST_FOREACH(spParticle prtl, particle_list) {
  //     t2x2tFile <<setprecision (9)<< ::setw( 5 )<<prtl->ID
  // 		<<::setw(15)<<prtl->R[0]<< ::setw(15)
  // 		<<prtl->U[0]<<::setw(15)<<prtl->U[1]
  // 		<<::setw(15)<<prtl->e<<endl;
  //   }
  //   t2x2tFile.close();
  // } else {
  //   cout << "Unable to open/create file";
  // }

}


void Hydrodynamics::AdvanceFirstStepInclRho(const double dt) {
 ///<ul><li>iterate the real partilce list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    prtl->rho = prtl->rho + prtl->drhodt*0.5*dt;
    prtl->U = prtl->U + prtl->dUdt*0.5*dt;
    prtl->e = prtl->e + prtl->dedt*0.5*dt;
    prtl->R = prtl->R + prtl->U*dt;
  }
}
void Hydrodynamics::AdvanceStandardStep(const double dt) {
 ///<ul><li>iterate the real partilce list
///<ul><li>update  U,e, by advancing 1 step starting at intermediate variables
///<li>update position by advancing one time step </ul>

  BOOST_FOREACH(spParticle prtl, particle_list) {
    prtl->U = prtl->U_I + prtl->dUdt*dt;
    prtl->e = prtl->e_I + prtl->dedt*dt;
    prtl->R = prtl->R + prtl->U*dt;
 }
}

void Hydrodynamics::AdvanceStandardStepInclRho(const double dt) {
 ///<ul><li>iterate the real partilce list
///<ul><li>update rho, U,e, by advancing 1 step starting at intermediate variables
///<li>update position by advancing one time step </ul>
  BOOST_FOREACH(spParticle prtl, particle_list) {
    prtl->rho = prtl->rho_I + prtl->drhodt*dt;
    prtl->U = prtl->U_I + prtl->dUdt*dt;
    prtl->e = prtl->e_I + prtl->dedt*dt;
    prtl->R = prtl->R + prtl->U*dt;
 }
}

void Hydrodynamics::UpdateUe2Half(const double dt) {
///<ul><li>iterate the real partilce list 
///<ul><li>write current values in intermediate variables
///<li>update (overwrite) current values by advancing half a time step </ul>
  BOOST_FOREACH(spParticle prtl, particle_list) {
    prtl->U_I=prtl->U;
    prtl->e_I=prtl->e;
    prtl->U = prtl->U + prtl->dUdt*0.5*dt;
    prtl->e = prtl->e + prtl->dedt*0.5*dt;
  }
}


void Hydrodynamics::UpdateUeRho2Half(const double dt) {
/// <ul><li>iterate the real partilce list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    prtl->U_I = prtl->U;
    prtl->e_I = prtl->e;
    prtl->rho_I = prtl->rho;
    prtl->U = prtl->U + prtl->dUdt*0.5*dt;
    prtl->e = prtl->e + prtl->dedt*0.5*dt;
    prtl->rho = prtl->rho + prtl->drhodt*0.5*dt;
  }
}
