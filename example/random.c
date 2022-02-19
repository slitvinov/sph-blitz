#include <stdio.h>
#include <stdlib.h>
#include <sph/random.h>
#include <sph/err.h>

#define FMT "%.16g"
static const char *me = "random";
static void
usg(void)
{
    fprintf(stderr, "%s -s seed -n number\n", me);
    exit(2);
}

int
main(int argc, const char **argv)
{
    int n, s;
    double x, y;
    const char *arg;

    if (argc);
    else {
    };
    n = 10;
    s = 1234;
    while (*++argv != NULL && argv[0][0] == '-')
        switch (argv[0][1]) {
        case 'h':
            usg();
            break;
        case 's':
            argv++;
            if ((arg = *argv) == NULL)
                ABORT(("-s needs an agreement"));
            s = atoi(*argv);
            break;
        case 'n':
            argv++;
            if ((arg = *argv) == NULL)
                ABORT(("-s needs an agreement"));
            n = atoi(*argv);
            break;
        default:
            ABORT(("unknown option '%s'", argv[0]));
            exit(1);
        }

    srand(s);
    for (;;) {
        random_gaussian(&x, &y);
        printf(FMT "\n", x);
        if (!--n)
            break;
        printf(FMT "\n", y);
        if (!--n)
            break;
    }
}
