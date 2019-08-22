class List;
class ListNode {
    friend class List;
private:
    Particle *data;
    ListNode *next;
    ListNode();
    ListNode(Particle *d, ListNode *n);
};

class List {
private:
    int len;
    ListNode *node;
public:
    List();
    bool empty();
    bool isEnd(ListNode *p);
    ListNode *first();
    ListNode *next(ListNode *p);
    Particle *retrieve(ListNode *p);
    void insert(ListNode *p, Particle *d);
    void remove(ListNode *p);
    void clear();
    void clear_data();
    ~List();
};
