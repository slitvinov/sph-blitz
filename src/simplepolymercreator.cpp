#include <string>
#include <vector>
#include <fstream>
#include <gsl/gsl_const_mksa.h>

#include "particlemanager.h"
#include "node.h"
#include "vec2d.h"
#include "polymerparticle.h"
#include "glbfunc.h"
#include "ConfigFile.h"
#include "initiation.h"
#include "simplepolymercreator.h"


using namespace std;
using namespace blitz;
extern double k_bltz;
SimplePolymerCreator::SimplePolymerCreator(const string& configfilename)
{ 
   //set parameters from the configuration file
  Initiation* ini =Initiation::Instance();
  
  ConfigFile config(configfilename);
  //  polyHead_ = 0.2, 0.2;
  ///read data from the file
  config.readInto(polyFileName_, "pname");  
  config.readInto(R0_, "R0");
  config.readInto(H_, "H");
  H_ = ini->non_dms_elasticity(H_);
  R0_  = ini->non_dms_length(R0_);

  
//   cout << "R/Rp = " << R0_/ini->delta << '\n';
//   cout << "b = " << H_*R0_*R0_ / (k_bltz * ini->T0) << endl;

   
  if ( !config.readInto(polyHead_, "polyHead") ) {
    cout << "Cannot read a polyHead" << '\n';
    throw 1;
  }
  // cout << "polyHead = " << polyHead_ << '\n';
    
  // read polymer configuration file
  ifstream fin;
  fin.open(polyFileName_.c_str());
  if (!fin) {
    cout<<"SimplePolymerCreator: Cannot open "
	<< polyFileName_ <<" \n";
    exit(1);
  }  
  //read the "polymer directions" part of the file
  double temp_angel;
  alphaVector_.clear();
  cout<< "Read polymer file:" << polyFileName_ << '\n';
  while(!fin.eof()) {    
    fin >> temp_angel;
    alphaVector_.push_back(temp_angel);
  }
}

SimplePolymerCreator::~SimplePolymerCreator() {
  
}

void SimplePolymerCreator::CreatePolymer(const ParticleManager& particles) {
   Initiation* ini=Initiation::Instance(); 
   
   Vec2d x_dm = polyHead_;
   Vec2d pvec(ini->delta / ini->box_size);   
   //particle 
   Node* Pa;
   //direction vector
   Vec2d vdirect;   
   //initial angel
   double rad_alpha = 0;
   for (unsigned int i=0; i<alphaVector_.size(); i++) {
     rad_alpha = rad_alpha + alphaVector_[i]/180*pi;
     vdirect = cos(rad_alpha), sin(rad_alpha);
     x_dm = x_dm + pvec * vdirect;
     Pa = particles.getClosestParticle(x_dm);

     //swith to a new particle position
     x_dm = Pa->R() / ini->box_size;
     
     ///change the particle state to polymer
     Pa->ChangeState(new PolymerParticle(Pa));
     std::cout << "Polymer particle position: " << Pa->R() << '\n';

     ///put the polymer particle into the vector
     //     polyVector_.push_back(Pa);
   }
}


Vec2d SimplePolymerCreator::getForce(const Vec2d& eij, 
				     const double& rij) const {
  // rij: distance
  // eij: normalised direction
  // FENE pair force 


  //the distance should be less then maximum extens
  if (rij >= R0_) {
    std::cout << "rij = " << rij << '\n';
    std::cout << "R0_ = " << R0_ << '\n';
    assert(true);
  };
  return -H_ * rij*eij / ( 1 - (rij*rij) / (R0_* R0_));
}

double SimplePolymerCreator::getEnergy(const Vec2d& eij,
				      const double& rij) const {
  // rij: distance
  // eij: normalized direction
  // FENE energy

  return -H_ / 2.0 * log(1- (rij*rij) / (R0_ * R0_)) * R0_*R0_;  
}

void SimplePolymerCreator::showName() const {
  cout << "simplepolymercreator" << '\n';
}

void SimplePolymerCreator::push_back(PolymerInteraction* newinteraction) {
  interactVector_.push_back(newinteraction);
}
