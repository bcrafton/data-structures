#include "hash_set.h"

static int hash(SET_TYPE value, HashSet* set);

HashSet* hash_set_constructor(int capacity, int (*hashset_hash_function)(void*) ){
	HashSet *set = malloc(sizeof(HashSet));
	set->capacity = capacity;
	set->vector = vector_constructor_capacity(capacity);
	set->hashset_hash_function = hashset_hash_function;
	return set;
}

void hash_set_add(SET_TYPE value, HashSet* set){
	int index = hash(value, set) % set->capacity;
	vector_set(index, value, set->vector);
}

int hash_set_contains(SET_TYPE value, HashSet* set){
	int index = hash(value, set) % set->capacity;
	return vector_get(index, set->vector) != NULL;
}

static int hash(SET_TYPE value, HashSet* set){
	return (*(set->hashset_hash_function))(value);
}
