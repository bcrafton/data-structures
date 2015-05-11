#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.h"
#include <assert.h>

// can test this doing a preorder print 

void cstring_print(void *s){
	printf("%s", (char*)s);
}
int cstring_compare(void *o1, void *o2){
	return strcmp((char*)o1, (char*)o2);
}
int main(){
	RBTree *tree = rbtree_constructor_print(&cstring_print, &cstring_compare);
	rbtree_add("Alex", "Alex", tree);
	rbtree_add("Brian", "Brian", tree);
	rbtree_add("Chris", "Chris", tree);
	rbtree_add("David", "David", tree);
	rbtree_add("Ethan", "Ethan", tree);
	rbtree_add("Fag", "Fag", tree);
	rbtree_add("George", "George", tree);
	rbtree_add("Hannibal", "Hannibal", tree);

	printf("\n%s\n", (char*)rbtree_search("Alex", tree));
	printf("\n%d\n", rbtree_contains("Brian", tree));

	printf("\n%d\n", rbtree_contains("hello", tree));

	rbtree_stack_print(tree);

	rbtree_remove("Chris", tree);

	printf("test complete\n");
}