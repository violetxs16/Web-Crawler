#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "crawler.h"
#include "queue.h"

webpage_t *create_webpage(){
        webpage_t *web = malloc(sizeof(webpage_t));
        web->url = NULL;
        web->html = NULL;
        web->length = 0;
        web->depth = 0;
        return web;
}
node_t *create_new(webpage_t *new_node){//Creating a new node
        node_t *newp = malloc(sizeof(node_t *));
        if(newp == NULL){
                return NULL;
        }
        //newp->webpage = malloc(sizeof(webpage_t));
        newp->webpage = new_node;
        newp->next = NULL;
        return newp;
}
bag_t *create_bag(){
        bag_t *new_bag = malloc(sizeof(bag_t));
        if(new_bag == NULL){
                return NULL;
        }
        new_bag->head = NULL;
        new_bag->tail = NULL;
        return new_bag;
}
void enqueue(bag_t *bag, webpage_t *web){
        node_t *newp = create_new(web);
        if(bag->tail == NULL){
                bag->head = bag->tail = newp;
        }
        bag->tail->next = newp;
        bag->tail = newp;
}
webpage_t *dequeue(bag_t *bag){
        if(bag->head == NULL){//Bag is empty
                return NULL;
        }
        node_t *temp = bag->head;
        bag->head = bag->head->next;
        webpage_t *web = temp->webpage;
        //free(temp);
        return web;
}
