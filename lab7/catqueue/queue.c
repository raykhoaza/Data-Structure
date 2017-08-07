// $Id: queue.c,v 1.18 2014-05-23 02:53:10-07 - - $
// KHOA LUONG KLUON7
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf (stderr, __VA_ARGS__);

typedef struct queue_node queue_node;
struct queue_node {
   queue_item_t item;
   queue_node *link;
};

struct queue {
   queue_node *front;
   queue_node *rear;
};

queue *new_queue (void) {
   queue *newqueue = malloc (sizeof (struct queue));
   assert(newqueue != NULL);
   newqueue->front = NULL;
   newqueue->rear = NULL;
   return newqueue;
}

void free_queue (queue *this) {
   assert (isempty_queue (this));
   free (this);
}

void insert_queue (queue *this, queue_item_t item) {
   queue_node *newnode = malloc(sizeof (struct queue_node));
   assert (newnode != NULL);
   newnode->item = item;
   if(this->rear == NULL){
      this->front = newnode;
   }
   else {
      this->rear->link = newnode;
   }
   this->rear = newnode;
}

queue_item_t remove_queue (queue *this) {
   assert (! isempty_queue (this));
   queue_node *newfront = this->front->link;
   queue_item_t result = this->front->item;
   free (this->front->item);
   free (this->front);
   this->front = newfront;
   return result;
}

bool isempty_queue (queue *this) {
   return this->front == NULL;
}

