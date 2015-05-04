#include "hashtable.h"

static int hash(KEY_TYPE key, Hashtable* table);
static int compare(VALUE_TYPE v1, VALUE_TYPE v2, Hashtable *table);

Hashtable* hashtable_constructor(int size, int (*table_hash_ptr)(void*), int (*table_compare_ptr)(void*, void*)){
	Hashtable *table = malloc(sizeof(Hashtable));
	table->size = size;
	table->vector = vector_constructor_size(size);
	table->table_hash_ptr = table_hash_ptr;
	table->table_compare_ptr = table_compare_ptr;
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
	return (*(table->table_hash_ptr))(key);
}

static int compare(VALUE_TYPE v1, VALUE_TYPE v2, Hashtable *table){
	return (*(table->table_compare_ptr))(v1, v2);
}
