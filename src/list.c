#include "sph/list.h"
#include "sph/macro.h"
#include <stdlib.h>

struct List;
struct ListNode {
  void *data;
  struct ListNode *next;
};

struct List {
  struct ListNode *node;
};

int list_endp(struct List *q, struct ListNode *n) { return n->next == q->node; }

struct ListNode *list_first(struct List *q) {
  return q->node;
}

struct ListNode *list_next(struct List *q, struct ListNode *n) {
  USED(q);
  return n->next;
}

void *list_retrieve(struct List *q, struct ListNode *n) {
  USED(q);
  return n->next->data;
}

void list_insert(struct List *q, struct ListNode *n, void *p) {
  struct ListNode *node;

  node = malloc(sizeof(struct ListNode));
  node->data = p;
  node->next = n->next;
  n->next = node;
}

void list_remove(struct List *q, struct ListNode *p) {
  struct ListNode *t = p->next;

  p->next = t->next;
  free(t);
}

void list_clear(struct List *q) {
  while (q->node != q->node->next)
    list_remove(q, q->node);
}

struct List *list_ini(void) {
  struct List *q;
  struct ListNode *node;

  q = malloc(sizeof(struct List));
  node = malloc(sizeof(struct ListNode));
  node->data = NULL;
  node->next = node;
  q->node = node;
  return q;
}

void list_fin(struct List *q) {
  while (q->node != q->node->next)
    list_remove(q, q->node);
  free(q->node);
  free(q);
}
