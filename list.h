#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef void* LIST_TYPE;
typedef struct Linkedlist Linkedlist;
typedef struct Node Node;

struct Node {
	LIST_TYPE data;
	Node* next;
	Node* prev;
};

struct Linkedlist{
	int size;
	Node* head;
	Node* tail;
	void (*list_print_function)(void*);
};

Node* node_constructor(LIST_TYPE data);
Linkedlist* linkedlist_constructor();
Linkedlist* linkedlist_constructor_print( void (*list_print_function)(void*) );
void linkedlist_append(LIST_TYPE data, Linkedlist* list);
void linkedlist_print(Linkedlist *list);
void linkedlist_insert(int index, LIST_TYPE data, Linkedlist *list);
void linkedlist_prepend(LIST_TYPE data, Linkedlist* list);
void linkedlist_remove(int index, Linkedlist *list);
LIST_TYPE linkedlist_get(int index, Linkedlist *list);

#endif