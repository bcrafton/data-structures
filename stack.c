#include "stack.h"

Stack* stack_constructor(){
	Stack *stack = malloc(sizeof(Stack));
	stack->list = linkedlist_constructor();
	return stack;
}

void stack_push(STACK_TYPE data, Stack *stack){
	linkedlist_prepend(data, stack->list);
}
STACK_TYPE stack_pop(Stack *stack){
	STACK_TYPE top = linkedlist_get(0, stack->list);
	linkedlist_remove(0, stack->list);
	return top;
}
STACK_TYPE stack_top(Stack *stack){
	return linkedlist_get(0, stack->list);
}
int stackIsEmpty(Stack *stack){
	return stack->list->size == 0;
}