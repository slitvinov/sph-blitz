#include "ilist.h"
#include "particle.h"
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
