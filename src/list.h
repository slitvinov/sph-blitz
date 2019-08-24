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
    bool empty();
    bool isEnd(ListNode*);
    ListNode *first();
    ListNode *next(ListNode*);
    Particle *retrieve(ListNode*);
    void insert(ListNode*, Particle*);
    void remove(ListNode*);
    void clear();
    void clear_data();
    ~List();
};
