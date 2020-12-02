typedef struct{
    int v;  // index(name) of the vertex it stores
    int dist;   // distance from the startpoint to this v, initialized to zero
}MHNode;

typedef struct{
    int size;       // current size of the MH, useful when trying to extract the last node. Note, it's not the actual size. All the element are still in the mh.
    int* pos;       // an array that stores the positions of each v
    MHNode **array;
}MinHeap;

MinHeap* init_mh(int nv);
void percolate_up(MinHeap* mh, int v);
void percolate_down(MinHeap* mh, int i);
void UpdateNodeDistance(MinHeap* mh, int v, int dist);
MHNode* pop_min(MinHeap* mh);
void destroy_mh(MinHeap *mh);