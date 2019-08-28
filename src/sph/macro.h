#define LOOP1(q, l) for (p1 = list_first(&(l));				\
			 !list_endp(&l, p1) && (q = list_retrieve(&(l), p1), 1); \
			 p1 = list_next(&(l), p1))

#define LOOP1_P(q, l) for (p1 = list_first((l));				\
			 !list_endp(l, p1) && (q = (struct Particle*)list_retrieve((l), p1), 1); \
			 p1 = list_next((l), p1))

#define INSERT(q, l) list_insert(&l, list_first(&l), q)
#define CLEAR(l) list_clear(&(l))

#define ILOOP_P(q, l) for (p = list_first((l));				\
			  !list_endp((l), p) && (q = (struct Pair*)list_retrieve((l), p), 1); \
			  p = list_next((l), p))


#define DINSERT(q, l) l->insert(l->first(), q)

#define IINSERT_P(q, l) list_insert(l, list_first(l), q)

#define LOOP_P(q, l) for (p = list_first((l));				\
			  !list_endp((l), p) && (q = (struct Particle*)list_retrieve((l), p), 1); \
			  p = list_next((l), p))

#define INSERT_P(q, l) list_insert(l, list_first(l), q)

#define DLOOP_P(q, l) for (p = list_first((l));				\
			  !list_endp((l), p) && (q = (double*)list_retrieve((l), p), 1); \
			  p = list_next((l), p))

#define	USED(x)		if(x);else{}
