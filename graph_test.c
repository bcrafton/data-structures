#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include <assert.h>

void int_print(void *s){
	printf("%d", *((int*)s));
}
void cstring_print(void *s){
	printf("%s", (char*)s);
}
int int_compare(void *o1, void *o2){
	return *((int*)o1) - *((int*)o2);
}
int cstring_compare(void *o1, void *o2){
	return strcmp((char*)o1, (char*)o2);
}
int* get_int_ptr(int value){
	int* temp = malloc(sizeof(int));
	*temp = value;
	return temp;
}

int main(){


	char* a1 = "Brian";
	char* b1 = "Julia";
	char* c1 = "Rex";

	Graph* graph = graph_constructor();

	Vertex* v1 = add_vertex(a1, graph);
	Vertex* v2 = add_vertex(b1, graph);
	Vertex* v3 = add_vertex(c1, graph);

	Edge* e1 = add_edge(v1, v2, 1, graph);
	Edge* e2 = add_edge(v2, v3, 1, graph);
	Edge* e3 = add_edge(v3, v1, 1, graph);

	print_graph(graph);
}
