#include <stdlib.h>
#include "list.h"
#include "particle.h"

struct List;
struct ListNode {
    void *data;
    ListNode *next;
};

struct List {
    int len;
    ListNode *node;
};

int list_empty(List *q) {
    return q->node == q->node->next;
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
    ListNode *node;
    q->len++;
    node = (ListNode*)malloc(sizeof(ListNode));
    node->data = p;
    node->next = n->next;
    n->next = node;
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
    ListNode *node;
    q = (List*)malloc(sizeof(List));
    node = (ListNode*)malloc(sizeof(ListNode));
    node->data = NULL;
    node->next = node;
    q->node = node;
    q->len = 0;
    return q;
}

void list_fin(List *q)
{
    while (!list_empty(q))
	list_remove(q, list_first(q));
    free(q->node);
    free(q);
}
