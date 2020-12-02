#include "minHeap.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

MinHeap* init_mh(int nv){
    MinHeap* mh = malloc(sizeof(MinHeap));
    mh->size = nv;
    mh->pos = malloc(nv*sizeof(int));
    mh->array = malloc(nv*sizeof(MHNode*));
    for(int i = 0; i < nv; i++){
        mh->pos[i] = i;
        mh->array[i] = malloc(sizeof(MHNode));
        mh->array[i]->v = i;
        mh->array[i]->dist = INT_MAX;
    }
    return mh;
}

// Start percolating up from v. Helper function for UpdateNodeDistance
void swapMHNode(MHNode** a, MHNode** b){
    MHNode* t = *a;
    *a = *b;
    *b = t;
}

void percolate_up(MinHeap* mh, int i){
    MHNode *child, *parent;
    while(i >= 0 && mh->array[i]->dist < mh->array[(i-1)/2]->dist){
        mh->pos[mh->array[i]->v] = (i-1)/2;
        mh->pos[mh->array[(i-1)/2]->v] = i;
        swapMHNode(&mh->array[i], &mh->array[(i-1)/2]);
        i = (i-1)/2;
    }
}

// Recursively percolate down the whole heap tree. Helper function for pop_min
void percolate_down(MinHeap* mh, int i){
    int smallest, left, right;
    smallest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;
 
    if (left < mh->size && mh->array[left]->dist < mh->array[smallest]->dist)
        smallest = left;
    if (right < mh->size && mh->array[right]->dist < mh->array[smallest]->dist)
        smallest = right;
 
    if (smallest != i){
        mh->pos[mh->array[smallest]->v] = i;
        mh->pos[mh->array[i]->v] = smallest;
        swapMHNode(&mh->array[smallest], &mh->array[i]);
        percolate_down(mh, smallest);
    }
}

void UpdateNodeDistance(MinHeap* mh, int v, int dist){
    int i = mh->pos[v];
    mh->array[i]->dist = dist;
    percolate_up(mh,i);
}

MHNode* pop_min(MinHeap* mh){
    if(mh->size == 0)
        return NULL;
    MHNode* root = mh->array[0];
    mh->array[0] = mh->array[mh->size-1];
    mh->pos[mh->array[mh->size-1]->v] = 0;
    mh->pos[mh->array[0]->v] = mh->size-1;  // This node has already been popped. This is for judging whether the node still exists (i.e. pos[node->v] > size-1)
    mh->size--;
    percolate_down(mh, 0);
    return root;
}

void destroy_mh(MinHeap *mh){
    for(int i = 0; i < mh->size; i++)
        free(mh->array[i]);
    free(mh->array);
    free(mh->pos);
    free(mh);
}
