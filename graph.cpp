#include"graph.h"

graph* graph_create(int vertex_count,  int error) {
	graph* g = (graph*)malloc(sizeof(graph));
	
	if (!g) {
		error = EALLOC;
		return NULL;
	} 	
	
	g->vertex_count = vertex_count;
	g->adj_matrix = (int**)calloc(vertex_count, sizeof(int *));
	
	if (!g->adj_matrix) {
		error = EALLOC;
		return NULL;
	}

	int i;
	for (i = 0; i < vertex_count; i++) {
		g->adj_matrix[i] = (int*)calloc(vertex_count, sizeof(int));
		
		if (!g->adj_matrix[i]) {
			error = EALLOC;
			return NULL;
		}
	}
	error = ESUCCESS;
	return g;
}

void graph_delete(graph** g) {
	int i;
	if (*g) {
	
		for (i = 0; i < (*g)->vertex_count; i++)
			free((*g)->adj_matrix[i]);
		free((*g)->adj_matrix);
		free(*g);
	}
}

int graph_add_edge(int u, int v, graph* g) {
	if (!g) {
		return EINVARG;
	}	

	if (u > g->vertex_count || v > g->vertex_count) {
		return EINVARG;
	}
	
	g->adj_matrix[u - 1][v - 1] = 1;
	
	return ESUCCESS;	
}
	
int graph_add_vertex(graph* g, int error) {
	if (!g) {
		g = graph_create(1, error);
		return ESUCCESS;
	}

	g->vertex_count++;
	int n = g->vertex_count;
	g->adj_matrix = (int **)realloc(g->adj_matrix, n * sizeof(int *));
	
	if (!g->adj_matrix) {
		return EALLOC;
	}

	int i;
	
	for (i = 0; i < n; i++) {
		g->adj_matrix[i] = (int *)realloc(g->adj_matrix[i], n * sizeof(int));

		if (!g->adj_matrix[i]) {
			return EALLOC;
		}
	}

	for (i = 0; i < n; i++) {
		g->adj_matrix[i][n - 1] = 0;
		g->adj_matrix[n - 1][i] = 0;
	}
		
	return ESUCCESS;
}

int graph_delete_edge(int u, int v, graph* g) {
	if (!g) {
		return EINVARG;
	}
	
	if (u > g->vertex_count || v > g->vertex_count) {
		return EINVARG;
	}

	g->adj_matrix[u - 1][v - 1] = 0;

	return ESUCCESS;
}

int graph_delete_vertex(int u, graph* g) {
	if (!g) {
		return EINVARG;
	}
	
	int n = g->vertex_count;
	
	if (u > n) {
		return EINVARG;
	}

	if (n == 1) {
		free(g->adj_matrix[0]);
		free(g->adj_matrix);
		g->vertex_count = 0;
		return 1;
	}

	int i, j;
	for (i = u - 1; i < n - 1; i++)
		for (j = 0; j < n; j++)
			g->adj_matrix[i][j] = g->adj_matrix[i + 1][j];

	for (i = 0; i < n - 1; i++) {
		for (j = u - 1; j < n - 1; j++) {
			g->adj_matrix[i][j] =  g->adj_matrix[i][j + 1];
		}
	}
	free(g->adj_matrix[g->vertex_count - 1]);
	g->vertex_count--;
	return ESUCCESS;
}

int graph_has_edge(int u, int v, graph* g) {
	if (!g) {
		return EINVARG;
	}
	
	if (u > g->vertex_count || v > g->vertex_count) {
		return EINVARG;
	}

	if (g->adj_matrix[u - 1][v - 1])
		return 1;

	return 0;
}

int graph_vertex_count(graph* g) {
	
	if (!g) {
		return EINVARG;	
	}
	
	return g->vertex_count;

}

int graph_edge_count(graph* g) {
	
	if (!g) {
		return EINVARG;
	}

	int i, j, count = 0, n = g->vertex_count;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (g->adj_matrix[i][j])
				count++;
	return count;
}

int get_adj_matrix(int n, int** adj_matrix, graph* g) {
	
	if (!g) {
		return EINVARG;
	}
	int i;
	for (i = 0; i < g->vertex_count; i++)
		free(g->adj_matrix[i]);
	free(g->adj_matrix);	
	g->adj_matrix = adj_matrix;
	g->vertex_count = n;

	return ESUCCESS;
}

void dfs(int u, int* visited, graph* g) {
	visited[u - 1] = 1;
	int i;
	for (i = 0; i < g->vertex_count; i++) {
		if (g->adj_matrix[u - 1][i] && visited[i] == 0) {
			dfs(i + 1, visited, g);
		}
	}
}

int* search(int u, graph* g, int error) {
	
	if (!g) {
		error = EINVARG;
		return NULL;
	}

	int* visited = (int*)calloc(g->vertex_count, sizeof(int));	

	if (!visited) {
		error = EALLOC;
		return NULL;
	}
	
	dfs(u, visited, g);
	error = ESUCCESS;
	return visited;
}
