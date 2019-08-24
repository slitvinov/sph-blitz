class IList;
class IListNode {
    friend class IList;
private:
    struct Interaction *data;
    IListNode *next;
    IListNode();
    IListNode(Interaction*, IListNode*);
};

class IList {
private:
    int len;
    IListNode *node;
public:
    IList();
    bool empty();
    bool isEnd(IListNode*);
    IListNode *first();
    IListNode *next(IListNode*);
    Interaction *retrieve(IListNode*);
    void insert(IListNode*, Interaction*);
    void remove(IListNode*);
    void clear();
    void clear_data();
    ~IList();
};
