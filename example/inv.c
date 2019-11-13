#include <stdio.h>
#include <stdlib.h>
#include <sph/glbfunc.h>
#include <sph/err.h>
enum { n = 3 };

static const char *me = "inv";

static void
usg(void)
{
    fprintf(stderr, "%s [9 numbers]\n", me);
    fprintf(stderr, "invert symmetric 3x3 matrix\n");
    exit(2);
}

int
main(int argc, const char **argv)
{
    int i, j, k;
    double a[n * n];

    argv++;
    for (i = 0; i < n * n; i++) {
        if (*argv == NULL)
            ABORT(("not enough arguments"));
        if (argv[0][0] == '-' && argv[0][1] == 'h')
            usg();
        a[i] = atof(*argv++);
    }

    SymmetricInverse3x3(a);
    for (k = i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (j > 0)
                putchar(' ');
            printf("%g", a[k++]);
        }
        putchar('\n');
    }
}

/*

$ ./inv 1 2 3 2 4 5 3 5 6

1 -3 2
-3 3 -1
2 -1 -0

*/
