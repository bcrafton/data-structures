#include "hashtable.h"

static int hash(KEY_TYPE key, Hashtable* table);

Hashtable* hashtable_constructor(int capacity, int (*table_hash_function)(void*) ){
	Hashtable *table = malloc(sizeof(Hashtable));
	table->capacity = capacity;
	table->vector = vector_constructor_capacity(capacity);
	table->table_hash_function = table_hash_function;
	return table;
}

VALUE_TYPE table_get(KEY_TYPE key, Hashtable* table){
	int index = hash(key, table) % table->capacity;
	return vector_get(index, table->vector);
}

void table_add(KEY_TYPE key, VALUE_TYPE value, Hashtable* table){
	int index = hash(key, table) % table->capacity;
	vector_set(index, value, table->vector);
}

int table_contains(KEY_TYPE key, Hashtable* table){
	int index = hash(key, table) % table->capacity;
	return vector_get(index, table->vector) != NULL;
}

int table_size(Hashtable* table){
	int element_count = 0;
	int counter;
	for(counter = 0; counter < table->capacity; counter++){
		if(vector_get(counter, table->vector) != NULL){
			element_count++;
		}
	}
	return element_count;
}

static int hash(KEY_TYPE key, Hashtable* table){
	return (*(table->table_hash_function))(key);
}

