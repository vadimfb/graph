#include"graph.h"

int main() {
	graph * g = graph_create(3);
	int i, j;
	graph_add_edge(1, 2, g);
	graph_add_edge(2, 1, g);
	graph_add_edge(2, 3, g);
	graph_add_edge(1, 3, g);
	graph_add_edge(3, 2, g);
	graph_add_vertex(g);
	graph_add_edge(3, 4, g);
        graph_add_edge(4, 3, g);
	graph_delete_edge(4, 3, g);
	graph_delete_edge(3, 4, g);
	printf("%d %d\n", graph_has_edge(1, 2, g), graph_has_edge(3, 4, g));
	int* visit = search(1, g);
	for (i = 0; i < graph_vertex_count(g); i++)
		printf("%d ", visit[i]);
	free(visit);
	printf("\n");
	print_adj_matrix(g);
	graph_delete_vertex(3, g);
	print_adj_matrix(g);
	int** tmp = (int**)calloc(5, sizeof(int*));
	for (i = 0; i < 5; i++) {
		tmp[i] = (int*)calloc(5, sizeof(int));
		tmp[i][4 - i] = 1;
	}
	get_adj_matrix(5, tmp, g);
	printf("%d\n", graph_vertex_count(g));
	printf("%d\n", graph_edge_count(g));
	int* visited = (int*)calloc(5, sizeof(int));
	dfs(1, visited, g);
	for (i = 0; i < graph_vertex_count(g); i++)
		printf("%d ", visited[i]);
	printf("\n");
	free(visited);
	print_adj_matrix(g);
	graph_delete(g);
	return 0;
}
