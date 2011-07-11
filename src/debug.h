#ifndef DEBUG_H
#define DEBUG_H
#include <string>
#include "initiation.h"
#include "dllist.h"

class Particle;
class Debug {
public:
  Debug(Initiation &ini);
  void checkPosition(const Llist<Particle>& particle_list, 
		     std::string const file, 
		     const int line) const;

  void checkVelocity(const Llist<Particle>& particle_list, const double dt,
		     std::string const file, 
		     const int line) const;
private:
  Initiation &ini;
};

#endif
