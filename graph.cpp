#include"graph.h"

graph* graph_create(int n) {
	graph* g = (graph*)malloc(sizeof(struct graph));
	
	if (!g) {
		return NULL;
	}
	
	g->n = n;
	g->adjancy_matrix = (int **)calloc(n, sizeof(int *));
	
	if (!g->adjancy_matrix) {
		return NULL;
	}

	int i;
	for (i = 0; i < n; i++) {
		g->adjancy_matrix[i] = (int *)calloc(n, sizeof(int));
		
		if (!g->adjancy_matrix[i]) {
			return NULL;
		}
	}
	return g;
}

void graph_destroy(graph* g) {
	int i;

	for (i = 0; i < g->n; i++)
		free(g->adjancy_matrix[i]);

	free(g->adjancy_matrix);

	free(g);
}

int graph_add_edge(int u, int v, graph* g) {
	
	if (u >= g->n || v >= g->n) {
		return -1;
	}
	
	g->adjancy_matrix[u][v] = 1;
	
	return 1;	
}
	
int graph_add_vertex(graph* g) {
	g->n++;
	g->adjancy_matrix = (int **)realloc(g->adjancy_matrix, g->n * sizeof(int *));
	
	if (!g->adjancy_matrix) {
		return -1;
	}

	int i;
	
	for (i = 0; i < g->n; i++) {
		g->adjancy_matrix[i] = (int *)realloc(g->adjancy_matrix[i], g->n * sizeof(int));

		if (!g->adjancy_matrix[i]) {
			return -1;
		}
	}

	for (i = 0; i < g->n; i++) {
		g->adjancy_matrix[i][g->n - 1] = 0;
		g->adjancy_matrix[g->n - 1][i] = 0;
	}
		
	return 1;
}


