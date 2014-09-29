// interaction.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//		defines interaction between particles
//		interaction.cpp
//----------------------------------------------------------------------------------------
#define NOMULTIPHASE

#include "interaction.h"
#include "initiation.h"
#include "material.h"
#include "quinticspline.h"
#include "force.h"
#include "glbfunc.h"
#include "node.h"
#include "particle.h"
#include <cmath>


//using namespace std;
long Interaction::nInteraction = 0;
int Interaction::number_of_materials = 0;
double Interaction::smoothinglength = 0.0;
double Interaction::art_vis = 0.0; 
double Interaction::delta = 0.0;
//----------------------------------------------------------------------------------------
//					constructor
//----------------------------------------------------------------------------------------
Interaction::Interaction(const Initiation* const ini) 
{
	//copy properties from initiation
	number_of_materials = ini->number_of_materials;
	smoothinglength = ini->smoothinglength;
	art_vis = ini->art_vis;
	delta = ini->delta;
}

//----------------------------------------------------------------------------------------
//					constructor
//----------------------------------------------------------------------------------------
Interaction::Interaction(Particle *prtl_org, Particle *prtl_dest, 
			 Force **forces,
			 QuinticSpline &weight_function, 
			 double dstc):
  Org(prtl_org), Dest(prtl_dest)
{
	//the original and the destinate particle in the reaction pair
  //	Org = prtl_org;
  //	Dest = prtl_dest;
	assert(Org->getParticleID() >= Dest->getParticleID());
	assert((Org->getParticleID()>0) 
	       || (Dest->getParticleID()>0));
	//interaction parameters
	noi = Org->getMaterialNumber();
	noj = Dest->getMaterialNumber(); 
	
	frc_ij = forces;

	//define pair values do not change in sub time steps
	mi = Org->getMass(); mj = Dest->getMass();
	rmi = 1.0/mi; rmj =1.0/mj;
	etai = Org->getEta(); etaj = Dest->getEta(); 
	zetai = Org->getZeta(); zetaj = Dest->getZeta(); 

	//the pair parameters
	rij = dstc;
	rrij = 1.0/(rij + 1.0e-30);
	eij = (Org->R() - Dest->R())*rrij;
	Wij = weight_function.w(rij);
//	Fij = weight_function.F(rij); //for BetaSpline wight fuction
	Fij = weight_function.F(rij)*rrij; //for QuinticSpline wight fuction
	LapWij = weight_function.LapW(rij); //for QuinticSpline fuction
	shear_rij = 2.0*etai*etaj*rij/(etai*(rij + 2.0*frc_ij[noj][noi].shear_slip) 
				       + etaj*(rij + 2.0*frc_ij[noi][noj].shear_slip) + 1.0e-30);
	bulk_rij =  2.0*zetai*zetaj*rij/(zetai*(rij + 2.0*frc_ij[noj][noi].bulk_slip) 
					 + zetaj*(rij + 2.0*frc_ij[noi][noj].bulk_slip) + 1.0e-30);
	nInteraction++;	
	if (std::fmod(nInteraction, 1e4) == 0) {
	  cout << "nInteraction = " << nInteraction << '\n';
	}
	
}


//destructor
Interaction::~Interaction() {
  nInteraction--;
}

//----------------------------------------------------------------------------------------
//	use old interaction object for new interaction
//----------------------------------------------------------------------------------------
void Interaction::NewInteraction(Particle *prtl_org, 
				 Particle *prtl_dest, 	
				 Force **forces,
				 QuinticSpline &weight_function, 
				 double dstc)
{
	//the original and the destinate particle in the reaction pair
	Org = prtl_org;
	Dest = prtl_dest;
	
	//interaction parameters
	noi = Org->getMaterialNumber();
	noj = Dest->getMaterialNumber(); 
	frc_ij = forces;

	//define pair values do not change in sub time steps
	mi = Org->getMass(); mj = Dest->getMass();
	rmi = 1.0/mi; rmj =1.0/mj;
	etai = Org->getEta(); etaj = Dest->getEta(); 
	zetai = Org->getZeta(); zetaj = Dest->getZeta(); 

	//the pair parameters
	rij = dstc;
	rrij = 1.0/(rij + 1.0e-30);
	eij = (Org->R() - Dest->R())*rrij;
	Wij = weight_function.w(rij);
//	Fij = weight_function.F(rij); //for BetaSpline wight fuction
	Fij = weight_function.F(rij)*rrij; //for QuinticSpline wight fuction
	LapWij = weight_function.LapW(rij); //for QuinticSpline fuction
	shear_rij = 2.0*etai*etaj*rij/(etai*(rij + 2.0*frc_ij[noj][noi].shear_slip) 
							 + etaj*(rij + 2.0*frc_ij[noi][noj].shear_slip) + 1.0e-30);
	bulk_rij =  2.0*zetai*zetaj*rij/(zetai*(rij + 2.0*frc_ij[noj][noi].bulk_slip) 
							   + zetaj*(rij + 2.0*frc_ij[noi][noj].bulk_slip) + 1.0e-30);
}


//----------------------------------------------------------------------------------------
					//renew pair parameters and changing pair values
//----------------------------------------------------------------------------------------
// Changes: Interaction object
// Depends on: Interaction Object, Org, Dest
void Interaction::RenewInteraction(const QuinticSpline &weight_function)
{
	//the pair parameters
	rij = v_abs(Org->R() - Dest->R());
	rrij = 1.0/(rij + 1.0e-30);
	eij = (Org->R() - Dest->R())*rrij;
	Wij = weight_function.w(rij);
//	Fij = weight_function.F(rij); //for BetaSpline wight fuction
	Fij = weight_function.F(rij)*rrij; //for QuinticSpline fuction
	LapWij = weight_function.LapW(rij); //for QuinticSpline fuction
	shear_rij = 2.0*etai*etaj*rij/(etai*(rij + 2.0*frc_ij[noj][noi].shear_slip) 
							 + etaj*(rij + 2.0*frc_ij[noi][noj].shear_slip) + 1.0e-30);
	bulk_rij =  2.0*zetai*zetaj*rij/(zetai*(rij + 2.0*frc_ij[noj][noi].bulk_slip) 
							   + zetaj*(rij + 2.0*frc_ij[noi][noj].bulk_slip) + 1.0e-30);
}
//----------------------------------------------------------------------------------------
//					summation the density
//					the idea is different from the original sph method
//----------------------------------------------------------------------------------------
// Changes: Org(rho:summation), Dest(rho:summation)
// Depends on: Interaction Object, Org(rho), Dest(rho)
void Interaction::SummationDensity()
{
	//summation
	Org->rho() += mi*Wij;
	if(Org->getParticleID() != Dest->getParticleID()) Dest->rho() += mj*Wij; 

}
//----------------------------------------------------------------------------------------
//					summation of the shear rates
//----------------------------------------------------------------------------------------
// Changes: Org(ShearRate_x, ShearRate_y:summation), Dest(ShearRate_x, ShearRate_y:summation)
// Depends on: Interaction Object, Org(ShearRate_x, ShearRate_y, U, rho), Dest(ShearRate_x, ShearRate_y, U, rho)
void Interaction::SummationShearRate()
{
	//pair particle state values
	double vi, vj; //particle volumes
	Vec2d Uij; //velocity, velocity difference and midddle point velocity
	Vec2d ShearRate_xi, ShearRate_yi; //shear rates
		
	//define particle state values
	vi = mi/Org->rho(); vj = mj/Dest->rho();
	Uij = Org->U() - Dest->U();
	ShearRate_xi = Uij*eij[0]*Fij*rij;
	ShearRate_yi = Uij*eij[1]*Fij*rij;
	
	//summation
// 	Org->ShearRate_x = Org->ShearRate_x + ShearRate_xi*vj;
// 	Org->ShearRate_y = Org->ShearRate_y + ShearRate_yi*vj;
// 	Dest->ShearRate_x = Dest->ShearRate_x + ShearRate_xi*vi;
// 	Dest->ShearRate_y = Dest->ShearRate_y + ShearRate_yi*vi;

	Org->increaseShearRate(ShearRate_xi*vj, ShearRate_yi*vj);
	Dest->increaseShearRate(ShearRate_xi*vi, ShearRate_yi*vi);
}
//----------------------------------------------------------------------------------------
//						phase field
//----------------------------------------------------------------------------------------
// Changes: Org(phi:summation), Dest(phi:summation)
// Depends on: Interaction Object, Org(phi, rho), Dest(phi, rho)
void Interaction::SummationPhaseField()
{
	double vi, vj; //particle volumes
	vi = mi/Org->rho(); vj = mj/Dest->rho();
	//Org->phi[noi][noj] += Wij*vj;
	Org->increasePhi(Wij*vj, noi, noj);

	if(Org->getParticleID() != Dest->getParticleID()) {
	  // Dest->phi[noj][noi] += Wij*vi;
	  Dest->increasePhi(Wij*vi, noi, noj);
	}
}
//----------------------------------------------------------------------------------------
//						density or phase gradient
//----------------------------------------------------------------------------------------
// Changes: Org(del_phi:summation), Dest(del_phi:summation)
// Depends on: Interaction Object, Org(del_phi,rho), Dest(del_phi,rho)
void Interaction::SummationPhaseGradient()
{

	double Vi, rVi, Vj, rVj; //mometum change rate
	Vi = mi/Org->rho(); Vj = mj/Dest->rho();
	rVi = 1.0/Vi; rVj = 1.0/Vj;
	double Vi2 = Vi*Vi, Vj2 = Vj*Vj;
	Vec2d dphi = eij*Fij*rij*frc_ij[noi][noj].sigma;

	Org->del_phi() += dphi*rVi*Vj2;
	Dest->del_phi() -= dphi*rVj*Vi2;
}
//----------------------------------------------------------------------------------------
//						phase field Laplacian
//----------------------------------------------------------------------------------------
void Interaction::SummationPhaseLaplacian()
{
	//pair particle state values
	double vi, vj; //particle volumes
	double lapi;
		
	//define particle state values
	vi = mi/Org->rho(); vj = mj/Dest->rho();
	lapi = LapWij;
	
	//summation
	//Org->lap_phi[noi][noj] += lapi*vj;
	Org->increaseLapPhi(lapi*vj, noi, noj);
	//Dest->lap_phi[noj][noi] += lapi*vi;
	Dest->increaseLapPhi(lapi*vi, noi, noj);
}
//----------------------------------------------------------------------------------------
//					Curvature
//----------------------------------------------------------------------------------------
void Interaction::SummationCurvature()
{
	double vi, vj; //particle volumes
	vi = mi/Org->rho(); vj = mj/Dest->rho();
	double phii = Fij*rij;
	//Org->phi[noi][noj] += phii*vj;
	Org->increasePhi(phii*vj, noi, noj);
	//Dest->phi[noj][noi] += phii*vi;
	Dest->increasePhi(phii*vi, noi, noj);
	
}
//----------------------------------------------------------------------------------------
//					update pair forces
//----------------------------------------------------------------------------------------
void Interaction::UpdateForces()
{	
  //pressure, density and inverse density and middle point pressure
  //double pi, Vi, pj, Vj;
  //define pair values change in sub time steps
  // double rhoi(Org->rho()); 
  //double rhoj(Dest->rho());
  
  double Vi(mi/Org->rho());
  double Vj(mj/Dest->rho());

  //  double pi(Org->getP()); 
  //  double pj(Dest->getP());
  
  Vec2d Ui(Org->U());
  Vec2d Uj(Dest->U());
    
  Vec2d Uij(Ui - Uj);

  //  double Uijdoteij(
  
  //pair focres or change rate
  //Vec2d dPdti; //mometum change rate
  //Vec2d dUi; //mometum change rate
  //double drhodti;

  double Vi2(Vi*Vi) ;
  double Vj2(Vj*Vj);
  
  Vec2d Uijdoteijeij(eij*dot(Uij, eij));
  
   //density change rate
  double drhodti(- Fij*rij*dot((Ui*Vi2 - Uj*Vj2), eij));  
  //momentum change rate
  //  cout << shear_rij << ' ' << bulk_rij << '\n';
  Vec2d dPdti(eij*Fij*rij*(Org->getP()*Vi2 + Dest->getP()*Vj2)
              - (  (Uij - Uijdoteijeij)*shear_rij + 
		    Uijdoteijeij*2.0*bulk_rij
         	)*Fij*(Vi2 + Vj2)
	      );
    
  //summation
  ///Fix:
  /// calculate drhodti without coefficient \rho^2/m
  //  Org->increasedrhodt(drhodti*rhoi*rVi);
  //  Dest->increasedrhodt(drhodti*rhoj*rVj);

  /// this part was removed

  //  Particle* porg(Org->getState());
  //  Particle* pdst(Dest->getState());
  
  
   Org->increasedrhodt(drhodti);
   Dest->increasedrhodt(drhodti);

   Org->increasedUdt(dPdti*rmi);
   //Org->dUdt += dPdti*rmi;
   Dest->increasedUdt(-dPdti*rmj);	  
   //Dest->dUdt -= dPdti*rmj;
  
}


//----------------------------------------------------------------------------------------
//				update forces with summation viscosity
//----------------------------------------------------------------------------------------
void Interaction::UpdateForces_vis()
{
	//pressure, density and inverse density and middle point pressure
	double pi, rhoi, rrhoi, pj, rhoj, rrhoj, _pij; 
	//velocity, velocity difference and midddle point velocity
	Vec2d Ui, Uj, Uij, _Uij; 

	//define pair values change in sub time steps
	rhoi = Org->rho(); rhoj = Dest->rho();
	rrhoi = 1.0/rhoi; rrhoj = 1.0/rhoj;
	pi = Org->getP(); pj = Dest->getP();
	
	Ui = Org->U(); Uj = Dest->U();
	Uij = Org->U() - Dest->U();
	_pij = (pi + pj)*0.5;
	_Uij = (Ui + Uj)*0.5;

	//shear rates
	Vec2d ShearRate_xi, ShearRate_yi;
	Vec2d ShearRate_xj, ShearRate_yj;
	double ShearStress[2][2], CompressRate;
	Vec2d ShearForce;

	//pair focres or change rate
	Vec2d dPdti; //mometum change rate

	
	//shear force
	//ShearRate_xi = Org->ShearRate_x; ShearRate_yi =  Org->ShearRate_y;
	//ShearRate_xj = Dest->ShearRate_x; ShearRate_yj =  Dest->ShearRate_y;
	
	ShearRate_xi = Org->getShearRateX();
	ShearRate_yi = Org->getShearRateY();
	ShearRate_xj = Dest->getShearRateX();
	ShearRate_yj = Dest->getShearRateY();

	ShearStress[0][0] = (ShearRate_xi[0] + ShearRate_xj[0]);
	ShearStress[0][1] = ((ShearRate_xi[1] + ShearRate_xj[1]) + (ShearRate_yi[0] + ShearRate_yj[0]))*0.5;
	ShearStress[1][0] = ShearStress[0][1];
	ShearStress[1][1] = (ShearRate_yi[1] + ShearRate_yj[1]);
	CompressRate = (ShearStress[0][0] + ShearStress[1][1])/3.0;
	ShearStress[0][0] -= CompressRate; 	ShearStress[1][1] -= CompressRate;

	ShearForce[0] = ShearStress[0][0]*eij[0] + ShearStress[1][0]*eij[1]; 
	ShearForce[1] = ShearStress[0][1]*eij[0] + ShearStress[1][1]*eij[1]; 
	ShearForce = ShearForce*2.0*etai*etaj/(etai + etaj) 
			   + eij*CompressRate*2.0*zetai*zetaj/(zetai + zetaj); 

	
	//define pair force or change rates
	dPdti =   eij*Fij*rij*_pij*(rrhoi*rrhoi + rrhoj*rrhoj)
			- ShearForce*Fij*rij*(rrhoi*rrhoi + rrhoj*rrhoj);
	//summation
	//Org->dUdt = Org->dUdt + dPdti*mj;
	Org->increasedUdt(dPdti*mj);
	//Dest->dUdt = Dest->dUdt - dPdti*mi;
	Dest->increasedUdt(-dPdti*mi);

}
//----------------------------------------------------------------------------------------
//					update random forces
//----------------------------------------------------------------------------------------
void Interaction::RandomForces(Wiener &wiener, 
			       double sqrtdt)
{

	//pair particle state values
	double Vi, Vj; 
	double Ti, Tj; //temperature
	//Fix::
	Vec2d v_eij(-eij[1], eij[0]) ; //90 degree rotation of pair direction
	extern double k_bltz;

	//define particle state values
	Vi = mi/Org->rho(); Vj = mj/Dest->rho();
	Ti =Org->getT(); Tj = Dest->getT();
	
	wiener.get_wiener(sqrtdt);

	//pair focres or change rate
	Vec2d _dUi; //mometum change rate
	double Vi2 = Vi*Vi, Vj2 = Vj*Vj;
	
	_dUi = eij*(wiener.Random_v)*sqrt(16.0*k_bltz*bulk_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij) +
	  v_eij*(wiener.Random_p)*sqrt(16.0*k_bltz*shear_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij);
	   
	
	//summation
	//modify for perodic boundary condition
	if(Dest->getBDtype() == 1) {
	  //Org->_dU	= Org->_dU + _dUi*rmi*0.5;
	  //Dest->rl_prtl->_dU	= Dest->rl_prtl->_dU - _dUi*rmj*0.5;
	  Org->increaseRandomU(_dUi*rmi*0.5);
	  Dest->increaseRandomUReal(- _dUi*rmi*0.5);
	}
	else {	  
	  //Org->_dU = Org->_dU + _dUi*rmi;
	  Org->increaseRandomU(_dUi*rmi);
	  //Dest->_dU = Dest->_dU - _dUi*rmj;
	  Dest->increaseRandomU(-_dUi*rmj);
	}
}
//----------------------------------------------------------------------------------------
//					update random forces with Espanol's method
//----------------------------------------------------------------------------------------
void Interaction::RandomForces_Espanol(Wiener &wiener, 
				       double sqrtdt)
{
  //pair particle state values
  //double smimj, smjmi;
  //  double Ti, Tj; //temperature
  //  Vec2d v_eij; //90 degree rotation of pair direction
  
	
  extern double k_bltz;
  
  //pair focres or change rate
  Vec2d random_force; //mometum change rate
  
  //define particle state values
  double smimj(sqrt(mi/mj)); 
  double smjmi(1.0/smimj);
  double rrhoi(1.0/Org->rho()); 
  double rrhoj(1.0/Dest->rho());


  double Ti(Org->getT()); 
  double Tj(Dest->getT());

  if ((Ti>0) && (Tj>0)) {
  
    wiener.get_wiener_Espanol(sqrtdt);
    random_force[0] = wiener.sym_trclss[0][0]*eij[0] + wiener.sym_trclss[0][1]*eij[1];
    random_force[1] = wiener.sym_trclss[1][0]*eij[0] + wiener.sym_trclss[1][1]*eij[1];
    
    Vec2d _dUi(random_force*sqrt(16.0*k_bltz*etai*etaj/(etai + etaj)*Ti*Tj/(Ti + Tj)*(rrhoi*rrhoi + rrhoj*rrhoj)*Fij) +
	       eij*wiener.trace_d*sqrt(16.0*k_bltz*zetai*zetaj/(zetai + zetaj)*Ti*Tj/(Ti + Tj)*(rrhoi*rrhoi + rrhoj*rrhoj)*Fij));
    
    //  cerr << "dUi = " << _dUi << endl;
    
    if(Dest->getBDtype() == 1) {
      Org->increaseRandomU(_dUi*smjmi*0.5);
      Dest->increaseRandomUReal( - _dUi*smjmi*0.5);
    }
    else {
      //Org->_dU	= Org->_dU + _dUi*smjmi;
      Org->increaseRandomU(_dUi*smjmi);
      //Dest->_dU	= Dest->_dU - _dUi*smimj;
      Dest->increaseRandomU(- _dUi*smimj);
    }
  }
}

///accept data collector object
void Interaction::acceptDataCollector(DataCollector* dc) {
  assert(dc != NULL);
  dc->VisitInteraction(this);
}

///get particle with larger ID
Particle* Interaction::getOrg() const {
  return Org;
}

///get particle with larger ID
Particle* Interaction::getDest() const {
  return Dest;
};


ostream& Interaction::put(ostream& ostr) const{
  ///get a pointer to initiation Singelton
  ///Initiation* pini = Initiation::Instance();
  ///output
  
  /// output nothing
  ostr << "";
//   ostr<<pini->dms_length(Org->R()[0])<<' ' <<
//     pini->dms_length(Org->R()[1])<<'\n'<<
//     pini->dms_length(Dest->R()[0])<<' ' <<
//     pini->dms_length(Dest->R()[1]) << '\n';
    ///0: plane interaction
    ///1: polymer polymer interaction
  return ostr;
}


