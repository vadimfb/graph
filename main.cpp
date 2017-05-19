#include"graph.h"

int main() {
	graph * g = graph_create(3);
	int i, j;
	graph_add_edge(1, 2, g);
	graph_add_edge(2, 1, g);
	graph_add_edge(2, 3, g);
	graph_add_edge(3, 2, g);
	graph_add_vertex(g);
	graph_add_edge(3, 4, g);
        graph_add_edge(4, 3, g);
//	graph_delete_edge(4, 3, g);
	graph_delete_vertex(3, g);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			printf("%d ",g->adj_matrix[i][j]);
		printf("\n");
	}
	graph_delete(g);
	return 0;
}
