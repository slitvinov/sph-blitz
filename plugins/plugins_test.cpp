#include <dlfcn.h>
#include <cstdlib>
#include <iostream>
int main () {

  typedef void(*Misc)(const double, const double, double&, double&);

  void* so = dlopen("libforce.so", RTLD_LAZY);
  if (!so) {
    std::cerr << "Cannot open library: " << dlerror() << '\n';
    return EXIT_FAILURE;
  }

  Misc misc = (Misc) dlsym(so, "bodyforce");
  if (!misc) {
    std::cerr << "Cannot load symbol 'hello': " << dlerror() <<
      '\n';
    dlclose(so);
    return EXIT_FAILURE;
  }


  double Fx;
  double Fy;
  (*misc)(1.0, 2.0, Fx, Fy);
  std::cerr << "Fy = " << Fy << '\n';

  dlclose(so);
  return EXIT_SUCCESS;
}
