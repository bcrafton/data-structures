#include "hashtable.h"

static int hash(KEY_TYPE key, Hashtable* table);
static int compare(VALUE_TYPE v1, VALUE_TYPE v2, Hashtable *table);

Hashtable* hashtable_constructor(int size, int (*table_hash_function)(void*), int (*table_compare_function)(void*, void*)){
	Hashtable *table = malloc(sizeof(Hashtable));
	table->size = size;
	table->vector = vector_constructor_size(size);
	table->table_hash_function = table_hash_function;
	table->table_compare_function = table_compare_function;
	return table;
}

void table_add(KEY_TYPE key, VALUE_TYPE value, Hashtable* table){
	int index = hash(key, table) % table->size;
	vector_set(index, value, table->vector);
}

int table_contains(KEY_TYPE key, VALUE_TYPE value, Hashtable* table){
	int index = hash(key, table) % table->size;
	return(compare(value, vector_get(index, table->vector), table) == 0);
}

static int hash(KEY_TYPE key, Hashtable* table){
	return (*(table->table_hash_function))(key);
}

static int compare(VALUE_TYPE v1, VALUE_TYPE v2, Hashtable *table){
	return (*(table->table_compare_function))(v1, v2);
}
