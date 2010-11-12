#ifndef SRC_TOOLS_KERNELWRAPPER_H
#define SRC_TOOLS_KERNELWRAPPER_H
#include <iostream>

class KernelWrapper {
 public:
  KernelWrapper() {};
  virtual double w(const double dx, const double dy) const = 0;
  virtual ~KernelWrapper() {};
};

#endif // SRC_TOOLS_KERNELWRAPPER_H
