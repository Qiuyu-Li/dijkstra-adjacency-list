#include "graph.h"
#include "minHeap.h"
#include "RList.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

#define MAX_PATHS 10    // Only want the 10 longest paths
#define FILENAME "graph1.txt"

RList* dijkstra(Graph* g, int start, int max_paths);
RList* result_paths(Graph* g,int max_paths,int nThreads);
void print_result(RList* list);

struct timeval timerStart;
void StartTimer();
double GetTimer();

int main(int argc, char** argv){

    // Thread num
    int nThreads = 30;
    if(argc > 1)
        nThreads = atoi(argv[1]);

    char* filename = FILENAME;
    Graph* g = read_graph_from_file(filename, true);   // Need to state whether the graph is directd
    printf("Graph readed in. Total vertices: %d\n",g->nv);
    StartTimer();
    RList* result = result_paths(g,MAX_PATHS,nThreads);
    const double time = GetTimer() / 1000.0;
    print_result(result);
    printf("Time costs with %d threads: %f\n",nThreads,time);
    destroy_graph(g);
    destroy_RList(result);
}


RList* dijkstra(Graph* g, int start, int max_paths){
    
    // Used to store the result
    RList* rlist = NULL;

    // A distance array is created to store the shortest path from vertex 0 to each vertex. Each element is initilized to INT_MAX.
    int nv = g->nv;
    int dist[nv];   
    for(int i = 0; i < nv; i++)
        dist[i] = INT_MAX;
    
    // Initiate a MinHeap of size nv, with all of the nodes' distance set to INT_MAX
    MinHeap* mh = init_mh(nv);
    MHNode* curr;

    //--------------------------------------
    // Mark the distance from the startpoint to itself to be zero. And update it in the heap.
    dist[start] = 0;
    UpdateNodeDistance(mh,start,0);

    while(mh->size != 0){

        // Pop the 1st element in the mh, exchange its position with the last element, and percolate down.
        curr = pop_min(mh);
        if(curr->dist == INT_MAX){// All the connectd point has been popped out
            free(curr);
            break;
        } 
        int u = curr->v;    // the position of the current node in the edge array of the graph

        // Traverse all the adjacent vertices of curr, and update their distance values
        ListNode* pcrawl = g->edges[u];
        while(pcrawl){
            int v = pcrawl->y;
            if(mh->pos[v] < mh->size && pcrawl->weight + dist[u] < dist[v]){
                dist[v] = dist[u] + pcrawl->weight;
                UpdateNodeDistance(mh,v,dist[v]);
            }
            pcrawl = pcrawl->next;
        }
        rlist = update_result(rlist,start,curr->v,curr->dist,max_paths);
        free(curr);
    }
    destroy_mh(mh);
    return rlist;
}

RList* result_paths(Graph* g,int max_paths,int nThreads){
    int nv = g->nv;
    RList *final = NULL;
    RList *new[nv];
    for(int i = 0; i < nv; i++){
        new[i] = NULL;
    }
#pragma omp parallel default(none) shared(new,g,max_paths,nv) num_threads(nThreads)
{
#pragma omp for schedule(dynamic)
    for(int i = 0; i < nv; i++){
        if(!g->edges[i]){   // Vertex does not exist
            continue;
        }
        new[i] = dijkstra(g,i,max_paths);
    }
}
    for(int i = 0; i < nv; i++){
        if(!new[i]){
            continue;
        }
        if(!final){
            final = new[i];
        }
        else{
            max_list(final,new[i]);
            destroy_RList(new[i]);
        }
    }
    return final;
}

void print_result(RList* list){
    RNode* curr = list->head;
    while(curr){
        printf("start vertex %d, end vertex %d, distance %d\n", curr->x, curr->y, curr->dist);
        curr = curr->next;
    }
}

void StartTimer(){
  gettimeofday(&timerStart, NULL);
}

double GetTimer(){
  struct timeval timerStop, timerElapsed;
  gettimeofday(&timerStop, NULL);
  timersub(&timerStop, &timerStart, &timerElapsed);

  return timerElapsed.tv_sec*1000.0+timerElapsed.tv_usec/1000.0;
}
