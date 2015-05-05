#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef void* PRIORITYQUEUE_TYPE;
typedef struct PriorityQueue PriorityQueue;

struct PriorityQueue{
	Heap *heap;
};

PriorityQueue* priorityqueue_constructor( int (*priority_queue_compare_function)(void*, void*) );
void priorityqueue_push(PRIORITYQUEUE_TYPE value, PriorityQueue *queue);
PRIORITYQUEUE_TYPE priorityqueue_pop(PriorityQueue *queue);
PRIORITYQUEUE_TYPE priorityqueue_front(PriorityQueue *queue);
int priorityqueueIsEmpty(PriorityQueue *queue);

#endif
