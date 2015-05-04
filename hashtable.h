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
	int size;
	int (*table_hash_ptr)(void*);
	int (*table_compare_ptr)(void*, void*);
};

void table_add(KEY_TYPE key, VALUE_TYPE value, Hashtable* table);
int table_contains(KEY_TYPE key, VALUE_TYPE value, Hashtable* table);
Hashtable* hashtable_constructor(int size, int (*table_hash_ptr)(void*), int (*table_compare_ptr)(void*, void*));

#endif