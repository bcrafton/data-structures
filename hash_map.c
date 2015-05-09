#include "hash_map.h"

static int hash(KEY_TYPE key, HashMap* map);

HashMap* hash_map_constructor(int capacity, int (*hashmap_hash_function)(void*) ){
	HashMap *map = malloc(sizeof(HashMap));
	map->capacity = capacity;
	map->vector = vector_constructor_capacity(capacity);
	map->hashmap_hash_function = hashmap_hash_function;
	return map;
}

VALUE_TYPE hash_map_get(KEY_TYPE key, HashMap* map){
	int index = hash(key, map) % map->capacity;
	return vector_get(index, map->vector);
}

void hash_map_add(KEY_TYPE key, VALUE_TYPE value, HashMap* map){
	int index = hash(key, map) % map->capacity;
	vector_set(index, value, map->vector);
}

int hash_map_contains(KEY_TYPE key, HashMap* map){
	int index = hash(key, map) % map->capacity;
	return vector_get(index, map->vector) != NULL;
}

int hash_map_size(HashMap* map){
	int element_count = 0;
	int counter;
	for(counter = 0; counter < map->capacity; counter++){
		if(vector_get(counter, map->vector) != NULL){
			element_count++;
		}
	}
	return element_count;
}

static int hash(KEY_TYPE key, HashMap* map){
	return (*(map->hashmap_hash_function))(key);
}

