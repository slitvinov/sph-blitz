#ifdef __cplusplus
extern "C" {
#endif
static const double pi=3.141592653589793;
double AMAX1(double a, double b);
double AMIN1(double a, double b);
inline double ABS(double a) { return fabs(a); }
double SIGN(double a, double b);
double AMAX4(double a, double b, double c, double d);
int SymmetricInverse3x3(double M[3][3]);
double Kronecker(int a, int b);
double K_sign(int a, int b);
double compare(int a, int b);
double sq(double a);
#ifdef __cplusplus
}
#endif
