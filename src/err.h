#define WARN(x) do {                                    \
	wprint("%s:%d: ", __FILE__, __LINE__);		\
	wprint x;					\
	wprint("\n");					\
    } while (0)

#define ERR(code, x) do {			\
	WARN(x);				\
	return(code);				\
    } while (0)

#define ABORT(x) do {				\
	WARN(x);				\
	exit(2);				\
    } while (0)

int wprint(const char *, ...);
