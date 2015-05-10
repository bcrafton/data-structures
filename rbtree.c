#include "rbtree.h"

static int compare(KEY_TYPE v1, KEY_TYPE v2, RBTree *tree);
static int print(VALUE_TYPE v, RBTree *tree);
static void adjustAfterInsertion(RBTreeNode* n, RBTree* tree);
static int isRed(RBTreeNode* node);
static int isBlack(RBTreeNode* node);
static void setColor(RBTreeNode* node, int red);
static RBTreeNode* parentOf(RBTreeNode* node);
static RBTreeNode* grandparentOf(RBTreeNode* node);
static RBTreeNode* siblingOf(RBTreeNode* node);
static RBTreeNode* leftOf(RBTreeNode* node);
static RBTreeNode* rightOf(RBTreeNode* node);
static void rotateLeft(RBTreeNode* n, RBTree* tree);
static void rotateRight(RBTreeNode* n, RBTree* tree);

static int node_compare(void *o1, void *o2){
	if(o1 == NULL && o2 == NULL){return 0;}
	if(o1 == NULL){return 1;}
	if(o2 == NULL){return -1;}
	if(o1 == o2){return 0;}
	if(o1 > o2){return 1;}
	else{return -1;}
}

RBTreeNode* rbtree_node_constructor(KEY_TYPE key, VALUE_TYPE value, RBTreeNode* parent) {
	RBTreeNode *node = malloc(sizeof(RBTreeNode));
	node->right = NULL;
	node->left = NULL;
	node->parent = parent;
	node->red = 1;
	node->value = value;
	node->key = key;
	return node;
}

RBTree* rbtree_constructor_print( void (*tree_print_function)(void*), int (*tree_compare_function)(void*, void*) ){
	RBTree *tree = malloc(sizeof(RBTree));
	tree->root = NULL;
	tree->tree_print_function = tree_print_function;
	tree->tree_compare_function = tree_compare_function;
	return tree;
}

RBTree* rbtree_constructor( int (*tree_compare_function)(void*, void*) ){
	RBTree *tree = malloc(sizeof(RBTree));
	tree->root = NULL;
	tree->tree_print_function = NULL;
	tree->tree_compare_function = tree_compare_function;
	return tree;
}

void rbtree_add(KEY_TYPE key, VALUE_TYPE value, RBTree* tree){
	tree->size++;
	
	if(tree->root == NULL){
		RBTreeNode* newNode = rbtree_node_constructor(key, value, NULL);
		newNode->red = 0; // this needs to be black or else it tries to get sibling of root which is null.
		tree->root = newNode;
		return;
	}
	RBTreeNode* itr = tree->root;
	while(itr != NULL){
		if( compare(key, itr->key, tree) > 0){
			if(itr->right == NULL){
				RBTreeNode* newNode = rbtree_node_constructor(key, value, itr);
				itr->right = newNode;
				adjustAfterInsertion(newNode, tree);
				return;
			}
			itr = rightOf(itr);
		}
		else{
			if(itr->left == NULL){
				RBTreeNode* newNode = rbtree_node_constructor(key, value, itr);
				itr->left = newNode;
				adjustAfterInsertion(newNode, tree);
				return;
			}
			itr = leftOf(itr);
		}
	}
}

VALUE_TYPE rbtree_search(KEY_TYPE key, RBTree* tree){
	RBTreeNode* itr = tree->root;
	while(itr != NULL){
		if( compare(key, itr->key, tree) == 0 ){
			return itr->value;
		}
		else if( compare(key, itr->key, tree) > 0 ){
			itr = itr->right;
		}
		else{
			itr = itr->left;
		}
	}
	return NULL;
}

void rbtree_stack_inorder_print(RBTree *tree){
	Stack *stack = stack_constructor();
	TreeSet* visited = tree_set_constructor(&node_compare);
	stack_push(tree->root, stack);
	tree_set_add(tree->root, visited);

	while(stackIsEmpty(stack) == 0){
		RBTreeNode* top = stack_top(stack);
		if(top->left != NULL && tree_set_contains(top->left, visited) == 0){
			stack_push(top->left, stack);
			tree_set_add(top->left, visited);
			continue;
		}

		print(top->key, tree);
		if(top->parent != NULL){
			printf(" parent: ");
			print(top->parent->key, tree);
		}
		if(top->right != NULL){
			printf(" right: ");
			print(top->right->key, tree);
		}
		if(top->left != NULL){
			printf(" left: ");
			print(top->left->key, tree);
		}
		printf("\n");

		stack_pop(stack);

		if(top->right != NULL && tree_set_contains(top->right, visited) == 0){
			stack_push(top->right, stack);
			tree_set_add(top->right, visited);
			continue;
		}
		
	}
	printf("[%d]\n", tree->size);
}

void rbtree_stack_print(RBTree *tree){
	Stack *stack = stack_constructor();
	stack_push(tree->root, stack);
	while(stackIsEmpty(stack) == 0){
		RBTreeNode* top = stack_pop(stack);
		if(top->right != NULL){
			stack_push(top->right, stack);
		}
		if(top->left != NULL){
			stack_push(top->left, stack);
		}
		print(top->value, tree);
		printf("|");
	}
	printf("[%d]\n", tree->size);
}

int rbtree_contains(KEY_TYPE key, RBTree* tree){
	return rbtree_search(key, tree) != NULL;
}

static void adjustAfterInsertion(RBTreeNode* n, RBTree* tree) {
	// Step 1: color the node red
    setColor(n, 1);

    // Step 2: Correct double red problems, if they exist
    if (n != NULL && n != tree->root && isRed(parentOf(n))) {

        // Step 2a (simplest): Recolor, and move up to see if more work
        // needed
        if (isRed(siblingOf(parentOf(n)))) {
            setColor(parentOf(n), 0);
            setColor(siblingOf(parentOf(n)), 0);
            setColor(grandparentOf(n), 1);
            adjustAfterInsertion(grandparentOf(n), tree);
        }
		
        // Step 2b: Restructure for a parent who is the left child of the
        // grandparent. This will require a single right rotation if n is
        // also
        // a left child, or a left-right rotation otherwise.
        else if (parentOf(n) == leftOf(grandparentOf(n))) {
            if (n == rightOf(parentOf(n))) {
                rotateLeft(n = parentOf(n), tree);
            }
            setColor(parentOf(n), 0);
            setColor(grandparentOf(n), 1);
            rotateRight(grandparentOf(n), tree);
        }

        // Step 2c: Restructure for a parent who is the right child of the
        // grandparent. This will require a single left rotation if n is
        // also
        // a right child, or a right-left rotation otherwise.
        else if (parentOf(n) == rightOf(grandparentOf(n))) {
            if (n == leftOf(parentOf(n))) {
                rotateRight(n = parentOf(n), tree);
            }
            setColor(parentOf(n), 0);
            setColor(grandparentOf(n), 1);
            rotateLeft(grandparentOf(n), tree);
        }
    }
    // Step 3: Color the root black
    setColor(tree->root, 0);
}


/*
protected void rotateLeft(BinaryTreeNode<E> n) {
    if (n.getRight() == null) {
        return;
    }
    BinaryTreeNode<E> oldRight = n.getRight();
    n.setRight(oldRight.getLeft());
    if (n.getParent() == null) {
        root = oldRight;
    } else if (n.getParent().getLeft() == n) {
        n.getParent().setLeft(oldRight);
    } else {
        n.getParent().setRight(oldRight);
    }
    oldRight.setLeft(n);
}
*/
static void rotateLeft(RBTreeNode* n, RBTree* tree){
	RBTreeNode* oldRight = rightOf(n);
	n->right = leftOf(oldRight);
	if(n == tree->root){
		tree->root = oldRight;
	}
	else if(leftOf(parentOf(n)) == n){
		n->parent->left = oldRight;
	}
	else{
		n->parent->right = oldRight;
	}
	oldRight->left = n;
	oldRight->parent = n->parent;
	n->parent = oldRight;
}
/*
protected void rotateRight(BinaryTreeNode<E> n) {
    if (n.getLeft() == null) {
        return;
    }
    BinaryTreeNode<E> oldLeft = n.getLeft();
    n.setLeft(oldLeft.getRight());
    if (n.getParent() == null) {
        root = oldLeft;
    } else if (n.getParent().getLeft() == n) {
        n.getParent().setLeft(oldLeft);
    } else {
        n.getParent().setRight(oldLeft);
    }
    oldLeft.setRight(n);
}
*/
static void rotateRight(RBTreeNode* n, RBTree* tree){
	RBTreeNode* oldLeft = leftOf(n);
	n->left = rightOf(oldLeft);
	if(n == tree->root){
		tree->root = oldLeft;
	}
	else if(leftOf(parentOf(n)) == n){
		n->parent->left = oldLeft;
	}
	else{
		n->parent->right = oldLeft;
	}
	oldLeft->right = n;
	oldLeft->parent = n->parent;
	n->parent = oldLeft;
}

static int compare(KEY_TYPE v1, KEY_TYPE v2, RBTree *tree){
	return (*(tree->tree_compare_function))(v1, v2);
}

static int print(VALUE_TYPE v, RBTree *tree){
	(*(tree->tree_print_function))(v);
}

static int isRed(RBTreeNode* node){
	if(node == NULL){
		return 0;
	}
	return node->red == 1;
}
static int isBlack(RBTreeNode* node){
	if(node == NULL){
		return 1;
	}
	return node->red == 0;
}
static void setColor(RBTreeNode* node, int red){
	node->red = red;
}
static RBTreeNode* parentOf(RBTreeNode* node){
	return node->parent;
}
static RBTreeNode* grandparentOf(RBTreeNode* node){
	return parentOf(parentOf(node));
}
static RBTreeNode* siblingOf(RBTreeNode* node){
	RBTreeNode* parent = parentOf(node);
	if(node == leftOf(parent)){
		return rightOf(parent);
	}
	return leftOf(parent);

}
static RBTreeNode* leftOf(RBTreeNode* node){
	return node->left;
}
static RBTreeNode* rightOf(RBTreeNode* node){
	return node->right;
}