#include "tree_set.h"

void tree_set_add(SET_TYPE value, TreeSet* set){
	binarytree_add(value, value, set->tree);
}

int tree_set_contains(SET_TYPE value, TreeSet* set){
	return binarytree_contains(value, set->tree);
}

TreeSet* tree_set_constructor( int (*treeset_compare_function)(void*, void*) ){
	TreeSet *set = malloc(sizeof(TreeSet));
	set->tree = binarytree_constructor(treeset_compare_function);
	return set;
}