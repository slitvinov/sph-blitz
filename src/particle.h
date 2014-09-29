#ifndef PARTICLE_H
#define PARTICLE_H

#ifdef _OPENMP
#include <omp.h>
#endif

#include <vector>
//#include <iostream>
#include "vec2d.h"
//#include "wiener.h"
#include "dllist.h"
//#include "node.h"
//#include "interaction.h"

//#include "material.h"
//#include "initiation.h"
//#include "particlemanager.h"

//class Particle;
class Interaction;
class Initiation;
class Material;
class ParticleManager;
class Force;
class QuinticSpline;
class InteractionState;
class Particle;
class Node;
class DataCollector;

//#include "initiation.h"
//particle
//a sph particle
//note: reference a particle by pointer or adress
//never reference a particle directly!

/// particle class
//particle
//a sph particle
//note: reference a particle by pointer or adress
//never reference a particle directly!

/// SPH particle class

class Particle {
  static int number_of_materials;
 public:
  //  const Vec2d& R() const;
  //  Vec2d&       R();

  /// \name Particle constructors
  //@{
  ///create an "empty" particle using data from  Initiation object
  Particle(Initiation* const ini);

  ///default constructor 
  ///should not be called
  Particle();

  /// \bref create a "real" particle
  /// 
  /// \oveload
  /// \param position particle position
  /// \param velocity particle velocity
  /// \param density particle density
  /// \param temperature particle temperature
  /// \particle @material a reference to the material
  Particle(const Vec2d& position, const Vec2d& velocity,
	   double density, double pressure, double temperature, 
	   Material &material);

  /// \bref create a wall particle
  ///
  /// \param x particle position's coordinate
  /// \param y particle position's coordinate
  /// \param v particle velocity x coordinate
  /// \param u particle velocity y coordinate
  /// \param distance distance to boundary
  /// \param normal_x x coordinate of normal direction to boundary
  /// \param normal_y y coordinate of normal direction to boundary
  /// \param &material a reaference to the material
  /// \oveload
  Particle(double x, double y, double u, double v, 
	   double distance, double normal_x, double normal_y, Material &material);
	

protected:
  ///create a ghost particle
  ///used by createGhost method
  Particle(Node &RealParticle);

public:

  ///create a mirror image particle
  Particle(Node &RealParticle, Material &material);
  //@}
  //
  
  ///output operation
  virtual ostream& put(ostream& ostr) const;

  ///return the header for the output file
  static vector<string> getHeader();

  ///particle class destructor
  virtual ~Particle();
	
  ///particle states copier for boundary particles
  ///\param &RealParticle a reference to the realparticle
  void StatesCopier(int type);
			
  /// Returns the position of the particles
  virtual const Vec2d& R() const;
  /// Returns the position of the particles
  virtual Vec2d&       R();

/*   /// Returns the dUdt of the particles */
/*   virtual const Vec2d& dUdt() const; */
/*   /// Returns the dUdt of the particles */
/*   virtual Vec2d&       dUdt(); */

  /// Returns the velocity of the particles
  virtual const Vec2d& U() const;  
  /// Returns the velocity the particles
  virtual Vec2d&       U();

  /// Returns the density of the particles
  virtual const double& rho() const;
  /// Returns the density of the particles
  virtual double&       rho();

  /// \bref first as phase field gradient matrix 
  virtual const Vec2d& del_phi() const;
  virtual Vec2d&       del_phi();

  virtual double getMass() const;
  virtual void setMass(double newM);
  virtual double getEta() const;
  virtual double getZeta() const;
  virtual double getP() const;
  virtual double getCs() const;
  virtual double getT() const;
  virtual void setVolume(double newV);

  ///get volume
  virtual double getVolume() const;
  


  virtual Interaction* createInteractionWith(Particle *prtl_dest,
					    Force **force,
					    QuinticSpline &weight_function,
					    double dstc);
  virtual Interaction* _createInteractionWith(Particle *prtl_org,
					      Force** force,
					      QuinticSpline& weight_function,
					      double dstc);
  ///get an ID of the particle
  virtual long getParticleID() const;
  ///set a particle ID
  virtual void setParticleID(long newID);
  virtual int getParticleType() const;
  virtual int getBDtype() const;
  virtual int getbd() const;

  ///returns particle temperature
  virtual double getTemperature() const;

  ///save values at step n
  virtual void saveRRU();

  ///calculate the middle values at step n+1/2
  virtual void setMiddleRRU();
  
  /// one step for predictor summation
  virtual void predictorSummationStep(const double& dt);

  ///correction base on values on n step and change rate at n+1/2
  virtual void correctorSummationStep(const double& dt);

  ///correct U
  virtual void correctU();

  ///correction base on values on n step and change rate at n+1/2
  virtual void correctRRU(const double& dt);

//   ///set cell position
//   virtual void setCellPosition(int ncell_i, int ncell_j);

  ///increase shear rate
  virtual void increaseShearRate(Vec2d dSRx, Vec2d dSRy);

  ///set all shear rates to 0
  virtual void setShearRatetoZero();

  ///get shear rate in x direction
  virtual Vec2d getShearRateX() const;

  ///get shear rate in y direction
  virtual Vec2d getShearRateY() const;

  ///get the material number
  virtual int getMaterialNumber() const;

  ///get the material name
  virtual char* getMaterialName() const;

  ///returns a pointer to material
  virtual Material* getMaterial() const;

  ///update pressure according to the equation
  ///of state
  virtual void updatePressure();
  virtual void increaseRandomU(const Vec2d& deltaU);
  virtual void increaseRandomUReal(const Vec2d& deltaU);
  virtual void increasePhi(double deltaPhi, int noi, int noj);
  virtual void increaseLapPhi(double deltaLapPhi, int noi, int noj);
  
  virtual void setPhiToZero(int noi, int noj);
  virtual void setLapPhiToZero(int noi, int noj);
  virtual double getPhiElement(int noi, int noj) const;
  virtual void increaseRandomdU(const Vec2d& deltadU);
  virtual void increasedrhodt(const double& deltadrhodt);
  virtual void increasedUdt(const Vec2d& deltadUdt);
  virtual void setAlldToZero(double dt);
  virtual void setRandomUtoZero();

  ///returns kinetic energy of the particle
  double getKinEnergy() const;
  ///set velosity to zero
  void setUtoZero();
  ///accept data collector object
  virtual void acceptDataCollector(DataCollector*);

  ///create ghost particle
  virtual Particle* createGhost(Node&);

  ///return ID of the particle or ID of the real particle for ghost
  virtual long getRealID() const;

  ///return a pointer real particle 
  ///(for real particle return this)
  Particle* getReal();



  ///maximum ID number for non-ghost particles (real or wall particles) in the simulation
  static unsigned long ID_max;  

  ///total number of particles
  static unsigned long nParticle;
protected:
  /// \name Physical data	
  //@{
  ///particle 
  //  Vec2d R;	
  ///particle momentum
  Vec2d P;
  ///particle position
  Vec2d R_;
  ///particle velocity
  Vec2d U_;
  ///density
  double rho_;
  ///pressure
  double p;
  ///particle temperature
  double T;
  ///FIX:
  double Cs; 
  ///particle density
  double rho_I;
  ///particle density FIX:
  double rho_n; 
  ///particle mass
  double m;
  ///volume
  double V;
  ///particle internal energy
  double e;

  ///normal direction to the boundary (for boundary particles)
  Vec2d  nrml;  
  ///for wall boundary particles
  double bd_dst;
  ///\bref ID number
  ///
  ///a real particle has a unique positive ID
  ///a wall particle has zero ID
  ///an ghost particle (for perodic boundary condition)
  ///has a negtive ID of its corresponding real particle
  long ID; 


  //boundary type when bd = 1
  //0 wall particle with zero or constant velocity
  // but never move its position
  //1 ghost particle for perodic boundary
  int bd_type; 		

  /// \bref boundary particle indicator 
  /// 
  ///0: inside the boundary <BR>
  ///1: on the boundary
  int bd; 

//   /// \name Particle position in cells
//   //@{
//   int cell_i, cell_j; 
//   //@}


  ///Intermediate values used in integrator
  //@{
  Vec2d  R_I, P_I, U_I, P_n, U_n; //intermediate momentum and 
                                  //velocity used in integrator
  double e_I, e_n; //intermediate volume, internal energy used in integrator
  //@}

  ///shear rate coordinate (should set by Interaction object)
  Vec2d ShearRate_x;
  ///shear rate coordinate (should set by Interaction object)
  Vec2d ShearRate_y;
  //@}

  ///a pointer to the material
  Material *mtl; 

  ///a pointer to a real particle
  Node *rl_prtl;

  /// \name Data for multimaterials
  //@{
  double eta, zeta; //viscosity of each particle
  double **phi; //phase field matrix
  //@}

  /// \bref first as phase field gradient matrix 
  ///then the independent values ([0][0] and [0][1]) of suface stress matrix 
  Vec2d del_phi_;
  
  ///laplasian phase field gradient
  double **lap_phi;

  /// \name Change rate for real particles
  //@{
  ///density change rate
  double drhodt;
  ///internal energy change rate
  double dedt; 
  ///acceration
  Vec2d dUdt;
  ///random velocity change
  Vec2d _dU;
  //@}
  
  ///particles conservation test
  friend double hydroConservationTest(const Llist<Node>&);

  ///particle moving test
  friend void hydroMovingTest(const Llist<Node>&);
  //  friend class Particle;
};
#endif
