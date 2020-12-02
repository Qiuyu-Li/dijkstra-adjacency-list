#include "RList.h"
#include "minHeap.h"
#include <stdlib.h>
#include <stdio.h>

RNode* create_RNode(int x, int y, int dist){
    RNode* new = malloc(sizeof(RNode));
    new->x = x;
    new->y = y;
    new->dist = dist;
    new->next = NULL;
}

void add_RNode(RList* list, RNode* new, int max_size){
    // Default: the list is not empty
    RNode* crawl = list->head;
    if(new->dist < crawl->dist && list->size == max_size){
        return;
    }
    while(crawl->next && crawl->next->dist < new->dist){
        crawl = crawl->next;
    }
    if(crawl->next){
        if(new == crawl->next)
            return;
        new->next = crawl->next;
        crawl->next = new;
    }
    else{
        if(list->tail)
            list->tail->next = new;
        list->tail = new;
    }
    if(list->size < max_size){
        list->size++;
    }
    else{
        RNode* head = list->head;
        list->head = list->head->next;
        free(head);
        head = NULL;
    }
}

RList* update_result(RList* list, int x, int y, int dist, int max_size){
    if(!list){
        list = malloc(sizeof(RList));
        list->size = 0;
        list->head = NULL;
        list->tail = NULL;
    }
    if(!list->head){
        list->head = create_RNode(x,y,dist);
        list->tail = list->head;
        list->size++;
    }
    else{
        if(dist < list->head->dist){
            return list;
        }
        RNode* new = create_RNode(x,y,dist);
        add_RNode(list,new,max_size);                 
    }
    return list;
}

void destroy_RList(RList* list){
    RNode* head;
    for(int i = 0; i < list->size; i++){
        head = list->head;
        list->head = list->head->next;
        free(head);
    }
    free(list);
}

void max_list(RList* final, RList* new){
    if(new->tail->dist < final->head->dist)
        return;
    else{
        RNode *next, *rcrawl = new->head;
        while(rcrawl){
            next = rcrawl->next;
            update_result(final, rcrawl->x, rcrawl->y, rcrawl->dist, final->size);   // so that the "new" list won't be affected
            rcrawl = next;
        }
    }
}

