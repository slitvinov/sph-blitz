struct Kernel {
    double reciprocH;
    double factorW;
    double factorGradW;
    double smoothingLength;
};

int kernel_ini(double smoothingLength, struct Kernel *);
double w(struct Kernel *, double);
double F(struct Kernel *, double);
