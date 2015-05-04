#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct BinarytreeNode BinarytreeNode;
typedef struct Binarytree Binarytree;
typedef void* TREE_TYPE;

struct BinarytreeNode {
	TREE_TYPE data;
	BinarytreeNode* left;
	BinarytreeNode* right;
};

struct Binarytree{
	int size;
	BinarytreeNode* root;
	void (*tree_print_ptr)(void*);
	int (*tree_compare_ptr)(void*, void*);
};

BinarytreeNode* binarytree_node_constructor(TREE_TYPE data);
Binarytree* binarytree_constructor( int (*tree_compare_ptr)(void*, void*) );
Binarytree* binarytree_constructor_print( void (*tree_print_ptr)(void*), int (*tree_compare_ptr)(void*, void*) );
void binarytree_add(TREE_TYPE data, Binarytree* tree);
void binarytree_stack_print(Binarytree *tree);

#endif