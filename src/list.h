#ifdef __cplusplus
extern "C" {
#endif
struct List;
struct ListNode;
struct Particle;
int list_empty(struct List*);
int list_endp(struct List*, struct ListNode*);
struct ListNode *list_first(struct List*);
struct ListNode *list_next(struct List*, struct ListNode*);
struct Particle *list_retrieve(struct List*, struct ListNode*);
void list_insert(struct List*, struct ListNode*, struct Particle*);
void list_remove(struct List*, struct ListNode*);
void list_clear(struct List*);
void list_clear_data(struct List*);
struct List *list_ini(void);
void list_fin(struct List*);
#ifdef __cplusplus
}
#endif
