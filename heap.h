#ifndef HEAP_H_
#define HEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

struct Heap{
	Vector *vector;
	int size;
	int (*heap_compare_function)(void*, void*);
};

typedef struct Heap Heap;
typedef void* HEAP_TYPE;

Heap* heap_constructor_print( void (*heap_print_function)(void*), int (*heap_compare_function)(void*, void*) );
Heap* heap_constructor( int (*heap_compare_function)(void*, void*) );
int heap_parent(int current_index);
int heap_right(int current_index);
int heap_left(int current_index);
HEAP_TYPE heap_get(int current_index, Heap* heap);
void heap_maxHeapify(int current_index, Heap* heap);
void heap_buildMaxHeap(Heap* heap);
void heap_add(HEAP_TYPE value, Heap *heap);
void heap_print(Heap *heap);
void heap_sort(Heap *heap);

#endif