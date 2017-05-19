#include<stdio.h>
#include<stdlib.h>

struct graph {
	int vertex_count;
	int ** adj_matrix;
};

typedef struct graph graph;

graph* graph_create(int vertex_count);

void graph_delete(graph* g);

int graph_add_edge(int u, int v, graph* g);

int graph_add_vertex(graph* g);

int graph_delete_edge(int u, int v,graph* g);

int graph_delete_vertex(int u,graph* g);

int graph_has_edge(int u, int v, graph* g);

int graph_vertex_count(graph* g);

int graph_edge_count(graph* g);

