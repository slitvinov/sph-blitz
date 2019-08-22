#include "particle.h"
#include "list.h"
ListNode::ListNode()                         { data = 0; next = this; }
ListNode::ListNode(Particle *d, ListNode *n)    { data = d; next = n; }
List::List() { node = new ListNode; len = 0; }
bool List::empty() { return (node == node->next); }
bool List::isEnd(ListNode *p) { return (p->next == node); }
ListNode *List::first() { return node; }
ListNode *List::next(ListNode *p)     { return p->next; }
Particle *List::retrieve(ListNode *p)    { return p->next->data; }
void List::insert(ListNode *p, Particle *d) {
    len++;
    p->next = new ListNode(d, p->next);
}
void List::remove(ListNode *p)	{ ListNode *t = p->next; p->next = t->next;
    delete t; len--; }
void List::clear() {while (!empty()) remove(first());
    len = 0; }
void List::clear_data()  {while (!empty()) { delete retrieve(first()); remove(first()); }
    len = 0; }
List::~List() { while (!empty()) remove(first());
    delete node; }

