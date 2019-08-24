#define LOOP(q, l) for (p = list_first(&l);					\
    			!list_isEnd(&l, p) && (q = list_retrieve(&l, p), 1); \
			p = list_next(&l, p))
#define LOOP1(q, l) for (p1 = list_first(&l);					\
    			!list_isEnd(&l, p1) && (q = list_retrieve(&l, p1), 1); \
			p1 = list_next(&l, p1))
#define INSERT(q, l) list_insert(&l, list_first(&l), q)
#define CLEAR(l) l.clear()
#define CLEAR_DATA(l) l.clear_data()

#define ILOOP(q, l) for (p = l.first();			       \
			!l.isEnd(p) && (q = l.retrieve(p), 1); \
			p = l.next(p))

#define DINSERT(q, l) l.insert(l.first(), q)

#define IINSERT(q, l) l.insert(l.first(), q);
