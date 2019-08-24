class List;
class ListNode {
    friend class List;
private:
    struct Particle *data;
    ListNode *next;
    ListNode();
    ListNode(Particle*, ListNode*);
};

class List;
class ListNode;
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

