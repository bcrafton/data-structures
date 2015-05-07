#include "set.h"

static int hash(SET_TYPE value, Set* set);

Set* set_constructor(int capacity, int (*set_hash_function)(void*) ){
	Set *set = malloc(sizeof(Set));
	set->capacity = capacity;
	set->vector = vector_constructor_capacity(capacity);
	set->set_hash_function = set_hash_function;
	return set;
}

void set_add(SET_TYPE value, Set* set){
	int index = hash(value, set) % set->capacity;
	vector_set(index, value, set->vector);
}

int set_contains(SET_TYPE value, Set* set){
	int index = hash(value, set) % set->capacity;
	return vector_get(index, set->vector) != NULL;
}

static int hash(SET_TYPE value, Set* set){
	return (*(set->set_hash_function))(value);
}
