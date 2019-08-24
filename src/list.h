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
    ListNode *first();
    ListNode *next(ListNode*);
    Particle *retrieve(ListNode*);
    void insert(ListNode*, Particle*);
    void remove(ListNode*);
    void clear();
    void clear_data();
    ~List();
};

int list_empty(List*);
int list_isEnd(List*, ListNode*);
