#ifdef __cplusplus
extern "C" {
#endif
struct List;
struct ListNode;
struct Particle;
int list_empty(List*);
int list_isEnd(List*, ListNode*);
ListNode *list_first(List*);
ListNode *list_next(List*, ListNode*);
Particle *list_retrieve(List*, ListNode*);
void list_insert(List*, ListNode*, Particle*);
void list_remove(List*, ListNode*);
void list_clear(List*);
void list_clear_data(List*);
List *list_ini(void);
void list_fin(List*);
#ifdef __cplusplus
}
#endif
