/// \file s1timesolver.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//-----------------------------------------------------------------------
//			Time solver class
//			s1timesolver.cpp
//-----------------------------------------------------------------------
#include <glog/logging.h>

// ***** localincludes *****
#include "src/hydrodynamics.h"
#include "src/particlemanager.h"
#include "src/TimeSolver/s1timesolver.h"
#include "src/initiation.h"
#include "src/boundary.h"
#include "src/Utilities/utilities.h"
#include "src/glbtype.h"
#include <boost/foreach.hpp>
#include "Interaction/interaction.h"
#include "Kernel/kernel.h"

using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
S1TimeSolver::S1TimeSolver():
  ite(0)
{
  ///- initialize the iteration
  LOG(INFO) <<"Creating S1TimeSolver object";
}

void S1TimeSolver::show_information() const {

}


//----------------------------------------------------------------------------------------
//					advance time interval D_time with summation for density
//					predictor and corrector method used
//----------------------------------------------------------------------------------------
void S1TimeSolver::TimeIntegral_summation(Hydrodynamics &hydro, 
					  ParticleManager &particles, 
					  Boundary &boundary, 
					  double &Time, const double D_time, 
					  const Initiation &ini, 
					  spKernel weight_function) {
  LOG(INFO) << "Start TimeIntegral_summation";
  double integeral_time = 0.0;
  while(integeral_time < D_time) {
    double dt;
    if (ini.simu_mode == 4) {
      dt = hydro.GetS1TimeStep(ini);
    } else {
      LOG(ERROR) << "wrong simulation mode";
      exit(EXIT_FAILURE);
    }
    assert(dt>0.0);
    //control output
    LOG(INFO)<<"\n current timestep:"<<dt<<
        "\n current absolute integraltime:"<<Time<<
        "\n current (relative) integraltime:"<<integeral_time<<
        "\n current (absolute) iterations:"<<ite;
    ite ++;
    integeral_time =integeral_time+ dt;
    Time += dt;
    ini.timer->updateTime(Time);
    ini.timer->update_dt(dt);
	  
    ///<ul><li>screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
			  <<Time<<"	dt: "<<dt<<"\n";
	  
    //predictor and corrector method used
    ///<li>the prediction step
    checkVelocity(ini, hydro.particle_list);
    LOG(INFO) << "checkVelocity passed";
    checkForces(ini, hydro.particle_list);
    LOG(INFO) << "checkForces passed";
    hydro.BuildInteractions(particles, weight_function, ini);///<ol><li> rebuild interactions
    hydro.UpdateDensity(ini, weight_function);///<li> hydro.UpdateDensity
    boundary.BoundaryCondition(particles);///<li> boundary.BoundaryCondition

    //control output
    hydro.UpdateChangeRate(ini);///<li> hydro.UpdateChangeRate
    checkForces(ini, hydro.particle_list);
	  
    hydro.Predictor_summation(dt);///<li>hydro.Predictor_summation</ol>
    ///<li> the correction step without update the interaction list
    boundary.BoundaryCondition(particles);///<ol><li>boundary.BoundaryCondition

    hydro.UpdateInteractions(weight_function);///<li> update interactions
    hydro.UpdateDensity(ini, weight_function);///<li>hydro.UpdateDensity
    
    boundary.BoundaryCondition(particles);///<li>boundary.BoundaryCondition

    //control output
    LOG(INFO)<<"change rate for corrector:";
    hydro.UpdateChangeRate(ini); ///<li>hydro.UpdateChangeRate

    //hydro.Corrector_summation(dt);///<li>hydro.Corrector_summation</ol>
    hydro.Corrector_summation_velocity(dt);
    const double pdt = dt / static_cast<double>(ini.s1_niter);
    for (int nit=0; nit<ini.s1_niter; nit++) {
      s1SubStep(hydro, particles, weight_function, pdt);
    }
    hydro.Corrector_summation_position(dt);

    checkVelocity(ini, hydro.particle_list);
    ///<li> renew boundary particles
    boundary.RunAwayCheck(hydro);///<ol><li>boundary.RunAwayCheck
    particles.UpdateCellLinkedLists();///<li>particles.UpdateCellLinkedLists
    boundary.BuildBoundaryParticle(particles, hydro);///<li>boundary.BuildBoundaryspParticle</ol></ul>
  }
}


void S1TimeSolver::TimeIntegral(Hydrodynamics &hydro, 
                                ParticleManager &particles, 
                                Boundary &boundary, 
                                double &Time, double D_time, 
                                const Initiation &ini, spKernel weight_function) {
  LOG(INFO) << "Start TimeIntegral_summation";
  double integeral_time = 0.0;
	
  while(integeral_time < D_time)
  {
    const double dt = hydro.GetTimestep(ini);
    assert(dt>0.0);
    //control output
    LOG(INFO)<<"\n current timestep:"<<dt<<
        "\n current absolute integraltime:"<<Time<<
        "\n current (relative) integraltime:"<<integeral_time<<
        "\n current (absolute) iterations:"<<ite;
    ite ++;
    integeral_time =integeral_time+ dt;
    Time += dt;
    ini.timer->updateTime(Time);
    ini.timer->update_dt(dt);
	  
    ///<ul><li>screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
			  <<Time<<"	dt: "<<dt<<"\n";
    //predictor and corrector method used
    ///<li> the prediction step
    hydro.BuildInteractions(particles, weight_function, ini);///<ol><li>hydro.BuildInteractions
    hydro.UpdateChangeRate(ini);///<li>hydro.UpdateChangeRate
    hydro.Predictor(dt);///<li>hydro.Predictor
    hydro.UpdateState(ini);///<li>hydro.UpdateState</ol>

    ///<li> the correction step without update the interaction list
    hydro.UpdateInteractions(weight_function);///<ol><li>hydro.UpdatePair
    //boundary.BoundaryCondition(particles);///<li>boundary.BoundaryCondition
    hydro.UpdateChangeRate(ini);///<li>hydro.UpdateChangeRate
    hydro.Corrector(dt);///<li>hydro.Corrector
    hydro.UpdateState(ini);///<li>hydro.UpdateState</ol>
    ///<li> renew boundary particles
    boundary.RunAwayCheck(hydro);///<ol><li>boundary.RunAwayCheck
    particles.UpdateCellLinkedLists();///<li>particles.UpdateCellLinkedLists
    //boundary.BuildBoundaryParticle(particles, hydro);///<li>boundary.BuildBoundaryParticles</ol></ul>
  }
}

S1TimeSolver::~S1TimeSolver() {
  LOG(INFO) << "destructor of S1TimeSolver is called";
}

void s1SubStep(Hydrodynamics &hydro, ParticleManager &particles, 
	       spKernel weight_function, const double pdt) {
   ///- iterate the interaction list

  LOG(INFO) << "s1SubStep is called";

  BOOST_FOREACH(spInteraction pair, hydro.interaction_list) {
    ///- calculate for eahc pair the pair forces or change rate
    spParticle Org = pair->getOrigin();
    spParticle Dest = pair->getDest();

    const double rhoi = Org->rho; 
    const double rhoj = Dest->rho;

    const double mi = Org->m;
    const double mj = Dest->m;

    const double rmi = 1.0/mi;
    const double rmj = 1.0/mj;
    
    const double etai = Org->eta;
    const double etaj = Dest->eta;
    const double eta_geom = 2.0*etai*etaj/(etai + etaj);

    const double rij = v_distance(Org->R, Dest->R);
    const double gradWij = weight_function->F(rij);

    const double sigmai = rhoi / mi ;
    const double sigmaj = rhoj / mj;

    const double Aij = (1.0 / (sigmai*sigmai) + 1.0 / (sigmaj*sigmaj) ) * (- gradWij);

    const double kij = - eta_geom * Aij / rij;

    const Vec2d Ui_p = Org->U;
    const Vec2d Uj_p = Dest->U;
    
    Org->U  = (pdt*kij*rmi*Uj_p+(pdt*kij*rmj+1)*Ui_p)/(pdt*kij*rmj+pdt*kij*rmi+1);
    Dest->U = (pdt*kij*rmi*Uj_p+Uj_p+pdt*kij*rmj*Ui_p)/(pdt*kij*rmj+pdt*kij*rmi+1);

    //    LOG(INFO) << "Org->U - Ui_p = " << Org->U - Ui_p;
    //    LOG(INFO) << "Dest->U - Uj_p = " << Dest->U - Uj_p;

  }
}
