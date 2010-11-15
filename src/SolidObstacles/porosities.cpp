///\file porosities.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//    a concrete soldi obstacle class: a simple porosities      
//
//----------------------------------------------------------------------------------------

#include <fstream>
#include <glog/logging.h>

//local includes
#include "SolidObstacles/porosities.h"


using namespace std;

/// Cubic spline kernel (see Liu eq. (3.6)
Porosities::Porosities(const Initiation& ini)
  :SolidObstacles(ini)
{
  // read head of porosities.ivs file, which contains essential data to build domain
  // structure of  .ivs file header:
  // ->number of zylinders
  // ->Pos_ci[0] Pos_ci[1] Rad_i (x-center, y-center, radius; one row for each zylinder)
  
  const std::string inputfile =std::string(ini.Ivs_file_name);
  //check if the .ivs file exists
  ifstream fin(inputfile.c_str(), ios::in);
  if (!fin) {
    LOG(INFO)<<"Initialtion: Cannot open file: "<< inputfile <<" \n";
    exit(EXIT_FAILURE);
  }
  else LOG(INFO)<<"read porosities data from first line in .ivs file "<< inputfile <<" \n"; 
  //read first header of porosities.ivs file to get porosities geometry  
  fin>>N_zyl;
  for (int i=0;i<N_zyl;i++) {
    // intermediate variable to store position of center of zylinder i
    Vec2d Pos_ci;
    // intermediate variable to store radius of center of zylinder i
    double rad_i;
    fin>>Pos_ci[0];
    fin>>Pos_ci[1];
    fin>>rad_i;
    assert(rad_i>0);
    //add current zylinder heotery information to vectors containing
    // all zylinders' geometrical info
    all_Zyl_centers.push_back(Pos_ci);
    all_Zyl_radii.push_back(rad_i);      
  }
  //close inputfile
  fin.close();
 
}
//----------------------------------------------------------------------------------------
// checks if particle is located within solid object
//----------------------------------------------------------------------------------------
int Porosities::prtl_in_solid(const  Vec2d& coordinates) const
{
  // test position of coordinates and return 1 when particle is
  // located within the solid obstacle (= porosities walls) and has a distance of
  // less than one supportlength to the wall surface.
  // If it is located further within the solid, the particle is not needed at
  // all for the simulation: in this case return 2
  // if the particle is not located within the solid return 0 (i.e.
  // particle is a real particle
  for (int i=0;i<N_zyl;i++) {
    if(v_abs(coordinates-all_Zyl_centers[i])<all_Zyl_radii[i]-supportlength)
      return 2;
    else if (v_abs(coordinates-all_Zyl_centers[i]) <=all_Zyl_radii[i])
      return 1;
  }
  //if particle is not located within any of teh zylinders:
  return 0;
}

void Porosities::cut_ivs_file_header(ifstream& inputfile) const {
  // very "elegant" way of cutting off first line of file
  string garbage;
  // for each zylinder one line plus first line with N_zyl
  for(int i=0;i<N_zyl+1;i++) {
    getline(inputfile, garbage);
  }
}

void Porosities::set_solObs_tangentAndDistance(spParticle& prtl)const {

  // first test if it's a real particle (and not a ghost particle for SolObs
  // ...this should not be the case but one never knows...)
  if(prtl->solidObstacle_ghostParticle==0) {
    //if particle is within one suppprtlength to one of the zylinders:
    // set tangent and distance
    //\todo{the fact that distances and tangents are only set for particles which are located within one supportlength to the wall surface could possibly be problematic if in the time between set of tangent and distance and force calculation a  particle originally >supportlength away from the surface  has moved closer to it. Therefore: be sure that method is always called directly before forces calculation (which is done so far)!}
    for (int i=0;i<N_zyl;i++) {
      //if particle is within supportlength of the zylinder surface
      if(v_abs(prtl->R-all_Zyl_centers[i])<=all_Zyl_radii[i]+supportlength) {
	//set distance to zylinder surface
	prtl->d_realPart_solObs=v_abs(prtl->R-all_Zyl_centers[i])-all_Zyl_radii[i];
	//set tangent:
	 // set origin
	prtl->SolObs_tangent[0]=(prtl->R-all_Zyl_centers[i])
	  *all_Zyl_radii[i]/v_abs(prtl->R-all_Zyl_centers[i]);
	
	// set direction of tangent line (orinetation does not matter)
	// tangent direction is direction of vector which has zero
	// scalar product with radius vector to the tangent origin
	// (=tangent origin - zylinder center)
	const Vec2d rad_vector=prtl->SolObs_tangent[0]-all_Zyl_centers[i];
	// solving the equation "scalarproduct=0" between the 
	// rad_vector (a,b)  and the searched direction
	// vector (x,y) and arbitrarily choosing x=1,
	// one obtains y=-ax/b
	// there are problems when b=0 and therefore this case is treated
	// separately:
	if (rad_vector[1]==0) {
	  prtl->SolObs_tangent[1][0]=0;
	  prtl->SolObs_tangent[1][1]=1;
	}
	else {
	  prtl->SolObs_tangent[1][0]=1;
	  prtl->SolObs_tangent[1][1]=-rad_vector[0]*1.0/rad_vector[1];	  
	}
      }
    }
  }
}

void Porosities::show_information() const {
  std::cerr << "(kernel) Porosities\n";
}
