/// \file utilities.cpp
#include <glog/logging.h>
#include <boost/smart_ptr/make_shared.hpp>
#include "src/Utilities/utilities.h"
#include "src/initiation.h"
#include "src/Kernel/quinticspline.h"
#include "src/Kernel/cubicspline.h"
#include "src/Kernel/cubicspline1D.h"
#include "src/Kernel/bspline.h"
#include "src/Kernel/harmonic.h"

spKernel chooseKernelType(const Initiation& ini) {
  return chooseKernelType(ini.kernel_type, ini.supportlength, ini.harmonic_n);
}


spKernel chooseKernelType(const std::string& kernel_type, 
                          const double supportlength, 
                          const double harmonic_n) {
  spKernel weight_function;
  if  (kernel_type == "CubicSpline")   {
    weight_function = boost::make_shared<CubicSpline>(supportlength); 
  } 
  else if (kernel_type == "BSpline")   {
    weight_function = boost::make_shared<BSpline>(supportlength); 
  } 
  else if (kernel_type == "QuinticSpline")   {
    weight_function = boost::make_shared<QuinticSpline>(supportlength);
  } 
  else if (kernel_type == "CubicSpline1D")   {
    weight_function = boost::make_shared<CubicSpline1D>(supportlength);
  }
  else if (kernel_type == "Harmonic")   {
    weight_function = boost::make_shared<Harmonic>(supportlength, harmonic_n);
  }
  else {
    LOG(ERROR) << " unknown kernel type (KERNEL_TYPE in configuration file)\n" 
	       << " KERNEL_TYPE: " << kernel_type;
    exit(EXIT_FAILURE);
  }
  return weight_function;
}
