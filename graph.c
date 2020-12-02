#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

Graph* init_graph(int nv, bool directed){
    Graph* g = malloc(sizeof(Graph));
    g->nv = nv;
    g->edges = malloc(nv*sizeof(ListNode*));
    for(int i = 0; i < nv; i++){
        g->edges[i] = NULL;
    }
    g->directed = directed;
    return g;
}

void add_edge(Graph* g, int x, int y, int w, bool directed){
    ListNode* new_x  = malloc(sizeof(ListNode));
    new_x->y = y;
    new_x->weight = w;
    new_x->next = g->edges[x];
    g->edges[x] = new_x;
    if(directed == false)
        add_edge(g,y,x,w,true);
}

Graph* read_graph_from_file(char* filename, bool directed){
    FILE* file = fopen(filename,"r");
    int nv, ne, x, y, w;

    char* line = NULL;
    size_t len = 0;
    getline(&line, &len, file);
    char first_char = line[0];
    while(first_char == '#'){
        getline(&line, &len, file);
        first_char = line[0];
    }
    sscanf(line,"%d %d",&nv,&ne);
    Graph* g = init_graph(nv,directed);
    for(int i = 0; i < ne; i++){
        fscanf(file,"%d %d %d",&x,&y,&w);
        add_edge(g,x,y,w,directed);
    }
    free(line);
    fclose(file);
    return g;
}

// print graph given the start and end position in the vertex array
void print_graph(Graph* g, int start, int end){
    for(int i = start; i < end; i++){
        ListNode* pcrawl = g->edges[i];
        printf("Vertex %d",i);
        while(pcrawl){
            printf("-> Vertex %d (weight %d)",pcrawl->y, pcrawl->weight);
            pcrawl = pcrawl->next;
        }
        printf("\n");
    }
}

void destroy_graph(Graph* g){
    ListNode *curr, *next;
    for(int i = 0; i < g->nv; i++){
        for(curr = g->edges[i]; curr; curr = next){
            next = curr->next;
            free(curr);
        }
    }
    free(g->edges);
    free(g);
}