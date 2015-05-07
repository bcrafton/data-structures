#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

typedef struct Hashtable Hashtable;
typedef void* VALUE_TYPE;
typedef void* KEY_TYPE;

struct Hashtable{
	Vector *vector;
	int capacity;
	int (*table_hash_function)(void*);
};

void table_add(KEY_TYPE key, VALUE_TYPE value, Hashtable* table);
int table_contains(KEY_TYPE key, Hashtable* table);
VALUE_TYPE table_get(KEY_TYPE key, Hashtable* table);
Hashtable* hashtable_constructor(int capacity, int (*table_hash_function)(void*) );
int table_size(Hashtable* table);
#endif