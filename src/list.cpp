#include "list.h"
#include "particle.h"
ListNode::ListNode()
{
    data = 0;
    next = this;
}
ListNode::ListNode(Particle *d, ListNode *n)
{
    data = d;
    next = n;
}
List::List()
{
    node = new ListNode;
    len = 0;
}
bool List::empty0()
{
    return (node == node->next);
}
bool List::isEnd0(ListNode *p)
{
    return p->next == node;
}
ListNode *List::first0()
{
    return node;
}
ListNode *List::next0(ListNode *p)
{
    return p->next;
}
Particle *List::retrieve0(ListNode *p) {
    return p->next->data;
}
void List::insert0(ListNode *p, Particle *d)
{
    len++;
    p->next = new ListNode(d, p->next);
}
void List::remove0(ListNode *p)
{
    ListNode *t = p->next;
    p->next = t->next;
    delete t;
    len--;
}
void List::clear0()
{
    while (!empty0())
	remove0(first0());
    len = 0;
}
void List::clear_data0()
{
    while (!empty0()) {
	particle_fin(retrieve0(first0()));
	remove0(first0());
    }
    len = 0;
}
List::~List()
{
    while (!empty0())
	remove0(first0());
    delete node;
}

int list_empty(List *q) {
    return q->empty0();
}

int list_isEnd(List *q, ListNode *n)
{
    return q->isEnd0(n);
}

ListNode* list_first(List *q)
{
    return q->first0();
}

ListNode* list_next(List *q, ListNode *n)
{
    return q->next0(n);
}

Particle* list_retrieve(List *q, ListNode *n)
{
    return q->retrieve0(n);
}

void list_insert(List *q, ListNode *n, Particle *p)
{
    q->insert0(n, p);
}
void list_remove(List *q, ListNode *n)
{
    q->remove0(n);
}
void list_clear(List *q)
{
    q->clear0();
}
void list_clear_data(List *q)
{
    q->clear_data0();
}

List *list_new(void)
{
    List *q;
    q = new List;
    return q;
}

void list_fin(List *q)
{
    delete q;
}
