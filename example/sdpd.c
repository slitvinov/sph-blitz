#include <stdio.h>
#include <stdlib.h>
#include "sph.h"
int
main(int argc, char *argv[])
{
    double Time;
    int ite;
    struct Ini ini;
    struct Kernel *kernel;

    if (argc < 2) {
      fprintf(stderr, "sdpd: error: no project name specified");
      exit(2);
    }
    srand(12345);
    iniread(argv[1], &ini);
    kernel = kernelnew(ini.h);

    mkparts(&ini, ini.materials, &ini);
    bndbuild(&ini, ini.materials);
    volmass(&ini, kernel);
    bndcond(&ini);

    Time = ini.t0;
    prtout(&ini, ini.materials, Time);
    ite = 0;
    while (Time < ini.t1) {
        if (Time + ini.tout >= ini.t1)
            ini.tout = ini.t1 - Time;
        step(&ite, &ini, &Time, ini.tout, kernel);
        prtout(&ini, ini.materials, Time);
        rstout(&ini, Time);
    }

    inifin(&ini);
    kernelfree(kernel);
    return 0;
}
