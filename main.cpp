#include"graph.h"
#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void test_create_delete() {
	int flag1 = 0, flag2 = 0;
	graph* g = graph_create(3);
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
	graph_delete(&g);	
	if (!flag1) {
		CU_PASS("graph_create and graph_delete succesed\n");
	}
}

void test_add_edge_vertex() {
	graph* g = graph_create(4);
	graph_add_edge(1, 2, g);
	graph_add_edge(2, 1, g);
	graph_add_edge(2, 3, g);
	graph_add_edge(3, 4, g);
	graph_add_vertex(g);
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
	if (flag) {
		CU_FAIL("graph_add_edge_or_vertex\n");
	}
	else {
		CU_PASS("graph_add_edge_and_vertex\n");
	}
	graph_delete(&g);
}

void test_delete_edge_vertex() {
	graph* g = graph_create(4);
        graph_add_edge(1, 2, g);
        graph_add_edge(2, 1, g);
        graph_add_edge(2, 3, g);
        graph_add_edge(3, 4, g);
        graph_add_vertex(g);
        graph_add_edge(4, 5, g);
	graph_add_edge(3, 5, g);
	graph_add_edge(1, 3, g);
	graph_add_edge(5, 4, g);
	graph_delete_edge(3, 4, g);
	graph_add_vertex(g);
	graph_delete_vertex(2, g);
	int matrix[5][5] = {0, 1, 0, 0,0,
			    0, 0, 0, 1,0,
			    0, 0, 0, 1,0,
			    0, 0, 1, 0,0,
			    0, 0, 0, 0,0};
	int i, j, flag = 0;
        for (i = 0; i < 5; i++)
                for (j = 0; j < 5; j++)
                        if (g->adj_matrix[i][j] != matrix[i][j])
                                flag = 1;
        if (flag) {
                CU_FAIL("graph_delete_edge_or_vertex\n");
        }
        else {
                CU_PASS("graph_delete_edge_and_vertex\n");
        }
	graph_delete(&g);
	
}

void test_hasedge_count_vertex_edge();


void test_get_matrix() {
	graph* g = graph_create(1);
	int** tmp = (int **)calloc(5, sizeof(int *));
	int i, j, flag = 0;
	for (i = 0; i < 5; i++) {
		tmp[i] = (int *)calloc(5, sizeof(int));
		tmp[i][4 - i] = 1;
	}
	get_adj_matrix(5, tmp, g);
	for (i = 0; i < 5; i++)
		for (j = 0; j < 5; j++)
			if (g->adj_matrix[i][j] != tmp[i][j])
				flag = 1;
	if (flag) {
		CU_FAIL("get_matrix failed\n");
	}
	else {
		CU_PASS("get_matrix passed\n");
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
	if ((NULL == CU_add_test(pSuite, "test_create", test_create_delete)) ||
	    (NULL == CU_add_test(pSuite, "test_add", test_add_edge_vertex)) ||
	    (NULL == CU_add_test(pSuite, "test_delete", test_delete_edge_vertex)) ||
	    (NULL == CU_add_test(pSuite, "test_get_matrix", test_get_matrix))) {
			CU_cleanup_registry();
      			return CU_get_error();
   	}
	CU_basic_set_mode(CU_BRM_VERBOSE);
   	CU_basic_run_tests();
 	CU_cleanup_registry();
   	return CU_get_error();
}
