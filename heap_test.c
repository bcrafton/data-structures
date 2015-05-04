#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

void int_print(void *s){
	printf("%d", *((int*)s));
}
void cstring_print(void *s){
	printf("%s", (char*)s);
}
int int_compare(void *o1, void *o2){
	return *((int*)o1) - *((int*)o2);
}
int cstring_compare(void *o1, void *o2){
	return strcmp((char*)o1, (char*)o2);
}

int main(){
	int a = 10;
	int b = 11;
	int c = 12;

	char* a1 = "Brian";
	char* b1 = "Julia";
	char* c1 = "Rex";

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
	heap_sort(heap);
	heap_print(heap);

	heap_buildMaxHeap(sheap);
	heap_print(sheap);
	heap_sort(sheap);
	heap_print(sheap);
}