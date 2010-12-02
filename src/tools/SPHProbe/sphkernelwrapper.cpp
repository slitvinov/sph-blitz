#include "src/tools/SPHProbe/sphkernelwrapper.h"
#include "src/Utilities/utilities.h"
#include "src/Kernel/kernel.h"

SPHKernelWrapper::SPHKernelWrapper(std::string kernel_type, const double supportlength) {
  boost::shared_ptr<Kernel> weight_function = chooseKernelType(kernel_type, supportlength, 3.0);
}

double SPHKernelWrapper::w(const double dx, const double dy) const {
  const double dr = sqrt(dx*dx + dy*dy);
  return weight_function->w(dr);
}
