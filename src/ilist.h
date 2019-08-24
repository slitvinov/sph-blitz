struct IList;
struct IListNode {
    struct Interaction *data;
    IListNode *next;
    IListNode();
    IListNode(Interaction*, IListNode*);
};

struct IList {
    int len;
    IListNode *node;
    bool empty();
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

struct IList;
struct IListNode;
struct Interaction;
int ilist_empty(struct IList*);
int ilist_isEnd(struct IList*, struct IListNode*);
struct IListNode *ilist_first(struct IList*);
struct IListNode *ilist_next(struct IList*, struct IListNode*);
struct Interaction *ilist_retrieve(struct IList*, struct IListNode*);
void ilist_insert(struct IList*, struct IListNode*, struct Interaction*);
void ilist_remove(struct IList*, struct IListNode*);
void ilist_clear(struct IList*);
void ilist_clear_data(struct IList*);
struct IList *ilist_ini(void);
void ilist_fin(struct IList*);
