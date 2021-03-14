#include <stdarg.h>
#include <stdio.h>
#include "sph/err.h"

int
wprint(const char *fmt, ...)
{
    int r;
    va_list ap;

    va_start(ap, fmt);
    r = vfprintf(stderr, fmt, ap);
    va_end(ap);
    return r;
}
