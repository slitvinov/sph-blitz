#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

// ***** local includes *****
#include "main.h"
//#include "glbcls.h"

using namespace std;
int main(int argc, char *argv[]) {
  //check if project name specified
  if (argc<2)  {
    cout<<"No Project Name Specified!!\n";
    exit(1);
  }
  
  //initializations
  Initiation ini = *Initiation::Instance(argv[1], 
					 new SimplePolymerCreator()); 
  ParticleManager particles(ini); //initiate the particle manager
  Hydrodynamics hydro(particles, ini); //create materials, forces and real particles
  LlistNode<Node> *p = particles.cell_lists[1][1].first();
  cout.setf(ios::scientific);
  Vec2d x_dm(0.1, 0.1);
  Vec2d x_dmless = ini.non_dms_box_size(x_dm);
  Node* Pa = particles.getClosestParticle(x_dmless);
  cout << x_dm[0] << ' ' << x_dm[0] << endl;
  cout << *Pa << endl;    
  cout << "Box size: " << ini.box_size << endl;
  return 0;  
}
