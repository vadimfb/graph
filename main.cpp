#include"graph.h"
#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"

int err;

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void test_create() {
	int flag1 = 0;
	graph* g = graph_create(3, err);
	if (g->vertex_count == 3) {
		int i, j;
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				if (g->adj_matrix[i][j] != 0)
					flag1 = 1;
		if (flag1) {
			CU_FAIL("graph_create failed\n");
		}
	}
	else {
		CU_FAIL("graph_create failed\n");
		flag1 = 1;
	}
	if (!flag1) {
		CU_PASS("graph_create and graph_delete succesed\n");
	}
	graph_delete(&g);
}

void test_add_edge() {
	graph* g = graph_create(5, err);
	graph_add_edge(1, 2, g);
	graph_add_edge(2, 1, g);
	graph_add_edge(2, 3, g);
	graph_add_edge(3, 4, g);
	graph_add_edge(4, 5, g);
	int matrix[5][5] = {0, 1, 0, 0, 0, 
			    1, 0, 1, 0, 0, 
			    0, 0, 0, 1, 0, 
			    0, 0, 0, 0, 1, 
			    0, 0, 0, 0, 0};
	int i, j, flag = 0;
	for (i = 0; i < 5; i++)
		for (j = 0; j < 5; j++)
			if (g->adj_matrix[i][j] != matrix[i][j])
				flag = 1;
	graph* g1 = NULL;
	err = graph_add_edge(1, 2, g1);
	if (err != EINVARG)
		flag = 1;
	err = graph_add_edge(4, 6, g);
	if (err != EINVARG)
		flag = 1;
	if (flag) {
		CU_FAIL("graph_add_edge failed\n");
	}
	else {
		CU_PASS("graph_add_edge passed\n");
	}
	graph_delete(&g);
}

void test_add_vertex() {
	graph* g = graph_create(2, err);
	graph_add_vertex(g, err);
        graph_add_edge(1, 2, g);
	graph_add_vertex(g, err);
        graph_add_edge(2, 1, g);
        graph_add_edge(2, 3, g);
	graph_add_vertex(g, err);
        graph_add_edge(3, 4, g);
        graph_add_edge(4, 5, g);
	int matrix[5][5] = {0, 1, 0, 0, 0,
                            1, 0, 1, 0, 0,
                            0, 0, 0, 1, 0,
                            0, 0, 0, 0, 1,
                            0, 0, 0, 0, 0};
        int i, j, flag = 0;
        for (i = 0; i < 5; i++)
                for (j = 0; j < 5; j++)
                        if (g->adj_matrix[i][j] != matrix[i][j])
                                flag = 1;
	graph * g1 = NULL;
	int val = graph_add_vertex(g1, err);
	if (val != ESUCCESS)
		flag = 1;
	if (flag) {
                CU_FAIL("graph_add_vertex failed\n");
        }
        else {
                CU_PASS("graph_add_vertex passed\n");
        }
        graph_delete(&g);
	graph_delete(&g1);
}

void test_delete_edge_vertex() {
	graph* g = graph_create(4, err);
        graph_add_edge(1, 2, g);
        graph_add_edge(2, 1, g);
        graph_add_edge(2, 3, g);
        graph_add_edge(3, 4, g);
        graph_add_vertex(g, err);
        graph_add_edge(4, 5, g);
	graph_add_edge(3, 5, g);
	graph_add_edge(1, 3, g);
	graph_add_edge(5, 4, g);
	graph_delete_edge(3, 4, g);
	graph_add_vertex(g, err);
	graph_delete_vertex(2, g);
	graph_delete_vertex(5, g);
	graph_delete_edge(1, 2, g);
	int matrix[4][4] = {0, 0, 0, 0,
			    0, 0, 0, 1,
			    0, 0, 0, 1,
			    0, 0, 1, 0};
	int i, j, flag = 0;
        for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                        if (g->adj_matrix[i][j] != matrix[i][j])
                                flag = 1;
	graph* g1 = NULL;
	graph* g2 = graph_create(1, err);
	if (graph_delete_vertex(1, g2) != ESUCCESS)
		flag = 1;
	if (graph_delete_edge(1, 2, g1) != EINVARG)
		flag = 1;
	if (graph_delete_edge(4, 5, g) != EINVARG)
		flag = 1;
	if (graph_delete_vertex(5, g) != EINVARG)
		flag = 1;
	if (graph_delete_vertex(1, g1) != EINVARG)
		flag = 1;
        if (flag) {
                CU_FAIL("graph_delete_edge_or_vertex failed\n");
        }
        else {
                CU_PASS("graph_delete_edge_and_vertex passed\n");
        }
	graph_delete(&g);
	
}

void test_has_edge_count_vertex_edge() {
	graph* g = graph_create(4, err);
        graph_add_edge(1, 2, g);
        graph_add_edge(2, 1, g);
        graph_add_edge(2, 3, g);
        graph_add_edge(3, 4, g);
        graph_add_vertex(g, err);
        graph_add_edge(4, 5, g);
        graph_add_edge(3, 5, g);
        graph_add_edge(1, 3, g);
        graph_add_edge(5, 4, g);
	int flag = 0;
	if (graph_has_edge(2, 3, g) != 1) {
		flag = 1;
	}
	if (graph_has_edge(1, 5, g) != 0) {
		flag = 1;
	}
	if (graph_has_edge(1, 6, g) != EINVARG) {
		flag = 1;
	}
	graph* g1 = NULL;
	if (graph_has_edge(1, 2, g1) != EINVARG) {
		flag = 1;
	}
	if (graph_vertex_count(g) != 5)
		flag = 1;
	if (graph_edge_count(g) != 8)
		flag = 1;
	if (graph_vertex_count(g1) != EINVARG)
		flag = 1;
	if (graph_edge_count(g1) != EINVARG)
		flag = 1;
	if (flag) {
		CU_FAIL("graph_has_edge, graph_count failed\n");
	}
	else
		CU_PASS("graph_has_edge, graph_count succesed\n");
	graph_delete(&g);
}

void test_get_matrix() {
	graph* g = graph_create(1, err);
	int** tmp = (int**)calloc(5, sizeof(int *));
	int i, j, flag = 0;
	for (i = 0; i < 5; i++) {
		tmp[i] = (int*)calloc(5, sizeof(int));
		tmp[i][4 - i] = 1;
	}
	get_adj_matrix(5, tmp, g);
	for (i = 0; i < 5; i++)
		for (j = 0; j < 5; j++)
			if (g->adj_matrix[i][j] != tmp[i][j])
				flag = 1;
	graph* g1 = NULL;
	if (get_adj_matrix(0, NULL, g1) != EINVARG)
		flag = 1;
	if (flag) {
		CU_FAIL("get_matrix failed\n");
	}
	else {
		CU_PASS("get_matrix passed\n");
	}
}

void test_dfs_search() {
	graph* g = graph_create(4, err);
        graph_add_edge(1, 2, g);
        graph_add_edge(2, 1, g);
        graph_add_edge(2, 3, g);
        graph_add_edge(3, 4, g);
        graph_add_vertex(g, err);
        graph_add_edge(4, 5, g);
        graph_add_edge(3, 5, g);
        graph_add_edge(1, 3, g);
        graph_add_edge(5, 4, g);
	int* visit = search(3, g, err);
	int* visited = (int *)calloc(5, sizeof(int));
	dfs(3, visited, g);
	int flag = 0, i;
	int answer[] = {0, 0, 1, 1, 1};
	for (i = 0; i < 5; i++)
		if (visit[i] != answer[i] || visited[i] != answer[i])
			flag = 1;
	graph* g1 = NULL;
	visit = search(1, g1, err);
	if (err != EINVARG || visit != NULL) {
		flag = 1;
	}
	if (flag) {
		CU_FAIL("dfs failed\n");
	}
	else {
		CU_PASS("dfs passed\n");
	}
}
	
int main() {
	CU_pSuite pSuite = NULL;

   	/* initialize the CUnit test registry */
   	if (CUE_SUCCESS != CU_initialize_registry())
      		return CU_get_error();

   	/* add a suite to the registry */
   	pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
   	if (NULL == pSuite) {
      		CU_cleanup_registry();
      		return CU_get_error();
   	}
   	/* add the tests to the suite */
	if ((NULL == CU_add_test(pSuite, "test_create", test_create)) ||
	    (NULL == CU_add_test(pSuite, "test_add_ver", test_add_vertex)) ||
	    (NULL == CU_add_test(pSuite, "test_add_edge", test_add_edge)) ||
	    (NULL == CU_add_test(pSuite, "test_delete", test_delete_edge_vertex)) ||
	    (NULL == CU_add_test(pSuite, "test_get_matrix", test_get_matrix)) ||
	    (NULL == CU_add_test(pSuite, "test_has_edge_count", test_has_edge_count_vertex_edge)) ||
	    (NULL == CU_add_test(pSuite, "test_dfs", test_dfs_search))) {
			CU_cleanup_registry();
      			return CU_get_error();
   	}
	CU_basic_set_mode(CU_BRM_VERBOSE);
   	CU_basic_run_tests();
 	CU_cleanup_registry();
   	return CU_get_error();
}
