#include "graph.h"

static int edge_count = 0;
static int vertex_count = 0;

static int int_hash(void *v){
	return *((int*)v);
}

static int vertex_compare(void *o1, void *o2){
	return *((int*)o1) - *((int*)o2);
}



static Edge* edge_constructor(int key, Vertex* v1, Vertex* v2, int weight){
	Edge* edge = malloc(sizeof(Edge));
	edge->v1 = v1;
	edge->v2 = v2;
	edge->weight = weight;
	edge->key = key;
	return edge;
}
static Vertex* vertex_constructor(int key, GRAPH_TYPE value){
	Vertex* vertex = malloc(sizeof(Vertex));
	vertex->value = value;
	vertex->edges = vector_constructor();
	vertex->key = key;
	return vertex;
}

Edge* add_edge(int key, Vertex* v1, Vertex* v2, int weight, Graph* graph){
	assert(table_contains(&key, graph->edge_table)==0);
	Edge* edge = edge_constructor(key, v1, v2, weight);
	vector_add(edge, v1->edges);
	vector_add(edge, v2->edges);

	vector_add(edge, graph->edge_list);
	table_add(&key, edge, graph->edge_table);
	return edge;
}
Vertex* add_vertex(int key, GRAPH_TYPE value, Graph* graph){
	assert(table_contains(&key, graph->vertex_table)==0);
	Vertex *vertex = vertex_constructor(key, value);
	vector_add(vertex, graph->vertex_list);
	table_add(&key, vertex, graph->vertex_table);
	return vertex;
}
Graph* graph_constructor(){
	Graph* graph = malloc(sizeof(Graph));
	graph->vertex_list = vector_constructor();
	graph->edge_list = vector_constructor();
	graph->vertex_table = hashtable_constructor(100, &int_hash);
	graph->edge_table = hashtable_constructor(100, &int_hash);
	return graph;
}

void print_vertex(Vertex *vertex){
	printf("Vertex key#: %d\n", vertex->key);
	printf("Connected Edges (%d):\n", vertex_edge_count(vertex));
	int edgeCounter = 0;
	for(edgeCounter = 0; edgeCounter < vertex_edge_count(vertex); edgeCounter++){
		Edge* e = vector_get(edgeCounter, vertex->edges);
		print_edge(e);
	}
}

void print_edge(Edge *edge){
	printf("Edge key#: %d, v1: %d, v2: %d\n", edge->key, edge->v1->key, edge->v2->key);
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

Edge* get_edge(int key, Graph* graph){
	return table_get(&key, graph->edge_table);
}

Edge* edge_between(Vertex* source, Vertex *target){
	int target_counter;
	int source_counter;
	for(target_counter = 0; target_counter < vertex_edge_count(target); target_counter++){
		for(source_counter = 0; source_counter < vertex_edge_count(source); source_counter++){
			if(vector_get(source_counter, source->edges) == vector_get(target_counter, target->edges)){
				return vector_get(source_counter, source->edges);
			}
		}
	}
	return NULL;
}

Vertex* get_vertex(int key, Graph* graph){
	return table_get(&key, graph->vertex_table);
}

void BredthFirstTraversal(Vertex *start){
	Queue* vertices = queue_constructor();
	Set* visited = set_constructor(100, &int_hash);
	queue_push(start, vertices);
	set_add(&(start->key), visited);
	while(queueIsEmpty(vertices) == 0){
		Vertex* front = queue_pop(vertices);
		Vector* adjacent_vertices_vector = adjacent_vertices(front);
		int counter;
		for(counter = 0; counter < vector_size(adjacent_vertices_vector); counter++) {
			Vertex *next = vector_get(counter, adjacent_vertices_vector);
			if(set_contains(&(next->key), visited) == 0){
				queue_push(next, vertices);
				set_add(&(next->key), visited);
			}
		}
		printf("%d\n", front->key);
	}
}

// pretty sure this works as depth first traversal. before we did the hasUnvisitedKey thing, but i do not think this is necessary.
// do it out in ur head and ull see. it keeps pushing on top so it will act as depth first. since it will keep visiting children on the one path.
/*
1  procedure DFS-iterative(G,v):
2      let S be a stack
3      S.push(v)
4      while S is not empty
5            v = S.pop() 
6            if v is not labeled as discovered:
7                label v as discovered
8                for all edges from v to w in G.adjacentEdges(v) do
9                    S.push(w)
*/
void DepthFirstTraversal(Vertex *start){
	Stack* vertices = stack_constructor();
	Set* visited = set_constructor(100, &int_hash);
	stack_push(start, vertices);
	set_add(&(start->key), visited);
	while(stackIsEmpty(vertices)==0){
		Vertex* top = stack_pop(vertices);
		Vector* adjacent_vertices_vector = adjacent_vertices(top);
		int counter;
		for(counter = 0; counter < vector_size(adjacent_vertices_vector); counter++) {
			Vertex *next = vector_get(counter, adjacent_vertices_vector);
			if(set_contains(&(next->key), visited) == 0){
				stack_push(next, vertices);
				set_add(&(next->key), visited);
			}
		}
		printf("%d\n", top->key);;
	}
}

// not sure if bad to do this instead of passing the heap the vertex list ... costs O(n) ... but dosnt fuck with our pointers ...
static void createVertexQueue(Graph *graph){
	PriorityQueue* queue = priorityqueue_constructor(&vertex_compare);
	int counter;
	for(counter = 0; counter < graph_vertex_count(graph); counter++){
		priorityqueue_push(vector_get(counter, graph->vertex_list), queue);
	}
}


/*
Vector* Dijkstra(Vertex* start, Graph* graph){
	// wud be interesting to consider how to make a table that takes a pointer as a key. like there has to be some way ... not hashing  ... to do it.
	Hashtable* weights = hashtable_constructor(100, &int_hash);
	Set* visited = set_constructor(100, &int_hash);
	PriorityQueue* queue = createVertexQueue(graph);
	while(priorityqueueIsEmpty(queue)==0){
		Vertex* front = priorityqueue_pop(queue);
		set_add(&(front->key), visited);
		Vector* adjacent_vertices_vector = adjacent_vertices(top);
		int counter;
		for(counter = 0; counter < vector_size(adjacent_vertices_vector); counter++) {
			Vertex *next = vector_get(counter, adjacent_vertices_vector);
			if(set_contains(&(next->key), visited) == 0) {
				Edge* bridge = edge_between(source, target);
				int weight = *((*int)table_get(&(front->key), weights)) + bridge->weight;
				if(table_contains(&(next->key), weights) == 0){
					table_add(&(next->key), &weight, weights);
				} else if(*((*int)table_get(&(next->key), weights)) > weight){
					table_add(&(next->key), &weight, weights);
				}
			}
		}
	}
}
*/

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

void print_graph(Graph *graph){
	int vertexCounter = 0;
	for(vertexCounter = 0; vertexCounter < graph_vertex_count(graph); vertexCounter++){
		Vertex* v = vector_get(vertexCounter, graph->vertex_list);
		print_vertex(v);
	}
}
