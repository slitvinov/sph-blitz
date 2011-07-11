#include <iostream>
#include <cmath>
#include "debug.h"
#include "particle.h"

Debug::Debug(Initiation &ini):
  ini(ini) {
}

void Debug::checkPosition(const Llist<Particle>& particle_list,
			  std::string const file, 
			  const int line) const {

  for (LlistNode<Particle> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
    Particle *prtl = particle_list.retrieve(p);
    if(fabs(prtl->R[0]) >= 2.0*ini.box_size[0] || fabs(prtl->R[1]) >= 2.0*ini.box_size[1]) {
      cout<<"Boundary: the particles run out too far away from the domain! \n";
      std::cout << "box_size: " << ini.box_size << std::endl;
      std::cout << "prtl->R: " << prtl->R << std::endl;
      std::cout << file << ':' << line << std::endl;
      exit(1);
    }
  }
}


void Debug::checkVelocity(const Llist<Particle>& particle_list,
			  const double dt, 
			  std::string const file, 
			  const int line) const {
  for (LlistNode<Particle> *p = particle_list.first(); 
       !particle_list.isEnd(p); 
       p = particle_list.next(p)) {
    Particle *prtl = particle_list.retrieve(p);
    if(fabs(prtl->U[0]*dt) >= 2.0*ini.box_size[0] || fabs(prtl->U[1]*dt) >= 2.0*ini.box_size[1]) {
      std::cout<<"Debug: velocity of the particle is too big \n";
      std::cout << "box_size: " << ini.box_size << std::endl;
      std::cout << "prtl->R: " << prtl->R << std::endl;
      std::cout << "prtl->U: " << prtl->U << std::endl;
      std::cout << file << ':' << line << std::endl;
      exit(1);
    }
  }
}
