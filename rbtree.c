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
static void removeFromParent(RBTreeNode* node);
static RBTreeNode* predecessor(RBTreeNode* node);
static void adjustAfterRemoval(RBTreeNode* n, RBTree *tree);

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
	tree->size = 0;
	tree->root = NULL;
	tree->tree_print_function = tree_print_function;
	tree->tree_compare_function = tree_compare_function;
	return tree;
}

RBTree* rbtree_constructor( int (*tree_compare_function)(void*, void*) ){
	RBTree *tree = malloc(sizeof(RBTree));
	tree->size = 0;
	tree->root = NULL;
	tree->tree_print_function = NULL;
	tree->tree_compare_function = tree_compare_function;
	return tree;
}

void rbtree_add(KEY_TYPE key, VALUE_TYPE value, RBTree* tree){
	tree->size++;
	
	if(tree->root == NULL){
		RBTreeNode* newNode = rbtree_node_constructor(key, value, NULL);
		newNode->red = 0; // this needs to be black or else it tries to get sibling of root which is NULL.
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

void rbtree_put(KEY_TYPE key, VALUE_TYPE value, RBTree* tree){
	tree->size++;
	
	if(tree->root == NULL){
		RBTreeNode* newNode = rbtree_node_constructor(key, value, NULL);
		newNode->red = 0; // this needs to be black or else it tries to get sibling of root which is NULL.
		tree->root = newNode;
		return;
	}
	RBTreeNode* itr = tree->root;
	while(itr != NULL){
		if( compare(key, itr->key, tree) == 0){
			itr->value = value;
			return;
		}
		else if( compare(key, itr->key, tree) > 0){
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

void rbtree_remove(KEY_TYPE key, RBTree* tree) {
    RBTreeNode* node = rbtree_search(key, tree);
    if (node == NULL) {
        // No such object, do nothing.
        return;
    } else if (leftOf(node) != NULL && rightOf(node) != NULL) {
        // Node has two children, Copy predecessor data in.
        RBTreeNode* pred = predecessor(node);
        //pred->parent->right == pred->left;
        node->key = pred->key;
        node->value = pred->value;
        //node.setData(predecessor.getData());
        //node = (Node) predecessor;
        node = pred;
    }
    // At this point node has zero or one child ...
    // this is because we node now equals pred and pred does not have a right child.
    RBTreeNode* pullUp = leftOf(node) == NULL ? rightOf(node) : leftOf(node);
    if (pullUp != NULL) {
        // Splice out node, and adjust if pullUp is a double black.
        if (node == tree->root) {
        	tree->root = pullUp;
        } else if (leftOf(parentOf(node)) == node) {
            node->parent->left = pullUp;
            pullUp->parent = node->parent;
        } else {
            node->parent->right = pullUp;
            pullUp->parent = node->parent;
        }
        if (isBlack(node)) {
            adjustAfterRemoval(pullUp, tree);
        }
    } else if (node == tree->root) {
        // Nothing to pull up when deleting a root means we emptied the tree
        tree->root = NULL;
    } else {
        // The node being deleted acts as a double black sentinel
        if (isBlack(node)) {
            adjustAfterRemoval(node, tree);
        }
        //node.removeFromParent();
        removeFromParent(node);
    }
}

static void adjustAfterRemoval(RBTreeNode* n, RBTree *tree) {
    while (n != tree->root && isBlack(n)) {
        if (n == leftOf(parentOf(n))) {
            // Pulled up node is a left child
            RBTreeNode* sibling = rightOf(parentOf(n));
            if (isRed(sibling)) {
                setColor(sibling, 0);
                setColor(parentOf(n), 1);
                rotateLeft(parentOf(n), tree);
                sibling = rightOf(parentOf(n));
            }
            if (isBlack(leftOf(sibling)) && isBlack(rightOf(sibling))) {
                setColor(sibling, 1);
                n = parentOf(n);
            } else {
                if (isBlack(rightOf(sibling))) {
                    setColor(leftOf(sibling), 0);
                    setColor(sibling, 1);
                    rotateRight(sibling, tree);
                    sibling = rightOf(parentOf(n));
                }
                setColor(sibling, isRed(parentOf(n)));
                setColor(parentOf(n), 0);
                setColor(rightOf(sibling), 0);
                rotateLeft(parentOf(n), tree);
                n = tree->root;
            }
        } else {
            // pulled up node is a right child
            RBTreeNode* sibling = leftOf(parentOf(n));
            if (isRed(sibling)) {
                setColor(sibling, 0);
                setColor(parentOf(n), 1);
                rotateRight(parentOf(n), tree);
                sibling = leftOf(parentOf(n));
            }
            if (isBlack(leftOf(sibling)) && isBlack(rightOf(sibling))) {
                setColor(sibling, 1);
                n = parentOf(n);
            } else {
                if (isBlack(leftOf(sibling))) {
                    setColor(rightOf(sibling), 0);
                    setColor(sibling, 1);
                    rotateLeft(sibling, tree);
                    sibling = leftOf(parentOf(n));
                }
                setColor(sibling, isRed(parentOf(n)));
                setColor(parentOf(n), 0);
                setColor(leftOf(sibling), 0);
                rotateRight(parentOf(n), tree);
                n = tree->root;
            }
        }
    }
    setColor(n, 0);
}

/*
public void removeFromParent() {
    if (parent != NULL) {
        if (parent.left == this) {
            parent.left = NULL;
        } else if (parent.right == this) {
            parent.right = NULL;
        }
        this.parent = NULL;
    }
}
*/
static void removeFromParent(RBTreeNode* node){
	RBTreeNode* parent = parentOf(node);
	if(parent == NULL){return;}
	if(leftOf(parent) == node){
		parent->left = NULL;
	}
	else if(rightOf(parent) == node){
		parent->right = NULL;
	}
	node->parent = NULL;
}


/*
protected void rotateLeft(BinaryTreeNode<E> n) {
    if (n.getRight() == NULL) {
        return;
    }
    BinaryTreeNode<E> oldRight = n.getRight();
    n.setRight(oldRight.getLeft());
    if (n.getParent() == NULL) {
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
    if (n.getLeft() == NULL) {
        return;
    }
    BinaryTreeNode<E> oldLeft = n.getLeft();
    n.setLeft(oldLeft.getRight());
    if (n.getParent() == NULL) {
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
/*
protected BinaryTreeNode<E> predecessor(BinaryTreeNode<E> node) {
    BinaryTreeNode<E> n = node.getLeft();
    if (n != NULL) {
        while (n.getRight() != NULL) {
            n = n.getRight();
        }
    }
    return n;
}
*/

// for remove, if it has no left node ... then predecessor is the parent and can just connect right and parent.
static RBTreeNode* predecessor(RBTreeNode* node){
	RBTreeNode* n = leftOf(node);
	if(n != NULL){
		while(rightOf(n) != NULL){
			n = rightOf(n);
		}
	}
	return n;
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