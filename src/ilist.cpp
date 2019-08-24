#include "ilist.h"
#include "interaction.h"
IListNode::IListNode()
{
    data = 0;
    next = this;
}

IListNode::IListNode(Interaction *d, IListNode *n)
{
    data = d;
    next = n;
}
IList::IList()
{
    node = new IListNode;
    len = 0;
}
bool IList::empty()
{
    return (node == node->next);
}
bool IList::isEnd(IListNode *p)
{
    return (p->next == node);
}
IListNode *IList::first()
{
    return node;
}
IListNode *IList::next(IListNode *p)
{
    return p->next;
}
Interaction *IList::retrieve(IListNode *p) {
    return p->next->data;
}
int IList::length() {
    return len;
}
void IList::insert(IListNode *p, Interaction *d)
{
    len++;
    p->next = new IListNode(d, p->next);
}
void IList::remove(IListNode *p)
{
    IListNode *t = p->next;
    p->next = t->next;
    delete t;
    len--;
}
IList::~IList()
{
    while (!empty())
	remove(first());
    delete node;
}

int ilist_isEnd(IList *q, IListNode *n)
{
    return q->isEnd(n);
}

IListNode* ilist_first(IList *q)
{
    return q->first();
}

IListNode* ilist_next(IList *q, IListNode *n)
{
    return q->next(n);
}

Interaction* ilist_retrieve(IList *q, IListNode *n)
{
    return q->retrieve(n);
}

void ilist_insert(IList *q, IListNode *n, Interaction *p)
{
    q->insert(n, p);
}
void ilist_remove(IList *q, IListNode *n)
{
    q->remove(n);
}
IList *ilist_ini(void)
{
    IList *q;
    q = new IList;
    return q;
}

void ilist_fin(IList *q)
{
    delete q;
}
