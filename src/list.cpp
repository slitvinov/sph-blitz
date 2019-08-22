class List;
class ListNode {
    friend class List;
private:
    Particle *data;
    ListNode *next;
    ListNode()                         { data = 0; next = this; }
    ListNode(Particle *d, ListNode *n)    { data = d; next = n; }
};

class List {
private:
    int len;
    ListNode *node;

public:
    List() { node = new ListNode; len = 0; }
    bool empty() const { return (node == node->next); }
    bool isEnd(ListNode *p) const { return (p->next == node); }
    ListNode *first() const { return node; }
    ListNode *next(ListNode *p) const     { return p->next; }
    Particle *retrieve(ListNode *p) const    { return p->next->data; }
    int length() const                  { return len; }
    void insert(ListNode *p, Particle *d) {
	len++;
	p->next = new ListNode(d, p->next);
    }
    void remove(ListNode *p)	{ ListNode *t = p->next; p->next = t->next;
	delete t; len--; }
    void clear() {while (!empty()) remove(first());
	len = 0; }
    void clear_data()  {while (!empty()) { delete retrieve(first()); remove(first()); }
	len = 0; }
    ~List() { while (!empty()) remove(first());
	delete node; }
};
