#include <stdbool.h>

typedef struct ListNode_{
    int y;
    int weight;
    struct ListNode_* next;
}ListNode;

typedef struct{
    int nv;             // number of vertices
    bool directed;
    ListNode** edges;   // an array that stores the head of each list
}Graph;

Graph* init_graph(int nv, bool directed);
void add_edge(Graph* g, int x, int y, int w, bool directed);
Graph* read_graph_from_file(char* filename, bool directed);
void print_graph(Graph* g, int start, int end);
void destroy_graph(Graph* g);