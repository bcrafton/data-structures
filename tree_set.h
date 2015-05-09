#ifndef TREESET_H_
#define TREESET_H_

#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

typedef struct TreeSet TreeSet;
typedef void* SET_TYPE;

struct TreeSet{
	Binarytree *tree;
};

void tree_set_add(SET_TYPE value, TreeSet* set);
int tree_set_contains(SET_TYPE value, TreeSet* set);
TreeSet* tree_set_constructor( int (*treeset_compare_function)(void*, void*) );


#endif