#include "list.h"
#include "particle.h"

struct List;
struct ListNode {
    void *data;
    ListNode *next;
    ListNode();
    ListNode(void*, ListNode*);
};

struct List {
    int len;
    ListNode *node;
    List();
    int endp(ListNode*);
    ListNode *first();
    ListNode *next(ListNode*);
    void *retrieve(ListNode*);
    void insert(ListNode*, void*);
    void remove(ListNode*);
    void clear();
    void clear_data();
    ~List();
};

ListNode::ListNode()
{
    data = 0;
    next = this;
}
ListNode::ListNode(void *d, ListNode *n)
{
    data = d;
    next = n;
}
List::List()
{
    node = new ListNode;
    len = 0;
}
int List::endp(ListNode *p)
{
    return p->next == node;
}
ListNode *List::first()
{
    return node;
}
ListNode *List::next(ListNode *p)
{
    return p->next;
}
void* List::retrieve(ListNode *p) {
    return p->next->data;
}
void List::insert(ListNode *p, void *d)
{
    len++;
    p->next = new ListNode(d, p->next);
}
void List::remove(ListNode *p)
{
    ListNode *t = p->next;
    p->next = t->next;
    delete t;
    len--;
}
void List::clear()
{
    while (!list_empty(this))
	remove(first());
    len = 0;
}
void List::clear_data()
{
    while (!list_empty(this)) {
	particle_fin((Particle*)retrieve(first()));
	remove(first());
    }
    len = 0;
}
List::~List()
{
    while (!list_empty(this))
	remove(first());
    delete node;
}

int list_empty(List *q) {
    return (q->node == q->node->next);
}

int list_endp(List *q, ListNode *n)
{
    return q->endp(n);
}

ListNode* list_first(List *q)
{
    return q->first();
}

ListNode* list_next(List *q, ListNode *n)
{
    return q->next(n);
}

void* list_retrieve(List *q, ListNode *n)
{
    return q->retrieve(n);
}

void list_insert(List *q, ListNode *n, void *p)
{
    q->insert(n, p);
}
void list_remove(List *q, ListNode *n)
{
    q->remove(n);
}
void list_clear(List *q)
{
    q->clear();
}
void list_clear_data(List *q)
{
    q->clear_data();
}

List *list_ini(void)
{
    List *q;
    q = new List;
    return q;
}

void list_fin(List *q)
{
    delete q;
}
