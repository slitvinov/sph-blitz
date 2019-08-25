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

List::~List()
{
    while (!list_empty(this))
	list_remove(this, list_first(this));
    delete node;
}

int list_empty(List *q) {
    return (q->node == q->node->next);
}

int list_endp(List *q, ListNode *n)
{
    return n->next == q->node;
}

ListNode* list_first(List *q)
{
    return q->node;
}

ListNode* list_next(List *q, ListNode *n)
{
    return n->next;
}

void* list_retrieve(List *q, ListNode *n)
{
    return n->next->data;
}

void list_insert(List *q, ListNode *n, void *p)
{
    q->len++;
    n->next = new ListNode(p, n->next);
}

void list_remove(List *q, ListNode *p)
{
    ListNode *t = p->next;
    p->next = t->next;
    delete t;
    q->len--;
}

void list_clear(List *q)
{
    while (!list_empty(q))
	list_remove(q, list_first(q));
    q->len = 0;
}

void list_clear_data(List *q)
{
    while (!list_empty(q)) {
	particle_fin((Particle*)list_retrieve(q, list_first(q)));
	list_remove(q, list_first(q));
    }
    q->len = 0;
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
