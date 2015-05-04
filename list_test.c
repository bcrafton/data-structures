#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include <assert.h>

void cstring_print(void *s){
	printf("%s", (char*)s);
}

int main(){
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

	printf("test complete\n");
}