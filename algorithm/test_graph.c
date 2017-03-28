#include "graph.h"
#include "test_api.h"

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
    
    ASSERT_EQUAL_INT(e_graph_success, alloc_graph(0, &graphid));

    for (i = 0; i < sizeof(vertices) / sizeof(vertices[0]); ++i)
        ASSERT_EQUAL_INT(e_graph_success, add_graph_vertex(graphid, &vertices[i]));

    ASSERT_EQUAL_INT(e_graph_success, get_graph_vertex_num(graphid, &nvertex));
    ASSERT_EQUAL_INT(sizeof(vertices) / sizeof(vertices[0]), nvertex);

    ASSERT_EQUAL_INT(e_graph_success, add_graph_edge(graphid, &vertices[0], &vertices[1], 6));
    ASSERT_EQUAL_INT(e_graph_success, add_graph_edge(graphid, &vertices[0], &vertices[2], 2));
    ASSERT_EQUAL_INT(e_graph_success, add_graph_edge(graphid, &vertices[0], &vertices[3], 1));
    
    ASSERT_EQUAL_INT(e_graph_success, add_graph_edge(graphid, &vertices[1], &vertices[2], 6));
    ASSERT_EQUAL_INT(e_graph_success, add_graph_edge(graphid, &vertices[1], &vertices[4], 3));

    ASSERT_EQUAL_INT(e_graph_success, add_graph_edge(graphid, &vertices[2], &vertices[3], 2));
    ASSERT_EQUAL_INT(e_graph_success, add_graph_edge(graphid, &vertices[2], &vertices[4], 2));    
    ASSERT_EQUAL_INT(e_graph_success, add_graph_edge(graphid, &vertices[2], &vertices[5], 4));

    ASSERT_EQUAL_INT(e_graph_success, add_graph_edge(graphid, &vertices[3], &vertices[5], 5));
    
    ASSERT_EQUAL_INT(e_graph_success, add_graph_edge(graphid, &vertices[4], &vertices[5], 3));

    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_num(graphid, &nedge));
    ASSERT_EQUAL_INT(10, nedge);

    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_weight(graphid, &vertices[2], &vertices[0], &weight));
    ASSERT_EQUAL_INT(2, weight);

    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_weight(graphid, &vertices[2], &vertices[1], &weight));
    ASSERT_EQUAL_INT(6, weight);    

    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_weight(graphid, &vertices[2], &vertices[2], &weight));
    ASSERT_EQUAL_INT(M_GRAPH_INVALID_WEIGHT, weight);    

    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_weight(graphid, &vertices[2], &vertices[3], &weight));
    ASSERT_EQUAL_INT(2, weight);      

    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_weight(graphid, &vertices[2], &vertices[4], &weight));
    ASSERT_EQUAL_INT(2, weight);  

    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_weight(graphid, &vertices[2], &vertices[5], &weight));
    ASSERT_EQUAL_INT(4, weight);      

    ASSERT_EQUAL_INT(e_graph_success, rmv_graph_edge(graphid, &vertices[2], &vertices[0]));
    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_weight(graphid, &vertices[2], &vertices[0], &weight));
    ASSERT_EQUAL_INT(M_GRAPH_INVALID_WEIGHT, weight);
    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_weight(graphid, &vertices[0], &vertices[2], &weight));
    ASSERT_EQUAL_INT(M_GRAPH_INVALID_WEIGHT, weight);
    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_num(graphid, &nedge));
    ASSERT_EQUAL_INT(9, nedge);    

    ASSERT_EQUAL_INT(e_graph_success, rmv_graph_vertex(graphid, &vertices[2]));
    ASSERT_EQUAL_INT(e_graph_success, get_graph_vertex_num(graphid, &nvertex));
    ASSERT_EQUAL_INT(sizeof(vertices) / sizeof(vertices[0]) - 1, nvertex);

    ASSERT_EQUAL_INT(e_graph_err_vertex_not_found, get_graph_edge_weight(graphid, &vertices[2], &vertices[0], &weight));

    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_num(graphid, &nedge));
    ASSERT_EQUAL_INT(5, nedge);  

    ASSERT_EQUAL_INT(e_graph_success, update_graph_edge_weight(graphid, &vertices[0], &vertices[1], 100));
    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_weight(graphid, &vertices[0], &vertices[1], &weight));
    ASSERT_EQUAL_INT(100, weight); 
    ASSERT_EQUAL_INT(e_graph_success, get_graph_edge_weight(graphid, &vertices[0], &vertices[1], &weight));
    ASSERT_EQUAL_INT(100, weight); 

    ASSERT_EQUAL_INT(e_graph_success, get_graph_vertex_indegree(graphid, &vertices[0], &indegree));
    ASSERT_EQUAL_INT(2, indegree);

    ASSERT_EQUAL_INT(e_graph_success, get_graph_vertex_outdegree(graphid, &vertices[0], &outdegree));
    ASSERT_EQUAL_INT(2, outdegree);

    ASSERT_EQUAL_INT(e_graph_success, get_graph_vertex_total_degree(graphid, &vertices[0], &totaldegree));
    ASSERT_EQUAL_INT(2, totaldegree);    

    ASSERT_EQUAL_INT(e_graph_success, free_graph(graphid));
}


void graph_test_cases(void)
{
    _graph_test_case01();
}

