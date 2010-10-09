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
#include "Interaction/interaction.h"
#include "Timer/timer.h"
#include "initiation.h"
#include "ParticleContext/particlecontext.h"
using namespace std;

Hydrodynamics::Hydrodynamics(ParticleManager &particles, Initiation &ini): 
  ini(ini) {
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
    viscosity_max = std::max(viscosity_max, materials[k]->nu);
  }

  /// <li>determine the artificial compressiblity
  const double sound =  viscosity_max;
  LOG(INFO) << "sound speed is ready: " << sound;
  for(int k = 0; k < ini.number_of_materials; k++) {
    materials[k]->Set_b0(sound);
  }
  LOG(INFO) << "update of b0 is finished";

  ///<li>biuld the real particles
  if (ini.simu_mode == 1) {
    particles.BuildRealParticle(materials, particle_list, ini);
  }  else if (ini.simu_mode == 2) {
    particles.BuildRealParticleGasDyn(materials, particle_list, ini);
  } else {
    LOG(ERROR) << "Unknown SIMULATION_MODE: " << ini.simu_mode;
    LOG(ERROR) << "check configuration file";
    std::exit(EXIT_FAILURE);
  }
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
  LOG(INFO)<<"Hydrodynamics::UpdateDensity(ini, weight_function, ini)";
  ///- obtain the interaction pairs
  particles.BuildInteraction(interaction_list, particle_list, weight_function, ini);
  assert(interaction_list.size()>0);
  ///- add density contribution of the particle itself
  Self_density(weight_function);
  ///- iterate the interaction list
  BOOST_FOREACH(spInteraction pair, interaction_list) {
    pair->SummationDensity();	
  };
  LOG(INFO)<<"density after smoothing";

  ///- calulate new pressure by calling UpdateState() Method
  UpdateState(ini);
}

//----------------------------------------------------------------------------------------
//		summation for particles density without updating interaction list
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateDensity(const Initiation &ini, spKernel  weight_function) {
  ///- initiate zero density
  LOG(INFO)<<"Hydrodynamics::UpdateDensity(ini, weight_function)";
  Self_density(weight_function);

  // BOOST_FOREACH(spParticle prtl, particle_list){
  //   LOG_EVERY_N(INFO,100) << setprecision (9)<<prtl->ID<<"    "<<prtl->rho<<endl;
  // }

  ///- iterate the interaction list
  assert(interaction_list.size()>0);
  BOOST_FOREACH(spInteraction pair, interaction_list) {
    pair->SummationDensity();	
  }

  LOG(INFO)<<"density after smoothing";
  assert(particle_list.size()>0);
  // BOOST_FOREACH(spParticle prtl, particle_list){
  //   LOG_EVERY_N(INFO,100) << setprecision (9)<<prtl->ID<<"    "<<prtl->rho<<endl;
  //}

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

    ///- iterate the interaction list
  BOOST_FOREACH(spInteraction aux_interaction, interaction_list) {
      aux_interaction->UpdateForces();
  }
  //control output
  //BOOST_FOREACH(spParticle prtl, particle_list) {
  //    LOG_EVERY_N(INFO, 100) <<"dUdt: "<<prtl->dUdt[0] << " dUdt1: "<<prtl->dUdt[1];
  //  }


  // ofstream tx2tFile("DerivativesDataN1");
  //   if (tx2tFile.is_open())
  //     {
  //       BOOST_FOREACH(spParticle prtl, particle_list) {
  // 	  tx2tFile <<setprecision (9)<< ::setw( 5 )<<prtl->ID<< ::setw(20)<<prtl->dUdt[0]<<::setw(20)<<prtl->dUdt[1]<<::setw(20)<<prtl->dedt<<endl;
  // 	}
  // 	tx2tFile.close();
  //     }
  //   else cout << "Unable to open/create file";
      
  //     BOOST_FOREACH(spParticle prtl, particle_list) {
  // 	LOG_EVERY_N(INFO, 100000) <<"dUdt: "<<prtl->dUdt[0] << " dUdt1: "<<prtl->dUdt[1];
  //     }


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
    assert(prtl->m>0.0);
    prtl->rho = weight_function->w(0.0)*prtl->m;
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
  ///- iterate particles on the real particle list
  ///- to each particles dUdt: add the gravity effects
  if (!ini.useCompiledBodyForce) {
    BOOST_FOREACH(spParticle prtl, particle_list) {
      const int no = prtl->mtl->material_no;
      prtl->dUdt[0] = prtl->dUdt[0] + ini.g_force(no, 0);
      prtl->dUdt[1] = prtl->dUdt[1] + ini.g_force(no, 1);
    }
  } else {
    BOOST_FOREACH(spParticle prtl, particle_list) {
      double Fx = 0.0;
      double Fy = 0.0;
      /// can segfoult 
      (*ini.bodyF)(prtl->R[0], prtl->R[1], Fx, Fy);
      prtl->dUdt[0] = prtl->dUdt[0] + Fx;
      prtl->dUdt[1] = prtl->dUdt[1] + Fy;
    } // BOOST_FOREACH
  } // !ini.useCompiledBodyForce
}

//----------------------------------------------------------------------------------------
//							calculate states from conservatives
//----------------------------------------------------------------------------------------
void Hydrodynamics::UpdateState(const Initiation &ini) {
  LOG(INFO) << "Hydrodynamics::UpdateState(ini)";
  ///- iterate particles on the real particle list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ///- calculate pressure for each particle
    if (ini.simu_mode==1)  { //liquid mode equation of state
      assert(prtl->rho > 0.0);
      prtl->p = prtl->mtl->get_p(prtl->rho);
    }
    //gas dynamics mode equation of state
    if (ini.simu_mode==2) {
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
  //maximum sound speed, particle velocity and density
 
  double dt_f=1.0e30;//time step due to force consideration 
  double dt_cv=1.0e30;//time step due to Courant and Viscosity consideration
  
  //predict the time step
  //iterate the partilce list, calculate theoretical max admissible time step
  //for each particle and retain the smallest of all
  BOOST_FOREACH(spParticle prtl, particle_list) {
    assert(prtl != NULL);
    //dt_f according to Monaghan 1992 ("smoothed particle hydrodynamics") (sec.10.3)
    dt_f=std::min(dt_f, sqrt(ini.supportlength/2/(v_abs(prtl->dUdt)+1e-35)));//to prevent singularity
    //dt_cv according to Monaghan 1992 ("smoothed particle hydrodynamics") (sec.10.3)
    dt_cv=std::min(dt_cv,ini.supportlength/2/(prtl->Cs+0.6*(ini.alpha_artVis*prtl->Cs+ini.beta_artVis*prtl->mue_ab_max)));
    assert(dt_cv>0.0);
  }
  
  // reset mue_ab to zero (for next iterarion)
  Zero_mue_ab_max();
  
  const double dt = 0.25*std::min(dt_f, dt_cv);
  assert(dt>0.0);
  LOG(INFO) << "dt: " << dt; 
  return dt;
}


//----------------------------------------------------------------------------------------
//							get the time step (hydro)
//----------------------------------------------------------------------------------------
double Hydrodynamics::GetTimestep(const Initiation& ini) const {
  //maximum sound speed, particle velocity and density
  double Cs_max = 0.0; 
  double viscosity_max=0.0;
  //predict the time step
  //iterate materials to find 
  // - largest sound spead 
  // - largest visocity 
  BOOST_FOREACH(spMaterial mtl, materials) {
    assert(mtl != NULL);
    Cs_max = std::max(Cs_max, mtl->get_Cs());
    viscosity_max = std::max(viscosity_max, mtl->nu);
  }
  LOG(INFO) << "Cs_max = " << Cs_max;
  LOG(INFO) << "viscosity_max = " << viscosity_max;

  double max_gr = 1e-13;
  for(int k = 0; k < ini.number_of_materials; k++) {
    Vec2d gravity;
    gravity[0] = ini.g_force(k, 0);
    gravity[1] = ini.g_force(k, 1);
    const double vabs = v_abs(gravity);
    if (vabs> max_gr) {
      max_gr = vabs;
    }
  }
  LOG(INFO) << "max_gr = " << max_gr;

  const double dt_vis = 0.125*ini.delta*ini.delta/viscosity_max;
  LOG(INFO) << "dt_vis = " << dt_vis;
  const double dt_sound = 0.25*ini.delta/Cs_max;
  LOG(INFO) << "dt_sound = " << dt_sound;
  const double dt_gravity = 0.25*ini.delta/max_gr;
  LOG(INFO) << "dt_gravity = " << dt_gravity;
  const double dt = AMIN3(dt_vis, dt_gravity, dt_sound);
  LOG(INFO) << "dt  = " << dt;
  return dt;
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
    const Vec2d auxR = prtl->R + prtl->U*dt;
    const double auxRho = prtl->rho + prtl->drhodt*dt;
    const Vec2d auxU = prtl->U + prtl->dUdt*dt;
    const double auxE = prtl->e + prtl->dedt*dt;
			
    ///<li>calculate the middle values at step n+1/2</ul></ul>
    if (movePartilces) {
      ini.context->UpdatePosition(prtl, (auxR + prtl->R_I)*0.5);
    }
    prtl->rho = (auxRho + prtl->rho_I)*0.5;
    ini.context->UpdateVelocity(prtl, (auxU+ prtl->U_I)*0.5);
    prtl->e=(auxE+ prtl->e_I)*0.5;
  }
}
//----------------------------------------------------------------------------------------
//							the redictor and corrector method: predictor
//----------------------------------------------------------------------------------------
void Hydrodynamics::Corrector(const double dt) {
  ///- iterate the real partilce list
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ///- for each particle: correction based on values on n step and change rate at n+1/2
    if (movePartilces) {
      ini.context->UpdatePosition(prtl, prtl->R_I + prtl->U*dt);
    }
    prtl->rho = prtl->rho + prtl->drhodt*dt;
    ini.context->UpdateVelocity(prtl, prtl->U_I + prtl->dUdt*dt);
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
    const Vec2d auxR = prtl->R + prtl->U*dt;
    const Vec2d auxU = prtl->U + prtl->dUdt*dt;
    const double auxE = prtl->e + prtl->dedt*dt;
			
    ///<li>calculate the middle values at step n+1/2 and save 
    ///them in spParticle objects prtl</ul></ul>
    if (movePartilces) {
      ini.context->UpdatePosition(prtl, (auxR + prtl->R_I)*0.5);
    }
    ini.context->UpdateVelocity(prtl, (auxU + prtl->U_I)*0.5);
    prtl->e = (auxE + prtl->e_I)*0.5;
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
    if (movePartilces) {
      ini.context->UpdatePosition(prtl, prtl->R_I + prtl->U*dt);
    }
    ini.context->UpdateVelocity(prtl, prtl->U_I + prtl->dUdt*dt);
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
