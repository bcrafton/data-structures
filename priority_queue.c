#include "priority_queue.h"

PriorityQueue* priorityqueue_constructor( int (*priority_queue_compare_function)(void*, void*) ){
	PriorityQueue *queue = malloc(sizeof(PriorityQueue));
	queue->heap = heap_constructor(priority_queue_compare_function);
	return queue;
}
void priorityqueue_push(PRIORITYQUEUE_TYPE value, PriorityQueue *queue){
	maxHeapInsert(value, queue->heap);
}
PRIORITYQUEUE_TYPE priorityqueue_pop(PriorityQueue *queue){
	return extractMaxHeapMaximum(queue->heap);
}
PRIORITYQUEUE_TYPE priorityqueue_front(PriorityQueue *queue){
	return getMaxHeapMaximum(queue->heap);
}
int priorityqueueIsEmpty(PriorityQueue *queue){
	return queue->heap->size == 0;
}