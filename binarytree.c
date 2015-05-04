#include "binarytree.h"

static int compare(TREE_TYPE v1, TREE_TYPE v2, Binarytree *tree);
static int print(TREE_TYPE v, Binarytree *tree);

BinarytreeNode* binarytree_node_constructor(TREE_TYPE value){
	BinarytreeNode *node = malloc(sizeof(BinarytreeNode));
	node->right = NULL;
	node->left = NULL;
	node->value = value;
	return node;
}

Binarytree* binarytree_constructor_print( void (*tree_print_function)(void*), int (*tree_compare_function)(void*, void*) ){
	Binarytree *tree = malloc(sizeof(Binarytree));
	tree->root = NULL;
	tree->tree_print_function = tree_print_function;
	tree->tree_compare_function = tree_compare_function;
	return tree;
}

Binarytree* binarytree_constructor( int (*tree_compare_function)(void*, void*) ){
	Binarytree *tree = malloc(sizeof(Binarytree));
	tree->root = NULL;
	tree->tree_print_function = NULL;
	tree->tree_compare_function = tree_compare_function;
	return tree;
}

void binarytree_add(TREE_TYPE value, Binarytree* tree){
	BinarytreeNode* newNode = binarytree_node_constructor(value);
	tree->size++;
	
	if(tree->root == NULL){
		tree->root = newNode;
		return;
	}
	BinarytreeNode* itr = tree->root;
	while(itr != NULL){
		if( compare(value, itr->value, tree) > 0){
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
		print(top->value, tree);
		printf("|");
	}
	printf("[%d]\n", tree->size);
}

static int compare(TREE_TYPE v1, TREE_TYPE v2, Binarytree *tree){
	return (*(tree->tree_compare_function))(v1, v2);
}

static int print(TREE_TYPE v, Binarytree *tree){
	(*(tree->tree_print_function))(v);
}