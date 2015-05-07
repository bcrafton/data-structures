#ifndef SET_H_
#define SET_H_

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

typedef struct Set Set;
typedef void* SET_TYPE;

struct Set{
	Vector *vector;
	int capacity;
	int (*set_hash_function)(void*);
};

void set_add(SET_TYPE value, Set* set);
int set_contains(SET_TYPE value, Set* set);
Set* set_constructor(int capacity, int (*set_hash_function)(void*) );


#endif