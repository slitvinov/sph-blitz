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
    bool empty();
public:
    IList();
    bool isEnd(IListNode*);
    IListNode *first();
    IListNode *next(IListNode*);
    Interaction *retrieve(IListNode*);
    int length(void);
    void insert(IListNode*, Interaction*);
    void remove(IListNode*);
    ~IList();
};
