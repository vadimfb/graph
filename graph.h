#include<stdio.h>
#include<stdlib.h>

struct graph {
	int n;
	int ** adjancy_matrix;
};

typedef struct graph graph;

typedef int* my_int;

graph* graph_create(int n);

void graph_destroy(graph* g);

int graph_add_edge(int u, int v, graph* g);

int graph_add_vertex(graph* g);

void graph_delete_edge(graph* g);

void graph_delete_vertex(graph* g);

int graph_has_edge(int u, int v, graph* g);

int graph_vertex_count(graph* g);

int edge_count(graph* g);
