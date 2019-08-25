class Llist;
class LlistNode {
    friend class Llist;
private:
    double *data;
    LlistNode *next;
    LlistNode()                         { data = 0; next = this; }
    LlistNode(double *d, LlistNode *n)    { data = d; next = n; }
};

class Llist {
private:
    int len;
    LlistNode *node;
    bool empty() { return (node == node->next); }
public:
    Llist() { node = new LlistNode; len = 0; }
    bool is_end(LlistNode *p) { return (p->next == node); }
    LlistNode *first() { return node; }
    LlistNode *next(LlistNode *p)     { return p->next; }
    double *retrieve(LlistNode *p)    { return p->next->data; }
    int length()                  { return len; }
    inline void insert(LlistNode *p, double *d) {
	len++;
	p->next = new LlistNode(d, p->next);
    }
    inline void remove(LlistNode *p)	{ LlistNode *t = p->next; p->next = t->next;
	delete t; len--; }
    inline ~Llist() { while (!empty()) remove(first());
	delete node; }
};
