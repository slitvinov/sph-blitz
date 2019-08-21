template <class Ldata> class Llist;
template <class Ldata> class LlistNode {
    friend class Llist<Ldata>;
private:
    Ldata *data;
    LlistNode<Ldata> *next;
    LlistNode()                         { data = 0; next = this; }
    LlistNode(Ldata *d, LlistNode<Ldata> *n)    { data = d; next = n; }
};

template <class Ldata> class Llist {
private:
    int len;
    LlistNode<Ldata> *node;

public:
    Llist() { node = new LlistNode<Ldata>; len = 0; }
    bool empty() const { return (node == node->next); }
    bool isEnd(LlistNode<Ldata> *p) const { return (p->next == node); }
    LlistNode<Ldata> *first() const { return node; }
    LlistNode<Ldata> *next(LlistNode<Ldata> *p) const     { return p->next; }
    Ldata *retrieve(LlistNode<Ldata> *p) const    { return p->next->data; }
    int length() const                  { return len; }
    inline void insert(LlistNode<Ldata> *p, Ldata *d) {
	len++;
	p->next = new LlistNode<Ldata>(d, p->next);
    }
    inline void remove(LlistNode<Ldata> *p)	{ LlistNode<Ldata> *t = p->next; p->next = t->next;
	delete t; len--; }
    inline void clear() {while (!empty()) remove(first());
	len = 0; }
    inline void clear_data()  {while (!empty()) { delete retrieve(first()); remove(first()); }
	len = 0; }
    inline ~Llist() { while (!empty()) remove(first());
	delete node; }
};
