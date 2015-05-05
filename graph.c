#include "graph.h"

static int edge_count = 0;
static int vertex_count = 0;

static Edge* edge_constructor(Vertex* v1, Vertex* v2, int weight){
	Edge* edge = malloc(sizeof(Edge));
	edge->v1 = v1;
	edge->v2 = v2;
	edge->weight = weight;
	edge->id = edge_count;
	edge_count++;
	return edge;
}
static Vertex* vertex_constructor(GRAPH_TYPE value){
	Vertex* vertex = malloc(sizeof(Vertex));
	vertex->value = value;
	vertex->edges = vector_constructor();
	vertex->id = vertex_count;
	vertex_count++;
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

void print_vertex(Vertex *vertex){
	printf("Vertex id#: %d\n", vertex->id);
	printf("Connected Edges (%d):\n", vertex_edge_count(vertex));
	int edgeCounter = 0;
	for(edgeCounter = 0; edgeCounter < vertex_edge_count(vertex); edgeCounter++){
		Edge* e = vector_get(edgeCounter, vertex->edges);
		print_edge(e);
	}
}

void print_edge(Edge *edge){
	printf("Edge id#: %d, v1: %d, v2: %d\n", edge->id, edge->v1->id, edge->v2->id);
}

int vertex_edge_count(Vertex* vertex){
	vector_size(vertex->edges);
}

int graph_edge_count(Graph *graph){
	vector_size(graph->edge_list);
}

int graph_vertex_count(Graph *graph){
	vector_size(graph->vertex_list);
}

Edge* get_edge(int edge_id){

}

Vertex* get_vertex(int vertex_id){

}

Vector* adjacent_vertices(Vertex *vertex){
	Vector* vertices = vector_constructor();
	int edge_counter = 0;
	for(edge_counter = 0; edge_counter < vertex_edge_count(vertex); edge_counter++){
		Edge *e = vector_get(edge_counter, vertex->edges);
		if(e->v1 != vertex){
			vector_add(e->v1, vertices);
		}
		else{
			vector_add(e->v2, vertices);
		}
	}
	return vertices;
}

// will have to pass the print functions for vertex and edge?
// or can just use the vector get functions and do it manually.
void print_graph(Graph *graph){
	int vertexCounter = 0;
	for(vertexCounter = 0; vertexCounter < graph_vertex_count(graph); vertexCounter++){
		Vertex* v = vector_get(vertexCounter, graph->vertex_list);
		print_vertex(v);
	}
}
