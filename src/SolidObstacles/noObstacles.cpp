///\file noObstacles.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//    a concrete soldi obstacle class: no obstalce      
//
//----------------------------------------------------------------------------------------

//local includes
#include "SolidObstacles/noObstacles.h"

using namespace std;


NoObstacles::NoObstacles(const Initiation& ini)
  :SolidObstacles(ini)
{
  // in this case (no obstacles) no need to do anything
}

//----------------------------------------------------------------------------------------
// checks if particle is located within solid object
//----------------------------------------------------------------------------------------
int NoObstacles::prtl_in_solid(const  Vec2d& coordinates) const
{
  // test position of coordinates and return 1 when particle is
  // located within the solid obstacle  and has a distance of
  // less than one supportlength to the wall surface.
  // If it is located further within the solid, the particle is ot needed at
  // all for the simulation: in this case return 2
  // if the particle is not located within the solid return 0 (i.e.
  // particle is a real particle
  //=> in the case of NO obstacles the method therefore returns always "0"
      return 0;
}

void NoObstacles::cut_ivs_file_header(ifstream& inputfile)const {
  // do nothing as no line needs to be cut off
}

void NoObstacles::set_solObs_tangentAndDistance(spParticle& prtl)const {

}

void NoObstacles::show_information() const {
  std::cerr << " NoObstacles\n";
}
