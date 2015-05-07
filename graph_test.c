#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "vector.h"
#include <assert.h>

void vertex_print_function(void *v){
	print_vertex((Vertex*)v);
}
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

	Vertex* v1 = add_vertex(0, a1, graph);
	Vertex* v2 = add_vertex(1, b1, graph);
	Vertex* v3 = add_vertex(2, c1, graph);

	Edge* e1 = add_edge(0, v1, v2, 1, graph);
	Edge* e2 = add_edge(1, v2, v3, 1, graph);
	Edge* e3 = add_edge(2, v3, v1, 1, graph);

	print_graph(graph);

	printf("\n\n\n");

	print_vertex(v2);
	Vector* vertices = adjacent_vertices(v2);
	printf("adjacents:\n");
	vertices->vector_print_function = &vertex_print_function;
	vector_print(vertices);

	printf("\n");
	BredthFirstTraversal(v1);
	printf("\n");
	DepthFirstTraversal(v1);
	printf("\n");
	Vertex* v = get_vertex(0, graph);
	printf("\n%d\n", v->key);
	v = get_vertex(1, graph);
	printf("\n%d\n", v->key);
	v = get_vertex(2, graph);
	printf("\n%d\n", v->key);
}
