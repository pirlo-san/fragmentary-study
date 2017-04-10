#include <stdio.h>
#include <string.h>
#include "graph.h"

static void _graph_test_case01(void)
{
    int graphid     = -1;
    int vertices[]  = {1, 2, 3, 4, 5, 6};
    int i           = 0;
    int nvertex     = 0;
    int nedge       = 0;
    int weight      = 0;
    int indegree    = 0;
    int outdegree   = 0;
    int totaldegree = 0;
    
    ASSERT_EQUAL_INT(e_graph_success, graph_alloc(0, &graphid));

    for (i = 0; i < sizeof(vertices) / sizeof(vertices[0]); ++i)
        ASSERT_EQUAL_INT(e_graph_success, graph_add_vertex(graphid));

    ASSERT_EQUAL_INT(e_graph_success, graph_get_vertex_num(graphid, &nvertex));
    ASSERT_EQUAL_INT(sizeof(vertices) / sizeof(vertices[0]), nvertex);

    ASSERT_EQUAL_INT(e_graph_success, graph_add_edge(graphid, 0, 1, 6));
    ASSERT_EQUAL_INT(e_graph_success, graph_add_edge(graphid, 0, 2, 2));
    ASSERT_EQUAL_INT(e_graph_success, graph_add_edge(graphid, 0, 3, 1));
    
    ASSERT_EQUAL_INT(e_graph_success, graph_add_edge(graphid, 1, 2, 6));
    ASSERT_EQUAL_INT(e_graph_success, graph_add_edge(graphid, 1, 4, 3));

    ASSERT_EQUAL_INT(e_graph_success, graph_add_edge(graphid, 2, 3, 2));
    ASSERT_EQUAL_INT(e_graph_success, graph_add_edge(graphid, 2, 4, 2));    
    ASSERT_EQUAL_INT(e_graph_success, graph_add_edge(graphid, 2, 5, 4));

    ASSERT_EQUAL_INT(e_graph_success, graph_add_edge(graphid, 3, 5, 5));
    
    ASSERT_EQUAL_INT(e_graph_success, graph_add_edge(graphid, 4, 5, 3));

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_num(graphid, &nedge));
    ASSERT_EQUAL_INT(10, nedge);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, 2, 0, &weight));
    ASSERT_EQUAL_INT(2, weight);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, 2, 1, &weight));
    ASSERT_EQUAL_INT(6, weight);    

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, 2, 2, &weight));
    ASSERT_EQUAL_INT(M_GRAPH_INFINITE_WEIGHT, weight);    

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, 2, 3, &weight));
    ASSERT_EQUAL_INT(2, weight);      

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, 2, 4, &weight));
    ASSERT_EQUAL_INT(2, weight);  

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, 2, 5, &weight));
    ASSERT_EQUAL_INT(4, weight);      

    ASSERT_EQUAL_INT(e_graph_success, graph_rmv_edge(graphid, 2, 0));
    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, 2, 0, &weight));
    ASSERT_EQUAL_INT(M_GRAPH_INFINITE_WEIGHT, weight);
    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, 0, 2, &weight));
    ASSERT_EQUAL_INT(M_GRAPH_INFINITE_WEIGHT, weight);
    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_num(graphid, &nedge));
    ASSERT_EQUAL_INT(9, nedge);    

    ASSERT_EQUAL_INT(e_graph_success, graph_rmv_vertex(graphid, 2));
    ASSERT_EQUAL_INT(e_graph_success, graph_get_vertex_num(graphid, &nvertex));
    ASSERT_EQUAL_INT(sizeof(vertices) / sizeof(vertices[0]) - 1, nvertex);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_num(graphid, &nedge));
    ASSERT_EQUAL_INT(5, nedge);  

    ASSERT_EQUAL_INT(e_graph_success, graph_update_edge_weight(graphid, 0, 1, 100));
    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, 0, 1, &weight));
    ASSERT_EQUAL_INT(100, weight); 
    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, 1, 0, &weight));
    ASSERT_EQUAL_INT(100, weight); 

    ASSERT_EQUAL_INT(e_graph_success, graph_get_vertex_indegree(graphid, 0, &indegree));
    ASSERT_EQUAL_INT(2, indegree);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_vertex_outdegree(graphid, 0, &outdegree));
    ASSERT_EQUAL_INT(2, outdegree);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_vertex_total_degree(graphid, 0, &totaldegree));
    ASSERT_EQUAL_INT(2, totaldegree);    

    ASSERT_EQUAL_INT(e_graph_success, graph_free(graphid));
}

static void _graph_test_cases(void)
{
    _graph_test_case01();
}

int main(int argc, char *argv[])
{

    fprintf(stderr, "graph test begin\n");
    _graph_test_cases();
    fprintf(stderr, "graph test end\n\n");

    return 0;    
}

