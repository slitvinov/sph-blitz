// particle.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: 

//-------------------------------------------------------------------
//				Particle data type definition
//				particle.cpp
//----------------------------------------------------------------

// ***** local includes *****
#include "node.h"
#include "particle.h"
#include "initiation.h"
#include "material.h"
#include "force.h"
#include "quinticspline.h"
#include "interaction.h"
#include "datacollector.h"
#include "glbfunc.h"
#ifndef NOLOG
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#endif


unsigned long Particle::ID_max = 0;
unsigned long Particle::nParticle = 0;

int Particle::number_of_materials = 0;
//----------------------------------------------------------------------------------------
//							constructors
//							empty particle
//---------------------------------------------------------------------------------------
Particle::Particle() {
  throw(1);
}

Particle::Particle(Initiation* const ini)
{
  int i, j;  
  //copy properties from initiation
  number_of_materials = ini->number_of_materials;
  
  //phase filed
  phi = new double*[number_of_materials];
  lap_phi = new double*[number_of_materials];
  for(i = 0; i < number_of_materials; i++) {
    phi[i] = new double[number_of_materials];
    lap_phi[i] = new double[number_of_materials];
  }
  for(i = 0; i < number_of_materials; i++)
    for(j = 0; j < number_of_materials; j++) {
      phi[i][j] = 0.0;
      lap_phi[i][j] = 0.0;
    }
  //  ID_max++;
}
//----------------------------------------------------------------------------------------
//pa
//----------------------------------------------------------------------------------------
Particle::~Particle()
{
	//phase filed
	for(unsigned int i = 0; i < number_of_materials; i++) {
		delete[] phi[i];
		delete[] lap_phi[i];
	}
	//pahse field gradient matrix
	delete[] phi;
	delete[] lap_phi;

	nParticle--;
	//decrease the total number of particles if it is not a ghost
	assert(ID_max > 0);
	assert(nParticle > 0);
	if (ID>0) {
	  ID_max--;
	}
	//	cerr << "nParticle = " << nParticle << '\n';
	//	cerr << "ID_max = " << nParticle << '\n';

}
//----------------------------------------------------------------------------------------
//							real particle
//		NOTE the particle mass and volume will be specified initiation::VolumeMass()
//----------------------------------------------------------------------------------------
Particle::Particle(const Vec2d& position, 
		   const Vec2d& velocity, 
		   double density, 
		   double pressure, 
		   double temperature, 
		   Material &material): 
  bd(0)
{
  int i, j;
  //increase the total particle number
  ID_max++;
  nParticle++;
  
  //give a new ID number
  ID = ID_max;
  
  //point to the material properties
  mtl = &material;
	//viscosity
  eta = mtl->eta; zeta = mtl->zeta;
  
  //set particle position
  R_ = position; 
  
  //set states
  rho_ = density; p = pressure; T = temperature; Cs = mtl->get_Cs(p, rho_);
  U_ = velocity; U_I = U_;
  
  //set conservative values and their  intermediate values
  m = 0.0; V = 0.0; e = mtl->get_e(T); e_I = e;
  R_I = R_; P_I = P; rho_I = rho_;
  P_n = P; U_n = U_; rho_n = rho_; e_n = e; 

  //phase filed
  phi = new double*[number_of_materials];
  lap_phi = new double*[number_of_materials];
  for(i = 0; i < number_of_materials; i++) {
    phi[i] = new double[number_of_materials];
    lap_phi[i] = new double[number_of_materials];
  }
  for(i = 0; i < number_of_materials; i++)
    for(j = 0; j < number_of_materials; j++) {
      phi[i][j] = 0.0;
      lap_phi[i][j] = 0.0;
    }
}
//----------------------------------------------------------------------------------------
//								construct a wall particle
//----------------------------------------------------------------------------------------
Particle::Particle(double x, double y, double u, double v, 
		   double distance, double normal_x, 
		   double normal_y, Material &material) : bd(1), bd_type(0)
{

	//give a new ID number
	ID = 0;
	//point to the material propertiI aes
	mtl = &material;

	//set particle position
	R()[0] = x; R()[1] = y; 
	
	//set states
	U_[0] = u; U_[1] = v;
	
	//distance and normal directions to boundary
	bd_dst = distance;
	nrml[0] = normal_x; nrml[1] = normal_y;

	//set states value to avoid error
	rho_ = 0.0, p = 0.0, T = 0.0;
}
//----------------------------------------------------------------------------------------
//						creat a ghost particle 
//----------------------------------------------------------------------------------------
Particle::Particle(Node &RealNode) : 
  bd(1), 
  bd_type(1),
  //give a new ID number
  ID(0)
{
  int i, j;	
  nParticle++;
  //point to its real particle
  Particle* RealParticle = RealNode.getState();
  rl_prtl = &RealNode;
  //point to the material properties
  mtl = RealParticle->mtl;
  //viscosity
  eta = mtl->eta; zeta = mtl->zeta; 
  
  //set states
  R_ = RealParticle->R(); rho_ = RealParticle->rho(); 
  p = RealParticle->getP(); T = RealParticle->getT();
  Cs =RealParticle->getCs(); U_ = RealParticle->U(); U_I = RealParticle->U_I;
  ShearRate_x = RealParticle->ShearRate_x, ShearRate_y = RealParticle->ShearRate_y;
  
  //set conservative values and their  intermediate values
  m = RealParticle->getMass(); V = RealParticle->V; e = RealParticle->e; 
  R_I = RealParticle->R_I;	e_I = RealParticle->e_I;
  P = RealParticle->P; P_I = RealParticle->P_I; rho_I = rho_;
  P_n = RealParticle->P_n; U_n = RealParticle->U_n; rho_n = RealParticle->rho_n;
  e_n = RealParticle->e_n;
  
  //phase filed
  phi = new double*[number_of_materials];
  lap_phi = new double*[number_of_materials];
  for(i = 0; i < number_of_materials; i++) {
    phi[i] = new double[number_of_materials];
    lap_phi[i] = new double[number_of_materials];
  }
  for(i = 0; i < number_of_materials; i++)
    for(j = 0; j < number_of_materials; j++) {
      phi[i][j] = 0.0;
      lap_phi[i][j] = 0.0;
    }
}
//----------------------------------------------------------------------------------------
//							creat an image particle
//----------------------------------------------------------------------------------------
Particle::Particle(Node &RealNode, Material &material): 
  bd(1), bd_type(0), ID(0)
{
	int i, j;
	//	cerr << "Image particle created" << endl;
	nParticle++;
	
	//give a new ID number
	Particle* RealParticle = RealNode.getState();
	//point to its real particle
	rl_prtl = &RealNode;

	//point to the material properties
	mtl = &material;
	//viscosity
	eta = RealParticle->eta; 
	zeta = RealParticle->zeta; 


	//set states
	R_ = RealParticle->R(); rho_ = RealParticle->rho_; p = RealParticle->p; T = RealParticle->T;
	Cs =RealParticle->Cs; U_ = RealParticle->U_; U_I = RealParticle->U_I;
	ShearRate_x = RealParticle->ShearRate_x, ShearRate_y = RealParticle->ShearRate_y;
	
	//set conservative values and their  intermediate values
	m = RealParticle->m; V = RealParticle->V; e = RealParticle->e; 
	R_I = RealParticle->R_I;	e_I = RealParticle->e_I;
	P = RealParticle->P; P_I = RealParticle->P_I; rho_I = rho_;
	P_n = RealParticle->P_n; U_n = RealParticle->U_n; rho_n = RealParticle->rho_n;
	e_n = RealParticle->e_n; 

	//phase filed
	phi = new double*[number_of_materials];
	lap_phi = new double*[number_of_materials];
	for(i = 0; i < number_of_materials; i++) {
		phi[i] = new double[number_of_materials];
		lap_phi[i] = new double[number_of_materials];
	}
	for(i = 0; i < number_of_materials; i++)
		for(j = 0; j < number_of_materials; j++) {
			phi[i][j] = 0.0;
			lap_phi[i][j] = 0.0;
		}

}

// Particle& Particle::operator= (const Particle& prtl) {
//   return *this;
// }
///output operation
ostream& Particle::put(ostream& ostr) const{
  ///get a pointer to initiation Singelton
  Initiation* pini = Initiation::Instance();
  ///output
  ostr<<pini->dms_length(R()[0])<<' ' <<
    pini->dms_length(R()[1])<<' '<<
    pini->dms_velocity(U()[0])<<' ' <<
    pini->dms_velocity(U()[1]) << ' ' <<
    pini->dms_volume(V) << ' ';
  ///check is it an image particle (negative ID)


  if (ID == 0) {
    ostr << 2; }
  else {
    ostr << 0;
  }
    ///0: plane particle
    ///1: polymer particle 
    ///2: image particle
//  cout << "7" << '\n';   
  return ostr;
}

//----------------------------------------------------------------------------------------
//					particle states copier for boundary particles
//----------------------------------------------------------------------------------------
void Particle::StatesCopier(int type)
{
  int i, j;
  //copy states
  assert(rl_prtl != NULL);
  Node& RealNode = *rl_prtl;
  Particle* RealParticle = RealNode.getState();
  R_ = RealParticle->R(); m = RealParticle->m;
  rho_ = RealParticle->rho_; V = RealParticle->V;
  p = RealParticle->p; T = RealParticle->T;
  rho_I = RealParticle->rho_I;
  Cs =RealParticle->Cs; U_ = RealParticle->U_; U_I = RealParticle->U_I;
  ShearRate_x = RealParticle->ShearRate_x, ShearRate_y = RealParticle->ShearRate_y;
  
  //perodic boundary
  if (type == 1 ) {
    del_phi_ = RealParticle->del_phi_;
    for(i = 0; i < number_of_materials; i++) {
      for(j = 0; j < number_of_materials; j++) {
	phi[i][j] = RealParticle->phi[i][j];
	lap_phi[i][j] = RealParticle->lap_phi[i][j];
      }
    }
  }
  
  //wall boundary
  if (type == 0) {
    phi[0][0] = 0.0;
    for(i = 1; i < number_of_materials; i++) phi[0][0] += RealParticle->phi[i][i];
  }
  
}

double Particle::getTemperature() const {
  return T;
}

inline const Vec2d& Particle::R() const {
   return R_;
}

inline Vec2d&       Particle::R() {
  return R_;
}

// inline const Vec2d& Particle::dUdt() const {
//    return dUdt;
// }

// inline Vec2d&       Particle::dUdt() {
//   return dUdt;
// }

inline const Vec2d& Particle::U() const {
   return U_;
}

inline Vec2d&       Particle::U() {
  return U_;
}

inline const double& Particle::rho() const {
   return rho_;
}

inline double&       Particle::rho() {
  return rho_;
}

const Vec2d& Particle::del_phi() const {
   return del_phi_;
}

Vec2d&       Particle::del_phi() {
  return del_phi_;
}



double Particle::getMass() const {
  return m;
}

double Particle::getEta() const {
  return eta;
}

double Particle::getZeta() const {
  return zeta;
}

double Particle::getP() const {
  return p;
}

double Particle::getCs() const {
  return Cs;
}

double Particle::getT() const {
  return T;
}

inline void Particle::setVolume(double newV) {
  V = newV;
}

inline double Particle::getVolume() const {
  return V;
}

inline void Particle::setMass(double newM) {
  m = newM;
}


//a realisation of double dispatch 
Interaction* Particle::createInteractionWith(Particle* prtl_dest,
					  Force **force, 
					  QuinticSpline &weight_function,
					  double dstc) {
  return (new Interaction(this, prtl_dest,
			  force, weight_function,
			  dstc));
}
  
Interaction* Particle::_createInteractionWith(Particle* prtl_org,
					   Force **force,
					   QuinticSpline &weight_function,
					   double dstc) {
  return (new Interaction(prtl_org, this,
			 force, weight_function,
			 dstc));
}

inline long Particle::getParticleID() const {  
  return ID;
}

inline long Particle::getRealID() const {
  if (ID==0) {
    assert(rl_prtl != NULL);
    return rl_prtl->getParticleID();
  }
  else {	  
    return ID;
  }
}


inline void Particle::setParticleID(long newID) {
  ID = newID;
}

inline int Particle::getParticleType() const {
  return 0;
}

inline int Particle::getBDtype() const {
   return bd_type;
}

inline int Particle::getbd() const {
   return bd;
 }

inline void Particle::saveRRU() {
  //save values at step n
  R_I = R_;
  rho_I = rho_;
  U_I = U_;  
}

inline void Particle::setMiddleRRU() {
  //calculate the middle values at step n+1/2
  R_ = (R_ + R_I)*0.5;
  rho_ = (rho_ + rho_I)*0.5;
  U_ = (U_ + U_I)*0.5;
}

// one step for predictor summation
inline void Particle::predictorSummationStep(const double& dt ) {
    //save values at step n
    R_I = R_;
    U_ += _dU; //renormalize velocity
    U_I = U_;
    
    //predict values at step n+1
    R_ = R_ + U_*dt;
    U_ = U_ + dUdt*dt;
    
    //calculate the middle values at step n+1/2
    R_ = (R_ + R_I)*0.5;
    U_ = (U_ + U_I)*0.5;
}

inline void Particle::correctorSummationStep(const double& dt) {
  //correction base on values on n step and change rate at n+1/2
  U_ += _dU; //renormalize velocity
  R_ = R_I + U_*dt;
  U_ = U_I + dUdt*dt;
}

inline void Particle::correctU() {
  U_ = U_ + _dU;
}

inline void Particle::correctRRU(const double& dt) {
  R_ = R_I + U_*dt;
  ///Fix:
  /// the drhodt was calculate without the coefficient \rho^2/m
  ///rho_ = rho_ + drhodt*dt;
  rho_ = rho_ + drhodt*dt*rho_*rho_/m;
  
  U_ = U_I + dUdt*dt;
}

// void Particle::setCellPosition(int ncell_i, int ncell_j) {
//   cell_i = ncell_j;
//   cell_j = ncell_j;
// }

inline void Particle::increaseShearRate(Vec2d dSRx, Vec2d dSRy) {
  ShearRate_x += dSRx;
  ShearRate_y += dSRy;  
}

inline void Particle::setShearRatetoZero() {
  ShearRate_x = 0.0;
  ShearRate_y = 0.0;
}

inline Vec2d Particle::getShearRateX() const {
  return ShearRate_x;
}

inline Vec2d Particle::getShearRateY() const {
  return ShearRate_y;
}

inline int Particle::getMaterialNumber() const {
  return mtl->number;
}

inline char* Particle::getMaterialName() const {
  return mtl->material_name;
}

inline Material* Particle::getMaterial() const {
  return mtl;
}

inline void Particle::updatePressure() {
  p = mtl->get_p(rho_);
}

inline void Particle::increaseRandomU(const Vec2d& deltaU) {
  _dU += deltaU;
}

inline void Particle::setRandomUtoZero() {
  
  _dU = 0;  
}

inline void Particle::increaseRandomUReal(const Vec2d& deltaU){
  rl_prtl->getState()->_dU += deltaU;
}

inline void Particle::increasePhi(double deltaPhi, int noi, int noj) {
  phi[noi][noj] += deltaPhi;
}

inline void Particle::increaseLapPhi(double deltaLapPhi, int noi, int noj) {
  lap_phi[noi][noj] += deltaLapPhi;
}

inline void Particle::setPhiToZero(int noi, int noj) {
  phi[noi][noj] = 0.0;
}
 
inline void Particle::setLapPhiToZero(int noi, int noj) {
  lap_phi[noi][noj] = 0.0;
}

inline double Particle::getPhiElement(int noi, int noj) const {
  return phi[noi][noj];
}

inline void Particle::increaseRandomdU(const Vec2d& deltadU) {
  _dU += deltadU;
}

inline void Particle::increasedrhodt(const double& deltadrhodt) {
  drhodt += deltadrhodt;
}

inline void Particle::increasedUdt(const Vec2d& deltadUdt) {
  dUdt += deltadUdt;
}

inline void Particle::setAlldToZero(double dt) {
  ///Fix::
  
  //cout << "_dU/dUdt = " << v_abs(_dU) / v_abs(dUdt*dt) << '\n';
  //  cout << "dUdt = " << v_abs(dUdt)  << '\n';
  dedt = 0.0;
  drhodt = 0.0;
  dUdt = 0.0;
  _dU = 0.0;
}

double Particle::getKinEnergy() const {
  return 0.5*m*dot(U_, U_);
}

void Particle::setUtoZero() {
  U_ = 0.0;  
}

inline void Particle::acceptDataCollector(DataCollector* dc) {
  dc->VisitParticle(this);
}

Particle* Particle::createGhost(Node& old_node) {
  Particle* newp = new Particle(old_node);
  ///should be ghost particle
  assert(newp->getParticleID() == 0);
  return newp;
}

vector<string> Particle::getHeader() {
  vector<string> v;
  v.push_back("Rx");
  v.push_back("Ry");
  v.push_back("Ux");
  v.push_back("Uy");
  v.push_back("V");
  v.push_back("type");
  return v;
}

Particle* Particle::getReal() {
  if (ID==0) {
#ifndef NOLOG
    log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("particle");
    LOG4CXX_DEBUG(Logger, "getReal");
#endif
    assert(rl_prtl != NULL);      
    return rl_prtl->getReal();
  }
  else {
    return this;
  }
}



double hydroConservationTest(const Llist<Node>& particle_list) {
  Vec2d sdU, sU, U;  
  //iterate the partilce list
  for (LlistNode<Node> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {    
    Node *prtl = particle_list.retrieve(p);
    sU = sU + prtl->getState()->dUdt;
    sdU = sdU + prtl->getState()->_dU;
    U = U + prtl->U();
  }
  return v_abs(U);
}

///moving test
void hydroMovingTest(const Llist<Node>& particle_list) {
  //a random double between 0.0 and 1.0
  Vec2d test_v;
  double f_rdmx = (float)RAND_MAX;
  
  //iterate the partilce list
  for (LlistNode<Node> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
    
    Node *prtl = particle_list.retrieve(p);
    if(prtl->getbd() == 0) {
      prtl->getState()->U_I = prtl->U();
      prtl->U() =  prtl->U() + prtl->U()*0.1*((float)rand() - f_rdmx / 2.0) / f_rdmx;
    }
  }  
}





///output operator for Particle
ostream& operator<< (ostream& ostr, const Particle& prtl) 
{
//  cout << "<<" << '\n';   
  return prtl.put(ostr);
}
