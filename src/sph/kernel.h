struct Kernel;
struct Kernel *kernel_ini(double smoothingLength);
int kernel_fin(struct Kernel *);
double w(struct Kernel *, double);
double F(struct Kernel *, double);
