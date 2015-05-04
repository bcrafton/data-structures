#include "vector.h"

static int print(VECTOR_TYPE v, Vector *vector);

Vector* vector_constructor_print(void (*vector_print_function)(void*)){
	Vector *newVector = malloc(sizeof(Vector));
	newVector->size = 10;
	newVector->next = 0;
	newVector->array = malloc(newVector->size * sizeof(VECTOR_TYPE));
	newVector->vector_print_function = vector_print_function;
	return newVector;
}

Vector* vector_constructor(){
	Vector *newVector = malloc(sizeof(Vector));
	newVector->size = 10;
	newVector->next = 0;
	newVector->array = malloc(newVector->size * sizeof(VECTOR_TYPE));
	newVector->vector_print_function = NULL;
	return newVector;
}

Vector* vector_constructor_size(int size){
	Vector *newVector = malloc(sizeof(Vector));
	newVector->size = size;
	newVector->next = 0;
	newVector->array = malloc(newVector->size * sizeof(VECTOR_TYPE));
	newVector->vector_print_function = NULL;
	return newVector;
}

void vector_resize(Vector *vector){
	vector->size = vector->size * 2;
	VECTOR_TYPE *newArray = malloc(vector->size * sizeof(VECTOR_TYPE));

	int indexCounter;
	for(indexCounter = 0; indexCounter < vector->next; indexCounter++){
		newArray[indexCounter] = vector->array[indexCounter];
	}
	vector->array = newArray;
}

void vector_add(VECTOR_TYPE value, Vector *vector){
	if(vector->next >= vector->size){
		vector_resize(vector);
	}
	vector->array[vector->next] = value;
	vector->next++;
}

void vector_print(Vector *vector){
	int indexCounter;
	for(indexCounter = 0; indexCounter < vector->next; indexCounter++){
		print(vector->array[indexCounter], vector);
		printf("|");
	}
	printf("[%d]\n", vector->next);
}

VECTOR_TYPE vector_get(int index, Vector *vector){
	return vector->array[index];
}

void vector_removeIndex(int index, Vector *vector){
	vector->next--;

	int indexCounter;
	for(indexCounter = index; indexCounter < vector->next; indexCounter++){
		vector->array[indexCounter] = vector->array[indexCounter+1];
	}
	vector->array[vector->next] = 0;
}

void vector_insert(int index, VECTOR_TYPE value, Vector *vector){
	if(vector->next >= vector->size){vector_resize(vector);}
	int indexCounter;
	for(indexCounter = vector->next; indexCounter >= index; indexCounter--){
		vector->array[indexCounter] = vector->array[indexCounter-1];
	}
	vector->array[index] = value;
	vector->next++;
}

void vector_set(int index, VECTOR_TYPE value, Vector *vector){
	vector->array[index] = value;
}

void vector_swap(int index1, int index2, Vector *vector){
	VECTOR_TYPE temp = vector->array[index1];
	vector->array[index1] = vector->array[index2];
	vector->array[index2] = temp;
}

static int print(VECTOR_TYPE v, Vector *vector){
	(*(vector->vector_print_function))(v);
}