#include"graph.h"

int main() {
	graph * g = graph_create(10);
	int i;
	graph_add_edge(0, 1, g);
	graph_add_edge(0, 5, g);
	graph_add_edge(0, 10, g);
	graph_add_vertex(g);
	for (i = 0; i < 11; i++)
		printf("%d ",g->adjancy_matrix[0][i]);
	return 0;
}
