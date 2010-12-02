#ifndef SRC_TOOLS_SPHKERNELWRAPPER_H
#define SRC_TOOLS_SPHKERNELWRAPPER_H
#include "src/tools/SPHProbe/kernelwrapper.h"
#include "src/glbtype.h"

class SPHKernelWrapper : public KernelWrapper {
public:
  SPHKernelWrapper(std::string kernel_type, const double supportlength);
  double w(const double dx, const double dy) const;
private:
  boost::shared_ptr<Kernel> weight_function;
};

#endif //SRC_TOOLS_SPHKERNELWRAPPER_H
