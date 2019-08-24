#define LOOP(q, l) for (p = l.first();					\
    			!list_isEnd(&l, p) && (q = l.retrieve(p), 1);	\
			p = l.next(p))
#define LOOP1(q, l) for (p1 = l.first();				\
			 !list_isEnd(&l, p1) && (q = l.retrieve(p1), 1); \
			 p1 = l.next(p1))
#define INSERT(q, l) l.insert(l.first(), q)
#define CLEAR(l) l.clear()
#define CLEAR_DATA(l) l.clear_data()

#define ILOOP(q, l) for (p = l.first();			       \
			!l.isEnd(p) && (q = l.retrieve(p), 1); \
			p = l.next(p))
