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
void IList::clear()
{
    while (!empty())
	remove(first());
    len = 0;
}
void IList::clear_data()
{
    while (!empty()) {
	//particle_fin(retrieve(first()));
	remove(first());
    }
    len = 0;
}
IList::~IList()
{
    while (!empty())
	remove(first());
    delete node;
}
