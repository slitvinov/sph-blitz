#ifndef SRC_UTILITIES_UTILITIES_H
#define SRC_UTILITIES_UTILITIES_H
/// \file utilities.h

#include "src/glbtype.h"
#include <list>

class Initiation;
/// return a pointer to kernel type
spKernel chooseKernelType(const Initiation& ini);

/// return a pointer to kernel type
spKernel chooseKernelType(const std::string& kernel_type, 
                          const double supportlength, 
                          const double harmonic_n);

/// check if velocity is too big
void checkVelocity(const Initiation& ini, 
                   const std::list<spParticle>& particle_list);

/// check if force is too big
void checkForces(const Initiation& ini, 
                 const std::list<spParticle>& particle_list);
void checkForces(const Initiation& ini, spParticle prtl);


#endif //SRC_UTILITIES_UTILITIES_H
