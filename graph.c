#include "graph.h"

static Edge* edge_constructor(Vertex* v1, Vertex* v2, int weight){
	Edge* edge = malloc(sizeof(Edge));
	edge->v1 = v1;
	edge->v2 = v2;
	edge->weight = weight;
	return edge;
}
static Vertex* vertex_constructor(GRAPH_TYPE value){
	Vertex* vertex = malloc(sizeof(Vertex));
	vertex->value = value;
	vertex->edges = vector_constructor();
	return vertex;
}

Edge* add_edge(Vertex* v1, Vertex* v2, int weight, Graph* graph){
	Edge* edge = edge_constructor(v1, v2, weight);
	vector_add(edge, v1->edges);
	vector_add(edge, v2->edges);
	vector_add(edge, graph->edge_list);
	return edge;
}
Vertex* add_vertex(GRAPH_TYPE value, Graph* graph){
	Vertex *vertex = vertex_constructor(value);
	vector_add(vertex, graph->vertex_list);
	return vertex;
}
Graph* graph_constructor(){
	Graph* graph = malloc(sizeof(Graph));
	graph->vertex_list = vector_constructor();
	graph->edge_list = vector_constructor();
	return graph;
}
