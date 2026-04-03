#include <stdio.h>
#include <stdlib.h>
#include "sph.h"

static const char *me = "kernel";

static void
usg(void)
{
    fprintf(stderr, "%s\n", me);
    fprintf(stderr, "write kernel values\n");
    exit(2);
}


int
main(int argc, const char **argv)
{
    int i;
    int n;
    struct Kernel *kernel;
    double lo;
    double hi;
    double h;
    double x;
    double dx;

    if (argc);
    else {
    };
    argv++;
    if (argv[0] != NULL && argv[0][0] == '-' && argv[0][1] == 'h')
        usg();

    h = 2.0;
    kernel = kernelnew(h);

    lo = 0;
    hi = 3;
    n = 100;
    dx = (hi - lo) / (n - 1);
    for (i = 0; i < n; i++) {
        x = lo + i * dx;
        printf("%.16g %.16g %.16g\n", x, w(kernel, x), F(kernel, x));
    }
    kernelfree(kernel);
    return 0;
}
