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

void List::clear()
{
    while (!list_empty(this))
	list_remove(this, list_first(this));
    len = 0;
}
void List::clear_data()
{
    while (!list_empty(this)) {
	particle_fin((Particle*)list_retrieve(this, list_first(this)));
	list_remove(this, list_first(this));
    }
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
