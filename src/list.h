class List;
class ListNode {
    friend class List;
private:
    struct Particle *data;
    ListNode *next;
    ListNode();
    ListNode(Particle*, ListNode*);
};

class List {
private:
    int len;
    ListNode *node;
public:
    List();
    bool empty0();
    bool isEnd0(ListNode*);
    ListNode *first0();
    ListNode *next0(ListNode*);
    Particle *retrieve0(ListNode*);
    void insert0(ListNode*, Particle*);
    void remove0(ListNode*);
    void clear0();
    void clear_data0();
    ~List();
};

int list_empty(List*);
int list_isEnd(List*, ListNode*);
ListNode *list_first(List*);
ListNode *list_next(List*, ListNode*);
Particle* list_retrieve(List*, ListNode*);
void list_insert(List*, ListNode*, Particle*);
void list_remove(List*, ListNode*);
void list_clear(List*);
void list_clear_data(List*);
