///\file cavity.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//    a concrete soldi obstacle class: a simple cavity      
//
//----------------------------------------------------------------------------------------

#include <fstream>
#include <glog/logging.h>

//local includes
#include "SolidObstacles/cavity.h"


using namespace std;

/// Cubic spline kernel (see Liu eq. (3.6)
Cavity::Cavity(const Initiation& ini)
  :SolidObstacles(ini)
{
  // read head of cavity.ivs file, which contains essential data to buidl domain
  // structure of first line of .ivs file:
  // y_surface, depth, width
  
  const std::string inputfile =std::string(ini.Ivs_file_name);
  //check if the .ivs file exists
  ifstream fin(inputfile.c_str(), ios::in);
  if (!fin) {
    LOG(INFO)<<"Initialtion: Cannot open file: "<< inputfile <<" \n";
    exit(EXIT_FAILURE);
  }
  else LOG(INFO)<<"read cavity data from first line in .ivs file "<< inputfile <<" \n"; 
  //read first line of cavity.ivs file to get cavity geometry  
  fin>>y_surface;
  fin>>depth;
  fin>>width;  
  //close inputfile
  fin.close();
  if(y_surface<depth) {
    LOG(INFO)<<"There is something wrong with the cavity geometry: \n";
    LOG(INFO)<<"the y-coordinate of the surface can not be < than the depth!!! \n";
    exit(EXIT_FAILURE);
  }
  //calculate the gemetrical dimensions
  //(cavity centered in domain in x-direction by default
  y_bottom=y_surface-depth;
  x_wall_left=(domain_size[0]-width)/2.0;
  x_wall_right=(domain_size[0]+width)/2.0;
}
//----------------------------------------------------------------------------------------
// checks if particle is located within solid object
//----------------------------------------------------------------------------------------
int Cavity::prtl_in_solid(const  Vec2d& coordinates) const
{
  // test position of coordinates and return 1 when particle is
  // located within the solid obstacle (= cavity walls) and has a distance of
  // less than one supportlength to the wall surface.
  // If it is located further within the solid, the particle is not needed at
  // all for the simulation: in this case return 2
  // if the particle is not located within the solid return 0 (i.e.
  // particle is a real particle
  if(coordinates[0]<=x_wall_left-supportlength)
    if(coordinates[1]<=y_surface-supportlength)
      return 2;
    else if(coordinates[1]<=y_surface)
      return 1;
    else
      return 0;
  else if(coordinates[0]<=x_wall_left)
    if(coordinates[1]<=y_bottom-supportlength)
      return 2;
    else if(coordinates[1]<=y_surface)
      return 1;
    else 
      return 0;
  else if (coordinates[0]<=x_wall_right)
    if(coordinates[1]<=y_bottom-supportlength)
      return 2;
    else  if(coordinates[1]<=y_bottom)
      return 1;
    else
      return 0;
  else if (coordinates[0]<=x_wall_right+supportlength)
    if(coordinates[1]<=y_bottom-supportlength)
      return 2;
    else if(coordinates[1]<=y_surface)
      return 1;
    else  
      return 0;
  else
    if(coordinates[1]<=y_surface-supportlength)
      return 2;
    else if(coordinates[1]<=y_surface)
      return 1;
    else
      return 0;
}

void Cavity::cut_ivs_file_header(ifstream& inputfile) const {
  // very "elegant" way of cutting off first line of file
  string garbage;
  getline(inputfile, garbage);
}

void Cavity::set_solObs_tangentAndDistance(spParticle& prtl)const {
  
}

void Cavity::show_information() const {
  std::cerr << "(kernel) Cavity\n";
}
