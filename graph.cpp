#include"graph.h"

graph* graph_create(int n) {
	graph* g = (graph*)malloc(n * sizeof(graph));
	
	if (!g) {
		return NULL;
	} 	
	
	g->n = n;
	g->adj_matrix = (int**)calloc(n, sizeof(int *));
	
	if (!g->adj_matrix) {
		return NULL;
	}

	int i;
	for (i = 0; i < n; i++) {
		g->adj_matrix[i] = (int *)calloc(n, sizeof(int));
		
		if (!g->adj_matrix[i]) {
			return NULL;
		}
	}
	return g;
}

void graph_delete(graph* g) {
	int i;

	for (i = 0; i < g->n; i++)
		free(g->adj_matrix[i]);

	free(g->adj_matrix);
}

int graph_add_edge(int u, int v, graph* g) {
	
	if (u > g->n || v > g->n) {
		return -1;
	}
	
	g->adj_matrix[u - 1][v - 1] = 1;
	
	return 1;	
}
	
int graph_add_vertex(graph* g) {
	g->n++;
	g->adj_matrix = (int **)realloc(g->adj_matrix, g->n * sizeof(int *));
	
	if (!g->adj_matrix) {
		return -1;
	}

	int i;
	
	for (i = 0; i < g->n; i++) {
		g->adj_matrix[i] = (int *)realloc(g->adj_matrix[i], g->n * sizeof(int));

		if (!g->adj_matrix[i]) {
			return -1;
		}
	}

	for (i = 0; i < g->n; i++) {
		g->adj_matrix[i][g->n - 1] = 0;
		g->adj_matrix[g->n - 1][i] = 0;
	}
		
	return 1;
}

int graph_delete_edge(int u, int v, graph* g) {

	if (u > g->n || v > g->n) {
		return -1;
	}

	g->adj_matrix[u - 1][v - 1] = 0;

	return 1;
}

int graph_delete_vertex(int u, graph* g) {
	if (u > g->n) {
		return -1;
	}

	if (g->n == 1) {
		free(g->adj_matrix[0]);
		free(g->adj_matrix);
		g->n = 0;
	}

	int i, j;
	int** new_adj_matrix = (int**)malloc((g->n - 1) * sizeof(int *));
	
	if (!new_adj_matrix) {
		return -1;
	}

	for (i = 0; i < g->n - 1; i++) {
                new_adj_matrix[i] = (int *)malloc((g->n - 1) * sizeof(int));

                if (!new_adj_matrix[i]) {
                        return -1;
                }
	
	}
	
	for (i = u - 1; i < g->n - 1; i++)
		g->adj_matrix[i] = g->adj_matrix[i + 1];
	
	for (i = 0; i < g->n - 1; i++) {
		for (j = 0; j < g->n - 1; j++) {
			if (j < u - 1)
				new_adj_matrix[i][j] = g->adj_matrix[i][j];
			else
				new_adj_matrix[i][j] =  g->adj_matrix[i][j + 1];
		}
	}
	g->adj_matrix = new_adj_matrix;
	g->n--;
	return 1;
}
	
	
	
	
