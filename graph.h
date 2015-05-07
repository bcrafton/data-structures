#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "stack.h"
#include "queue.h"
#include "set.h"
#include "hashtable.h"
#include "priority_queue.h"

typedef void* GRAPH_TYPE;
typedef struct Graph Graph;
typedef struct Edge Edge;
typedef struct Vertex Vertex;

struct Edge {
	int key;
	int weight;
	Vertex* v1;
	Vertex* v2;
};

struct Vertex {
	int key;
	GRAPH_TYPE value;
	Vector* edges;
};

struct Graph{
	int size;
	Vector* vertex_list;
	Vector* edge_list;
	Hashtable* vertex_table;
	Hashtable* edge_table;
};

Edge* add_edge(int key, Vertex* v1, Vertex* v2, int weight, Graph* graph);
Vertex* add_vertex(int key, GRAPH_TYPE value, Graph* graph);
/*
// static constructors
Edge* edge_constructor(Vertex* v1, Vertex* v2, int weight);
Vertex* vertex_constructor(GRAPH_TYPE value);
*/
Graph* graph_constructor();
void print_graph(Graph *graph);
void print_edge(Edge *edge);
void print_vertex(Vertex *vertex);

Edge* get_edge(int key, Graph* graph);
Vertex* get_vertex(int key, Graph* graph);

Vector* adjacent_vertices(Vertex *vertex);
void BredthFirstTraversal(Vertex *start);
void DepthFirstTraversal(Vertex *start);

#endif