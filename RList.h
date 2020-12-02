// Short for "Reuslt List". Just want to make the main file look more elegant

typedef struct rnode_{
    int x;      // start vertex
    int y;      // end vertex
    int dist;   // distance
    struct rnode_ *next;
}RNode;         // short for Result Node

typedef struct{
    int size;       // how many paths have been stored
    RNode* head;
    RNode* tail;
}RList;

RNode* create_RNode(int x, int y, int dist);
void add_RNode(RList* list, RNode* new, int max_size);
RList* update_result(RList* list, int x, int y, int dist, int max_size);
void destroy_RList(RList* list);
void max_list(RList* final, RList* new_list);