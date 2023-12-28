#ifndef QUEUE_WRAPPER_H
#define QUEUE_WRAPPER_H

#include <stdbool.h>
#include "crawler.h"
#include <stdio.h>
#include <stdlib.h>

struct webpage;
typedef struct node node_t;

struct node{//Node implementation
        struct webpage *webpage;
        node_t *next;
};


typedef struct bag{//Queue implementation
        node_t *head;
        node_t *tail;
} bag_t;

node_t *create_new(struct webpage *new_node);
bag_t *create_bag();
void enqueue(bag_t *bag, struct webpage *web);
struct webpage *dequeue(bag_t *bag);
struct webpage *create_webpage();

#endif
