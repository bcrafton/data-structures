#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "vector.h"
#include "list.h"
#include "binarytree.h"
#include "stack.h"
#include "queue.h"
#include "heap.h"
#include "hashtable.h"

void int_print(void *s){
	printf("%d", *((int*)s));
}
void cstring_print(void *s){
	printf("%s", (char*)s);
}
int int_compare(void *o1, void *o2){
	if(o1 == NULL && o2 == NULL){
		return 0;
	}
	if(o1 == NULL){
		return -1;
	}
	if(o2 == NULL){
		return 1;
	}
	return *((int*)o1) - *((int*)o2);
}
int cstring_compare(void *o1, void *o2){
	if(o1 == NULL && o2 == NULL){
		return 0;
	}
	if(o1 == NULL){
		return -1;
	}
	if(o2 == NULL){
		return 1;
	}
	return strcmp((char*)o1, (char*)o2);
}
int int_hash(void *v){
	return *((int*)v);
}
int cstring_hash(void *v){
	int hash = 0;
	int indexCounter;
	char* s = (char*)v;

	for(indexCounter = 0; indexCounter < strlen(s) || indexCounter < 4; indexCounter++){
		if(indexCounter != 0){
			hash = hash << 8;
		}
		hash = hash | s[indexCounter];
	}
	return hash;
}

int main(){
	int a = 10;
	int b = 11;
	int c = 12;

	char* a1 = "Brian";
	char* b1 = "Julia";
	char* c1 = "Rex";

	List* list = list_constructor_print(&cstring_print);
	list_append(a1, list);
	list_append(b1, list);
	list_append(c1, list);
	
	assert(strcmp((char*)list_get(0, list), a1) == 0);
	assert(strcmp((char*)list_get(1, list), b1) == 0);
	assert(strcmp((char*)list_get(2, list), c1) == 0);

	list_print(list);

	Vector* vector = vector_constructor_print(&cstring_print);
	vector_add(a1, vector);
	vector_add(b1, vector);
	vector_add(c1, vector);
	
	assert(strcmp((char*)vector_get(0, vector), a1) == 0);
	assert(strcmp((char*)vector_get(1, vector), b1) == 0);
	assert(strcmp((char*)vector_get(2, vector), c1) == 0);

	vector_print(vector);

	Binarytree* tree = binarytree_constructor_print(&cstring_print, &cstring_compare);
	binarytree_add(a1, tree);
	binarytree_add(b1, tree);
	binarytree_add(c1, tree);

	binarytree_stack_print(tree);

	Hashtable *table = hashtable_constructor(26, &int_hash, &int_compare);
	table_add(&a, &a, table);
	printf("%d\n", table_contains(&a, &a, table));
	printf("%d\n", table_contains(&b, &b, table));

	Hashtable *stable = hashtable_constructor(26, &cstring_hash, &cstring_compare);
	table_add(a1, a1, stable);
	printf("%d\n", table_contains(a1, a1, stable));
	printf("%d\n", table_contains(b1, b1, stable));

	Heap* heap = heap_constructor_print(&int_print, &int_compare);
	heap_add(&a, heap);
	heap_add(&b, heap);
	heap_add(&c, heap);

	Heap* sheap = heap_constructor_print(&cstring_print, &cstring_compare);
	heap_add(a1, sheap);
	heap_add(b1, sheap);
	heap_add(c1, sheap);

	heap_buildMaxHeap(heap);
	heap_print(heap);
	heap_sort_inc(heap);
	heap_print(heap);

	heap_buildMinHeap(sheap);
	heap_print(sheap);
	heap_sort_dec(sheap);
	heap_print(sheap);

	Queue* queue = queue_constructor();
	queue_push(a1, queue);
	queue_push(b1, queue);
	queue_push(c1, queue);

	assert(strcmp((char*)queue_pop(queue), a1) == 0);
	assert(strcmp((char*)queue_pop(queue), b1) == 0);
	assert(strcmp((char*)queue_pop(queue), c1) == 0);

	Stack* stack = stack_constructor();
	stack_push(a1, stack);
	stack_push(b1, stack);
	stack_push(c1, stack);
	
	assert(strcmp((char*)stack_pop(stack), c1) == 0);
	assert(strcmp((char*)stack_pop(stack), b1) == 0);
	assert(strcmp((char*)stack_pop(stack), a1) == 0);

	printf("test complete\n");
}
