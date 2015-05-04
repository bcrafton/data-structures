#include "list.h"

Node* node_constructor(LIST_TYPE data){
	Node *node = malloc(sizeof(Node));
	node->next = NULL;
	node->prev = NULL;
	node->data = data;
}

Linkedlist* linkedlist_constructor_print( void (*list_print_function)(void*) ){
	Linkedlist *list = malloc(sizeof(Linkedlist));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->list_print_function = list_print_function;
	return list;
}

Linkedlist* linkedlist_constructor(){
	Linkedlist *list = malloc(sizeof(Linkedlist));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->list_print_function = NULL;
	return list;
}

void linkedlist_append(LIST_TYPE data, Linkedlist* list){
	Node* newNode = node_constructor(data);
	if(list->head == NULL && list->tail == NULL){
		list->head = newNode;
		list->tail = newNode;
	}
	else{
		list->tail->next = newNode;
		newNode->prev = list->tail;
		list->tail = newNode;
	}
	list->size++;
}

void linkedlist_prepend(LIST_TYPE data, Linkedlist* list){
	Node* newNode = node_constructor(data);
	if(list->head == NULL && list->tail == NULL){
		list->head = newNode;
		list->tail = newNode;
	}
	else{
		list->head->prev = newNode;
		newNode->next = list->head;
		list->head = newNode;
	}
	list->size++;
}

// code will break if only 1 element in the list
void linkedlist_insert(int index, LIST_TYPE data, Linkedlist *list){
	Node* newNode = node_constructor(data);
	if(list->head == NULL && list->tail == NULL){
		list->head = newNode;
		list->tail = newNode;
	}
	else if(index >= list->size){
		list->tail->next = newNode;
		newNode->prev = list->tail;
		list->tail = newNode;
	}
	else if(index <= 0){
		list->head->prev = newNode;
		newNode->next = list->head;
		list->head = newNode;
	}
	else{
		int counter = 0;
		Node* ptr;
		for(ptr = list->head; ptr != NULL; ptr = ptr->next){
			if(counter == index){
				Node* left = ptr->prev;
				Node* right = ptr;
				left->next = newNode;
				newNode->prev = left;
				right->prev = newNode;
				newNode->next = right;
				return;
			}
			counter++;
		}
	}
	list->size++;
}

void linkedlist_remove(int index, Linkedlist *list){
	if(list->head == NULL && list->tail == NULL){
		return;
	}
	else if(list->size == 1){
		list->head = NULL;
		list->tail = NULL;
	}
	else if(index >= list->size){
		list->tail = list->tail->prev;
		list->tail->next = NULL;
	}
	else if(index <= 0){
		list->head = list->head->next;
		list->head->prev = NULL;
	}
	else{
		int counter = 0;
		Node* ptr;
		for(ptr = list->head; ptr != NULL; ptr = ptr->next){
			if(counter == index){
				Node* left = ptr->prev;
				Node* right = ptr->next;
				left->next = right;
				right->prev = left;
			}
			counter++;
		}
	}
	list->size--;
}

LIST_TYPE linkedlist_get(int index, Linkedlist *list){
	int counter = 0;
	Node* ptr;
	for(ptr = list->head; ptr != NULL; ptr = ptr->next){
		if(counter == index){
			return ptr->data;
		}
		counter++;
	}
	return NULL;
}

void linkedlist_print(Linkedlist *list){
	Node *ptr;
	for(ptr = list->head; ptr != NULL; ptr = ptr->next){
		(*(list->list_print_function))(ptr->data);
		printf("|");
	}
	printf("[%d]\n", list->size);
}