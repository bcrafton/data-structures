#include "heap.h"

static int NULL_INDEX = -1; 
static int compare(HEAP_TYPE v1, HEAP_TYPE v2, Heap *heap);

Heap* heap_constructor_print( void (*heap_print_function)(void*), int (*heap_compare_function)(void*, void*) ){
	Heap* heap = malloc(sizeof(Heap));
	heap->vector = vector_constructor_print(heap_print_function);
	heap->size = 0;
	heap->heap_compare_function = heap_compare_function;
	return heap;
}

Heap* heap_constructor( int (*heap_compare_function)(void*, void*) ){
	Heap* heap = malloc(sizeof(Heap));
	heap->vector = vector_constructor();
	heap->size = 0;
	heap->heap_compare_function = heap_compare_function;
	return heap;
}

int heap_parent(int current_index){
	return current_index/2;
}
int heap_right(int current_index){
	return 2*(current_index+1);
}
int heap_left(int current_index){
	return 2*current_index+1;
}
HEAP_TYPE heap_get(int current_index, Heap* heap){
	return vector_get(current_index, heap->vector);
}

void heap_maxHeapify(int current_index, Heap* heap){
	int left_child_index;
	int right_child_index;
	int largest_index = NULL_INDEX;
	Vector *vector = heap->vector;
	int heapSize = heap->size;

	while(largest_index != current_index){
		left_child_index = heap_left(current_index);
		right_child_index = heap_right(current_index);

		HEAP_TYPE current = vector_get(current_index, vector);
		HEAP_TYPE left_child = vector_get(left_child_index, vector);
		HEAP_TYPE right_child = vector_get(right_child_index, vector);

		if(left_child_index <= heapSize-1 && compare(left_child, current, heap) > 0 ) {
			largest_index = left_child_index;
		} else {
			largest_index = current_index;
		}

		HEAP_TYPE largest = vector_get(largest_index, vector);

		if(right_child_index <= heapSize-1 && compare(right_child, largest, heap) > 0 ) {
			largest_index = right_child_index;
		}

		if(largest_index != current_index) {
			vector_swap(current_index, largest_index, vector);
			current_index = largest_index;
			largest_index = NULL_INDEX;
		}
	}
}

void heap_add(HEAP_TYPE value, Heap *heap){
	vector_add(value, heap->vector);
	heap->size++;
}

void heap_buildMaxHeap(Heap* heap){
	int index_counter;
	for(index_counter = (heap->size)/2-1; index_counter >= 0; index_counter--)
	{
		heap_maxHeapify(index_counter, heap);
	}
}

void heap_print(Heap *heap){
	vector_print(heap->vector);
}

void heap_sort(Heap *heap){
	heap_buildMaxHeap(heap);

	int counter;
	int heapSize = heap->size;

	for(counter = heapSize - 1; counter >= 1; counter--){
		vector_swap(0, counter, heap->vector);
		heap->size--;
		heap_maxHeapify(0, heap);
	}
	heap->size = heapSize;
}

static int compare(HEAP_TYPE v1, HEAP_TYPE v2, Heap *heap){
	return (*(heap->heap_compare_function))(v1, v2);
}