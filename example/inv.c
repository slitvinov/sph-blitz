#include <stdio.h>
#include <glbfunc.h>
enum { n = 3 };
int
main()
{
    int i, j, k;

    /* m : matrix([1, 2, 3], [2, 4, 5], [3, 5, 6]); */
    double a[] = { 1, 2, 3,
	2, 4, 5,
	3, 5, 6
    };
    SymmetricInverse3x3(a);
    for (k = i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	    if (j > 0) putchar(' ');
	    printf("%g", a[k++]);
	}
	putchar('\n');
    }
}
