#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

void int_print(void *s){
	printf("%d", *((int*)s));
}
void cstring_print(void *s){
	printf("%s", (char*)s);
}
int int_compare(void *o1, void *o2){
	if(o1 == NULL && o2 == NULL){
		return 0;
	}
	if(o1 == NULL){
		return -1;
	}
	if(o2 == NULL){
		return 1;
	}
	return *((int*)o1) - *((int*)o2);
}
int cstring_compare(void *o1, void *o2){
	if(o1 == NULL && o2 == NULL){
		return 0;
	}
	if(o1 == NULL){
		return -1;
	}
	if(o2 == NULL){
		return 1;
	}
	return strcmp((char*)o1, (char*)o2);
}
int int_hash(void *v){
	return *((int*)v);
}
int cstring_hash(void *v){
	int hash = 0;
	int indexCounter;
	char* s = (char*)v;

	for(indexCounter = 0; indexCounter < strlen(s) || indexCounter < 4; indexCounter++){
		if(indexCounter != 0){
			hash = hash << 8;
		}
		hash = hash | s[indexCounter];
	}
	return hash;
}

int main(){
	int a = 10;
	int b = 11;
	int c = 12;

	char* a1 = "Brian";
	char* b1 = "Julia";
	char* c1 = "Rex";

	Hashtable *table = hashtable_constructor(26, &int_hash, &int_compare);
	table_add(&a, &a, table);
	printf("%d\n", table_contains(&a, &a, table));
	printf("%d\n", table_contains(&b, &b, table));

	Hashtable *stable = hashtable_constructor(26, &cstring_hash, &cstring_compare);
	table_add(a1, a1, stable);
	printf("%d\n", table_contains(a1, a1, stable));
	printf("%d\n", table_contains(b1, b1, stable));
}