#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdio.h>
#include <stdlib.h>

typedef void* VECTOR_TYPE;
typedef struct Vector Vector;

struct Vector{
	int next;
	int size;
	VECTOR_TYPE *array;
	void (*vector_print_function)(void*);
};

Vector* vector_constructor_print( void (*vector_print_function)(void*) );;
Vector* vector_constructor();
Vector* vector_constructor_size(int size);
void  vector_resize(Vector *vector);
void vector_add(VECTOR_TYPE data, Vector *vector);
void vector_print(Vector *vector);
VECTOR_TYPE vector_get(int index, Vector *vector);
void vector_removeIndex(int index, Vector *vector);
void vector_insert(int index, VECTOR_TYPE data, Vector *vector);
void vector_swap(int index1, int index2, Vector *vector);

#endif
