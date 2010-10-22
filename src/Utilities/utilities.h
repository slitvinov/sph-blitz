#ifndef SRC_UTILITIES_UTILITIES_H
#define SRC_UTILITIES_UTILITIES_H
/// \file utilities.h

#include "src/glbtype.h"

class Initiation;
/// return a pointer to kernel type
spKernel chooseKernelType(const Initiation& ini);

/// return a pointer to kernel type
spKernel chooseKernelType(const std::string& kernel_type, 
                          const double supportlength, 
                          const double harmonic_n);

#endif //SRC_UTILITIES_UTILITIES_H
