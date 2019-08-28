#include <stdio.h>
#include <sph/kernel.h>

int
main()
{
    int i;
    int n;
    struct Kernel *kernel;
    double lo;
    double hi;
    double smoothingLength;
    double x;
    double dx;

    smoothingLength = 2.0;
    kernel = kernel_ini(smoothingLength);

    lo = 0;
    hi = 3;
    n = 100;
    dx = (hi - lo) / (n - 1);
    for (i = 0; i < n; i++) {
	x = lo + i * dx;
	printf("%.16g %.16g %.16g\n", x, w(kernel, x), F(kernel, x));
    }
    kernel_fin(kernel);
}
