#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable.h"
#include <limits.h>

int* get_int_ptr(int value){
	int* temp = malloc(sizeof(int));
	*temp = value;
	return temp;
}
long long int* get_long_ptr(long long int value){
	long long int* temp = malloc(sizeof(long long int));
	*temp = value;
	return temp;
}
int int_hash(void *v){
	return *((int*)v);
}

long long int fib(long long int n, Hashtable *table){
	if(n == 0){
		return 0;
	}
	else if(n == 1){
		return 1;
	}
	else if(table_contains(&n, table)==1){
		return *((long long int *)table_get(&n, table));
	}
	else{
		long long int fib_val = fib(n-1, table)+fib(n-2, table);
		long long int *value = get_long_ptr(fib_val);
		table_add(&n, value, table);
		return fib_val;
	}
}

long long int shitinacci(long long int n){
	if(n == 0){
		return 0;
	}
	else if(n == 1){
		return 1;
	}
	else{
		return shitinacci(n-1)+shitinacci(n-2);
	}
}


int main(){
	long long int x = 9223372036854775807;
	printf("%lld\n", x);
	printf("%lld\n", LLONG_MAX);
	Hashtable *table = hashtable_constructor(1000, &int_hash);
	printf("%lld\n", fib(50, table));
	printf("%lld\n", shitinacci(50));	
}
