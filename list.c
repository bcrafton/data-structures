#include "list.h"

static int print(LIST_TYPE v, List *list);

Node* node_constructor(LIST_TYPE value){
	Node *node = malloc(sizeof(Node));
	node->next = NULL;
	node->prev = NULL;
	node->value = value;
}

List* list_constructor_print( void (*list_print_function)(void*) ){
	List *list = malloc(sizeof(List));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->list_print_function = list_print_function;
	return list;
}

List* list_constructor(){
	List *list = malloc(sizeof(List));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->list_print_function = NULL;
	return list;
}

void list_append(LIST_TYPE value, List* list){
	Node* newNode = node_constructor(value);
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

void list_prepend(LIST_TYPE value, List* list){
	Node* newNode = node_constructor(value);
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
void list_insert(int index, LIST_TYPE value, List *list){
	Node* newNode = node_constructor(value);
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

void list_remove(int index, List *list){
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

LIST_TYPE list_get(int index, List *list){
	int counter = 0;
	Node* ptr;
	for(ptr = list->head; ptr != NULL; ptr = ptr->next){
		if(counter == index){
			return ptr->value;
		}
		counter++;
	}
	return NULL;
}

void list_print(List *list){
	Node *ptr;
	for(ptr = list->head; ptr != NULL; ptr = ptr->next){
		print(ptr->value, list);
		printf("|");
	}
	printf("[%d]\n", list->size);
}

static int print(LIST_TYPE v, List *list){
	(*(list->list_print_function))(v);
}