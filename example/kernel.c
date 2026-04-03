#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sph.h"

static double W(struct Ini *q, double r) {
	double d = 3.0 * r * q->rh;
	double a = 3.0 - d, b = 2.0 - d, c = 1.0 - d;
	if (d < 1.0)
		return q->fw * (a*a*a*a*a - 6.0*b*b*b*b*b + 15.0*c*c*c*c*c);
	if (d < 2.0)
		return q->fw * (a*a*a*a*a - 6.0*b*b*b*b*b);
	if (d < 3.0)
		return q->fw * a*a*a*a*a;
	return 0.0;
}

static double dW(struct Ini *q, double r) {
	double d = 3.0 * r * q->rh;
	double a = 3.0 - d, b = 2.0 - d, c = 1.0 - d;
	if (d < 1.0)
		return q->fg * (a*a*a*a - 6.0*b*b*b*b + 15.0*c*c*c*c);
	if (d < 2.0)
		return q->fg * (a*a*a*a - 6.0*b*b*b*b);
	if (d < 3.0)
		return q->fg * a*a*a*a;
	return 0.0;
}

int
main(int argc, const char **argv)
{
	int i, n;
	double lo, hi, x, dx, h, norm;
	struct Ini q = {0};

	(void)argc;
	argv++;
	if (argv[0] != NULL && argv[0][0] == '-' && argv[0][1] == 'h') {
		fprintf(stderr, "kernel\nwrite kernel values\n");
		exit(2);
	}

	h = 2.0;
	norm = 63.0 / 478.0 / 3.141592653589793;
	q.h = h;
	q.rh = 1.0 / h;
	q.fw = norm * pow(q.rh, 2);
	q.fg = 15.0 * norm * pow(q.rh, 3);

	lo = 0;
	hi = 3;
	n = 100;
	dx = (hi - lo) / (n - 1);
	for (i = 0; i < n; i++) {
		x = lo + i * dx;
		printf("%.16g %.16g %.16g\n", x, W(&q, x), dW(&q, x));
	}
	return 0;
}
