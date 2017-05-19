#include"graph.h"

graph* graph_create(int vertex_count) {
	graph* g = (graph*)malloc(sizeof(graph));
	
	if (!g) {
		return NULL;
	} 	
	
	g->vertex_count = vertex_count;
	g->adj_matrix = (int**)calloc(vertex_count, sizeof(int *));
	
	if (!g->adj_matrix) {
		return NULL;
	}

	int i;
	for (i = 0; i < vertex_count; i++) {
		g->adj_matrix[i] = (int*)calloc(vertex_count, sizeof(int));
		
		if (!g->adj_matrix[i]) {
			return NULL;
		}
	}
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
		return -1;
	}	

	if (u > g->vertex_count || v > g->vertex_count) {
		return -1;
	}
	
	g->adj_matrix[u - 1][v - 1] = 1;
	
	return 1;	
}
	
int graph_add_vertex(graph* g) {
	if (!g) {
		g = graph_create(1);
		return 1;
	}

	g->vertex_count++;
	int n = g->vertex_count;
	g->adj_matrix = (int **)realloc(g->adj_matrix, n * sizeof(int *));
	
	if (!g->adj_matrix) {
		return -1;
	}

	int i;
	
	for (i = 0; i < n; i++) {
		g->adj_matrix[i] = (int *)realloc(g->adj_matrix[i], n * sizeof(int));

		if (!g->adj_matrix[i]) {
			return -1;
		}
	}

	for (i = 0; i < n; i++) {
		g->adj_matrix[i][n - 1] = 0;
		g->adj_matrix[n - 1][i] = 0;
	}
		
	return 1;
}

int graph_delete_edge(int u, int v, graph* g) {
	if (!g) {
		return -1;
	}
	
	if (u > g->vertex_count || v > g->vertex_count) {
		return -1;
	}

	g->adj_matrix[u - 1][v - 1] = 0;

	return 1;
}

int graph_delete_vertex(int u, graph* g) {
	if (!g) {
		return -1;
	}
	
	int n = g->vertex_count;
	
	if (u > n) {
		return -1;
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
	return 1;
}

int graph_has_edge(int u, int v, graph* g) {
	if (!g) {
		return -1;
	}
	
	if (u > g->vertex_count || v > g->vertex_count) {
		return -1;
	}

	if (g->adj_matrix[u - 1][v - 1])
		return 1;

	return 0;
}

int graph_vertex_count(graph* g) {
	
	if (!g) {
		return -1;	
	}
	
	return g->vertex_count;

}

int graph_edge_count(graph* g) {
	
	if (!g) {
		return -1;
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
		return -1;
	}
	int i;
	for (i = 0; i < g->vertex_count; i++)
		free(g->adj_matrix[i]);
	free(g->adj_matrix);	
	g->adj_matrix = adj_matrix;
	g->vertex_count = n;

	return 1;
}

int print_adj_matrix(graph* g) {
	
	if (!g) {
		return -1;
	}
	
	int i, j;
	printf("--Adjancy matrix--\n");
	for (i = 0; i < g->vertex_count; i++) {
		for (j = 0; j < g->vertex_count; j++)
			printf("%d ", g->adj_matrix[i][j]);
		printf("\n");
	}
	return 1;
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

int* search(int u, graph* g) {
	int i;
	int* visited = (int*)calloc(g->vertex_count, sizeof(int));
	
	if (!visited) {
		return NULL;
	}
	
	dfs(u, visited, g);
	return visited;
}
