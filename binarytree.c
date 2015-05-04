#include "binarytree.h"

BinarytreeNode* binarytree_node_constructor(TREE_TYPE data){
	BinarytreeNode *node = malloc(sizeof(BinarytreeNode));
	node->right = NULL;
	node->left = NULL;
	node->data = data;
	return node;
}

Binarytree* binarytree_constructor_print( void (*tree_print_ptr)(void*), int (*tree_compare_ptr)(void*, void*) ){
	Binarytree *tree = malloc(sizeof(Binarytree));
	tree->root = NULL;
	tree->tree_print_ptr = tree_print_ptr;
	tree->tree_compare_ptr = tree_compare_ptr;
	return tree;
}

Binarytree* binarytree_constructor( int (*tree_compare_ptr)(void*, void*) ){
	Binarytree *tree = malloc(sizeof(Binarytree));
	tree->root = NULL;
	tree->tree_print_ptr = NULL;
	tree->tree_compare_ptr = tree_compare_ptr;
	return tree;
}

void binarytree_add(TREE_TYPE data, Binarytree* tree){
	BinarytreeNode* newNode = binarytree_node_constructor(data);
	tree->size++;
	
	if(tree->root == NULL){
		tree->root = newNode;
		return;
	}
	BinarytreeNode* itr = tree->root;
	while(itr != NULL){
		if( (*(tree->tree_compare_ptr))(data, itr->data) > 0){
			if(itr->right == NULL){
				itr->right = newNode;
				return;
			}
			itr = itr->right;
		}
		else{
			if(itr->left == NULL){
				itr->left = newNode;
				return;
			}
			itr = itr->left;
		}
	}
}

void binarytree_stack_print(Binarytree *tree){
	Stack *stack = stack_constructor();
	stack_push(tree->root, stack);
	while(stackIsEmpty(stack) == 0){
		BinarytreeNode* top = stack_pop(stack);
		if(top->left != NULL){
			stack_push(top->left, stack);
		}
		if(top->right != NULL){
			stack_push(top->right, stack);
		}
		(*(tree->tree_print_ptr))(top->data);
		printf("|");
	}
	printf("[%d]\n", tree->size);
}
