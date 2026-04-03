#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sph.h"

enum { N = 999 };
static const char *me = "list";
static void
usg(void)
{
    fprintf(stderr, "%s < command.file\n", me);
    fprintf(stderr, "commands:\n");
    fprintf(stderr, "\tinsert [integer]\n");
    fprintf(stderr, "\ttraverse\n");
    fprintf(stderr, "\tlength\n");
    fprintf(stderr, "\tremove\n");
    exit(2);
}

static int eq(const char *, const char *);

#define ARG(x)							\
    do {							\
	c = strtok(NULL, sep);					\
	if (c == NULL)						\
	    ABORT(("wrong command '%s'",p));			\
	(x) = atoi(c);						\
    } while (0)

#define LOOP()							     \
    for (n = listfirst((l));					     \
	 !listendp((l), n) && (x = (int*)listget((l), n), 1); \
	 n = listnext((l), n))

static char *get(char *, FILE *);

int
main(int argc, const char **argv)
{
    struct List *l;
    struct ListNode *n;
    char s[N], p[N], sep[] = " \t\n";
    char *c;
    int *x;

    if (argc);
    else {
    };
    argv++;
    if (argv[0] != NULL && argv[0][0] == '-' && argv[0][1] == 'h')
        usg();
    l = listnew();
    while (get(s, stdin)) {
        strncpy(p, s, N);
        if ((c = strtok(s, sep))) {
            if (eq(c, "insert")) {
                x = malloc(sizeof(*x));
                ARG(*x);
                n = listfirst(l);
                listins(l, n, x);
            } else if (eq(c, "traverse")) {
                LOOP()
                    printf("%d\n", *x);
            } else if (eq(c, "remove")) {
                n = listfirst(l);
                x = listget(l, n);
                free(x);
                listrm(l, n);
            } else
                ABORT(("unknown command: %s", p));
        }
    }
    LOOP()
        free(x);
    listfree(l);
}

static char *
get(char *s, FILE * f)
{
    int n;

    if (fgets(s, N, f) == NULL)
        return NULL;
    n = strlen(s);
    if (s[n - 1] == '\n')
        s[n - 1] = '\0';
    return s;
}

static int
eq(const char *a, const char *b)
{
    return strncmp(a, b, N) == 0;
}
