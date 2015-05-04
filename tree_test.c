#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"
#include <assert.h>

void cstring_print(void *s){
	printf("%s", (char*)s);
}
int cstring_compare(void *o1, void *o2){
	return strcmp((char*)o1, (char*)o2);
}
int main(){
	char* a1 = "Brian";
	char* b1 = "Julia";
	char* c1 = "Rex";

	Binarytree* tree = binarytree_constructor_print(&cstring_print, &cstring_compare);
	binarytree_add(a1, tree);
	binarytree_add(b1, tree);
	binarytree_add(c1, tree);

	binarytree_stack_print(tree);

	printf("test complete\n");
}