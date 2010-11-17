///\file linearWall.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//    a concrete soldi obstacle class: two simple linearWalls (in x-direction)
//   wall 1 characterized by y_wall_1; solid part of wall for y<y_wall_1    
//   wall 2 characterized by y_wall_2; solid part of wall for y>y_wall_2
//   ==>y_wall_1 should be LOWER y_wall_2  
//----------------------------------------------------------------------------------------

#include <fstream>
#include <glog/logging.h>

//local includes
#include "SolidObstacles/linearWall.h"


using namespace std;

/// Cubic spline kernel (see Liu eq. (3.6)
LinearWall::LinearWall(const Initiation& ini)
  :SolidObstacles(ini)
{
  // read head of linearWall.ivs file, which contains essential data to build domain.
  // structure of first line of .ivs file:
  // y_wall
  
  const std::string inputfile =std::string(ini.Ivs_file_name);
  //check if the .ivs file exists
  ifstream fin(inputfile.c_str(), ios::in);
  if (!fin) {
    LOG(INFO)<<"Initialtion: Cannot open file: "<< inputfile <<" \n";
    exit(EXIT_FAILURE);
  }
  else LOG(INFO)<<"read linearWall data from first line in .ivs file "<< inputfile <<" \n"; 
  //read first line of linearWall.ivs file to get linearWall geometry 
  // (one input per wall)  
  fin>>y_wall_1;//wall 1: solid part for y<y_wall_1
  fin>>y_wall_2;//wall 2: solid part for y>y_wall_2
  //close inputfile
  fin.close();
}
//----------------------------------------------------------------------------------------
// checks if particle is located within solid object
//----------------------------------------------------------------------------------------
int LinearWall::prtl_in_solid(const  Vec2d& coordinates) const
{
  // test position of coordinates and return 1 when particle is
  // located within the solid obstacle  and has a distance of
  // less than one supportlength to the wall surface.
  // If it is located further within the solid, the particle is not needed at
  // all for the simulation: in this case return 2.
  // If the particle is not located within the solid return 0 (i.e.
  // particle is a real particle
  if(coordinates[1]<=y_wall_1-supportlength)
    return 2;
  else if(coordinates[1]<=y_wall_1)
    return 1;
  else if(coordinates[1]<y_wall_2)
    return 0;
  else if(coordinates[1]<=y_wall_2+supportlength)
    return 1;
  else
    return 2;
}

void LinearWall::cut_ivs_file_header(ifstream& inputfile) const {
  // very "elegant" way of cutting off first line of file
  string garbage;
  getline(inputfile, garbage);
}

void LinearWall::set_solObs_tangentAndDistance(spParticle& prtl) const {

  // here its very easy to determine the tangent (but still, the same
  // formalism is applied as for more complicated cases: 
  // the point on the solObs which is closest to the real particle is
  // taken as origin of the tangent

  // first test if it's a real particle (and not a ghost particle for SolObs
  // ...this should not be the case but one never knows...)
  if(prtl->solidObstacle_ghostParticle==0) {
    //if particle is within one suppprtlength to the lower wall: set tangent 
    if(prtl->R[1]-supportlength<=y_wall_1) {
      // set origin
      prtl->SolObs_tangent[0][0]=prtl->R[0];
      prtl->SolObs_tangent[0][1]=y_wall_1;
      // set direction of tangent line (orinetation does not matter, 
      // I picked positive direction)
      prtl->SolObs_tangent[1][0]=1;
      prtl->SolObs_tangent[1][1]=0;

      //set distance to surface
      prtl->d_realPart_solObs=prtl->R[1]-y_wall_1;
      assert(prtl->d_realPart_solObs>=0);
	
    }
    //if particle is within one suppprtlength to the upper wall: set tangent
    if(prtl->R[1]+supportlength>=y_wall_2) {
      // set origin
      prtl->SolObs_tangent[0][0]=prtl->R[0];
      prtl->SolObs_tangent[0][1]=y_wall_2;
      // set direction of tangent line (orinetation does not matter, 
      // I picked positive direction)
      prtl->SolObs_tangent[1][0]=1;
      prtl->SolObs_tangent[1][1]=0;

      //set distance to surface
      prtl->d_realPart_solObs=y_wall_2-prtl->R[1];
      assert(prtl->d_realPart_solObs>=0);
    }
  }
}
void LinearWall::show_information() const {
  std::cerr << "(kernel) LinearWall\n";
}
