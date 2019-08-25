#include <stdlib.h>
#include "list.h"
#include "particle.h"

struct List;
struct ListNode {
    void *data;
    struct ListNode *next;
};

struct List {
    int len;
    struct ListNode *node;
};

int list_empty(struct List *q) {
    return q->node == q->node->next;
}

int list_endp(struct List *q, struct ListNode *n)
{
    return n->next == q->node;
}

struct ListNode* list_first(struct List *q)
{
    return q->node;
}

struct ListNode* list_next(struct List *q, struct ListNode *n)
{
    return n->next;
}

void* list_retrieve(struct List *q, struct ListNode *n)
{
    return n->next->data;
}

void list_insert(struct List *q, struct ListNode *n, void *p)
{
    struct ListNode *node;
    q->len++;
    node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->data = p;
    node->next = n->next;
    n->next = node;
}

void list_remove(struct List *q, struct ListNode *p)
{
    struct ListNode *t = p->next;
    p->next = t->next;
    free(t);
    q->len--;
}

void list_clear(struct List *q)
{
    while (!list_empty(q))
	list_remove(q, list_first(q));
    q->len = 0;
}

void list_clear_data(struct List *q)
{
    while (!list_empty(q)) {
	particle_fin((struct Particle*)list_retrieve(q, list_first(q)));
	list_remove(q, list_first(q));
    }
    q->len = 0;
}

struct List *list_ini(void)
{
    struct List *q;
    struct ListNode *node;
    q = (struct List*)malloc(sizeof(struct List));
    node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->data = NULL;
    node->next = node;
    q->node = node;
    q->len = 0;
    return q;
}

void list_fin(struct List *q)
{
    while (!list_empty(q))
	list_remove(q, list_first(q));
    free(q->node);
    free(q);
}
