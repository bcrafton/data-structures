#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

int int_hash(void *v){
	return *((int*)v);
}

int* get_int_ptr(int value){
	int* temp = malloc(sizeof(int));
	*temp = value;
	return temp;
}

int main(){
	int a = 10;
	int b = 11;
	int c = 12;

	Set *set = set_constructor(100, &int_hash);
	set_add(get_int_ptr(10), set);
	set_add(get_int_ptr(1), set);
	set_add(get_int_ptr(12), set);

	printf("%d\n", set_contains(get_int_ptr(10), set));
	printf("%d\n", set_contains(get_int_ptr(1), set));
	printf("%d\n", set_contains(get_int_ptr(2), set));
	printf("%d\n", set_contains(get_int_ptr(4), set));

}