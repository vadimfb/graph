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
	graph_delete_edge(4, 3, g);
	graph_delete_vertex(3, g);
	print_adj_matrix(g);
	int** tmp = (int**)calloc(5, sizeof(int*));
	for (i = 0; i < 5; i++) {
		tmp[i] = (int*)calloc(5, sizeof(int));
		tmp[i][5 - i] = 1;
	}
	get_adj_matrix(tmp, g);
	print_adj_matrix(g);
	graph_delete(g);
	return 0;
}
