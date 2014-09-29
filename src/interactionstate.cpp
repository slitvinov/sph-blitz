// interaction.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//		defines interaction between particles
//		interaction.cpp
//----------------------------------------------------------------------------------------

//#include <iostream>
//#include <fstream>
//#include <string>

//#include <cstdio>
//#include <cstdlib>

// ***** localincludes *****
//#include "interaction.h"
//#include "particle.h"
//#include "polymerparticle.h"
//#include "initiation.h"
//#include "material.h"
//#include "force.h"
//#include "glbfunc.h"
#include "interactionstate.h"
#include "interaction.h"
class QuinticSpline;


using namespace std;

InteractionState::InteractionState(Interaction* newState)
{
  state_ = newState;
}

InteractionState::~InteractionState() {
  delete state_;
}


void InteractionState::ChangeState(Interaction* newState)
{  
  delete state_;
  state_ = newState;
}

void InteractionState::RenewInteraction(QuinticSpline &weight_function)
{
  state_->RenewInteraction(weight_function);
}

void InteractionState::SummationDensity()
{
  state_->SummationDensity();
}


void InteractionState::SummationShearRate()
{
  state_->SummationShearRate();
}


void InteractionState::SummationPhaseField()
{
  state_->SummationPhaseField();
}


void InteractionState::SummationPhaseGradient()
{
  state_->SummationPhaseGradient();
}

void InteractionState::SummationPhaseLaplacian()
{
  state_->SummationPhaseLaplacian();
}

void InteractionState::SummationCurvature()
{
  state_->SummationCurvature();
}


void InteractionState::acceptDataCollector(DataCollector* dc) {
  state_->acceptDataCollector(dc);
}

///get particle with larger ID
Particle* InteractionState::getOrg() const {
  return state_->getOrg();
}

///get particle with larger ID
Particle* InteractionState::getDest() const {
  return state_->getDest();
};



void InteractionState::UpdateForces()
{	
  state_->UpdateForces();
}


void InteractionState::UpdateForces_vis()
{
  state_->UpdateForces_vis();
}


void InteractionState::RandomForces(Wiener &wiener, 
				    double sqrtdt)
{
  state_->RandomForces(wiener, sqrtdt);
}

void InteractionState::RandomForces_Espanol(Wiener &wiener, 
					    double sqrtdt)
{
  state_->RandomForces_Espanol(wiener, sqrtdt);
}

ostream& InteractionState::put(ostream& ostr) const{
  return(state_->put(ostr));
}

ostream& operator<< (ostream& ostr, const InteractionState& inter)
{
  return inter.put(ostr);
}
