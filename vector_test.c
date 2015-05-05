#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include <assert.h>

void cstring_print(void *s){
	printf("%s", (char*)s);
}

int main(){
	char* a1 = "Brian";
	char* b1 = "Julia";
	char* c1 = "Rex";

	Vector* vector = vector_constructor_print(&cstring_print);
	vector_add(a1, vector);
	vector_add(b1, vector);
	vector_add(c1, vector);
	
	assert(strcmp((char*)vector_get(0, vector), a1) == 0);
	assert(strcmp((char*)vector_get(1, vector), b1) == 0);
	assert(strcmp((char*)vector_get(2, vector), c1) == 0);

	vector_print(vector);

	assert(vector->next == 3);
	assert(vector_size(vector) == 3);

	printf("test complete\n");
}