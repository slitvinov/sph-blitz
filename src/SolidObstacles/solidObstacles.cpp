/// \file solidObstacles.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes
/// \brief abstract class for solid obstacles within the calculation domain
///


//----------------------------------------------------------------------------------------
//      abstract class for solid obstacles within the calculation domain
//----------------------------------------------------------------------------------------
#include <glog/logging.h>
#include <boost/foreach.hpp>
#include "glbfunc.h"

// ***** local includes *****
#include "SolidObstacles/solidObstacles.h"

//constructor to inizialize the data members
SolidObstacles::SolidObstacles(const Initiation& ini)
  : domain_size(ini.box_size), supportlength(ini.supportlength), solObs_virt_veloc_type(ini.solObs_virt_veloc_type),d_realPart_solObs_min(ini.d_realPart_solObs_min), solObs_thermal_BC_type(ini.solObs_thermal_BC_type), T_w_solObs_isothermal(ini.T_w_solObs_isothermal)
{
  
}


// sets flag <<solidObstacle_ghostParticle>>, 
// which is an attribute of each particle object.
void SolidObstacles::set_ghostPrtlSolidObstacle_flag(spParticle& prtl)
{
  prtl->solidObstacle_ghostParticle=1;
}

//set tangents to solObs surface for all particles 
void SolidObstacles::set_all_solObs_tangentsAndDistances(Hydrodynamics &hydro) {
  // iterate particle list
  BOOST_FOREACH(spParticle prtl, hydro.particle_list) {
    set_solObs_tangentAndDistance(prtl);
  } 
}


// set virtual velocity for destination particle if ghost particle 
// (if no ghost particle set virtual velocity equal to real velocity) 
Vec2d SolidObstacles::set_virtual_velocity(spParticle& org_prtl,spParticle& dest_prtl) {
  // first check if destination particle is a ghost particle for solid Obstacle
  // ad if a virtual velcoity assignment is activated
  if(dest_prtl->solidObstacle_ghostParticle==1&&solObs_virt_veloc_type==1) {
    // if this is the case: calculate virtual velocity according to Morris1997
    
    // first calculate distance d_ghost_tang from
    // ghost particle to boundary tangent 
    
    // first step for this:
    // from line equation: x=origin_point+lambda*direction-vector
    // calculate lambda which leads to the point C on the line closest to ghost
    // particle
    // ATTENTION: the origin is here origin of the line and NOT
    // the origin particle of an interaction

    // LOG(INFO)<<"origin-point"<<org_prtl->SolObs_tangent[0];
    // LOG(INFO)<<"direction-vector"<<org_prtl->SolObs_tangent[1];
    // LOG(INFO)<<"ghost prtl position"<<dest_prtl->R;
    // LOG(INFO)<<"d_realPart_solObs"<<org_prtl->d_realPart_solObs;
    const Vec2d origin_point=org_prtl->SolObs_tangent[0];
    const Vec2d direction_vector=org_prtl->SolObs_tangent[1];
    const Vec2d P_ghost=dest_prtl->R; // position/point of ghost particle
    
    const double lambda=dot(P_ghost-origin_point,
			    direction_vector/v_sq(direction_vector));
    // LOG(INFO)<<"lambda"<<lambda;
    
    // second step: with this lambda value and the equation for the
    // line one obtais point C, the vector D connecting particle position
    // and point_c has the desired length
    
    const Vec2d vector_D=P_ghost-(origin_point+lambda*direction_vector);
    // desired distance is norm of the vector
    double d_ghost_tang=v_abs(vector_D);
    // LOG(INFO)<<"distance ghost tang"<<d_ghost_tang;
    
    const double d_realPart_solObs=AMAX1(org_prtl->d_realPart_solObs,d_realPart_solObs_min);
    // LOG(INFO)<<"final distance real prtl. <-> tangent"<<d_realPart_solObs;

    //finally return the virtual velocity 
    const Vec2d U_virt= -1*d_ghost_tang/d_realPart_solObs*org_prtl->U;
    // LOG(INFO)<<"virtual velocity"<<U_virt;
    return U_virt;
        
  }
  // if not ghost particle solObs or no virt. velocity assignment desired,
  // simply return actual velocity of destination particle
  else
    return dest_prtl->U;
}

//set initial temperature for ghost particles solObs
// all ghost particles sol obs are initialized with the same temeperature T_w
// (which corresponds to the desired wall temperature for isothermal boundary condition)
void SolidObstacles::set_initial_Temperature_solObs_prtl(spParticle& prtl) {

  if(solObs_thermal_BC_type==1)
    prtl->T=T_w_solObs_isothermal;
}

// set Temperature for destination particle if ghost particle (for isothermal BC)
double SolidObstacles::set_Temperature_SolObs_isothermal(spParticle& org_prtl,spParticle& dest_prtl) {
  // first check if destination particle is a ghost particle for solid Obstacle
  // ad if thermal boundary condition type is isothermal with extrapolated T (2)
  if(dest_prtl->solidObstacle_ghostParticle==1&&solObs_thermal_BC_type==2) {
    // if this is the case: calculate his temperature
    
    // first calculate distance d_ghost_tang from
    // ghost particle to boundary tangent 
    
    // first step for this:
    // from straight line equation: x=origin_point+lambda*direction-vector
    // calculate lambda which leads to the point C on the line closest to ghost
    // particle
    // ATTENTION: the origin is here origin of the line and NOT
    // the origin particle of an interaction

    const Vec2d origin_point=org_prtl->SolObs_tangent[0];
    const Vec2d direction_vector=org_prtl->SolObs_tangent[1];
    const Vec2d P_ghost=dest_prtl->R; // position/point of ghost particle
    
    const double lambda=dot(P_ghost-origin_point,
			    direction_vector/v_sq(direction_vector));
        
    // second step: with this lambda value and the equation for the
    // straight one obtais point C, the vector D connecting particle position
    // and point_c has the desired length
    
    const Vec2d vector_D=P_ghost-(origin_point+lambda*direction_vector);
    // desired distance is norm of the vector
    double d_ghost_tang=v_abs(vector_D);
      
    //limit distance real prtl<-> solid obstacle to avoid too high temperature 
    //values for ghost particles 
    const double d_realPart_solObs=AMAX1(org_prtl->d_realPart_solObs,d_realPart_solObs_min);
    // LOG(INFO)<<"real distance real part <-> tangent"<<org_prtl->d_realPart_solObs;

    //  LOG(INFO)<<"final distance real part <-> tangent"<<d_realPart_solObs;
    //finally return the temperature according to linear interpolation (see thesis)
    const double T=T_w_solObs_isothermal+d_ghost_tang/d_realPart_solObs*(T_w_solObs_isothermal-org_prtl->T);
    // LOG(INFO)<<"virtual velocity"<<U_virt;
    return T;
        
  }
  // if particle is not ghost particle solObs or if ghost prtl but isothermal
  // boundary condition modelling using constant temperature wall particles
  // (solObs_thermal_BC_type=1) simply return the actual temerature value again
  // (ghost particles are all initialized with
  // either T_w(solObs_thermal_BC_type=1) or keep their temperature from
  // initialization (.ivs-file) (solObs_thermal_BC_type=0)
  else
    return dest_prtl->T;
}






SolidObstacles::~SolidObstacles()
{
}
