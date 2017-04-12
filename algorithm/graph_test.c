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
    ASSERT_EQUAL_INT(0, weight);    

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

/* Dijkstra */
static void _graph_test_case02(void)
{
#define vindex(c) ((c) - 'A')
    
    const char  vertices[]   = {'A', 'B', 'C', 'D', 'E', 'F'};
    int         i            = 0;
    int         graphid      = -1;
    int         nvertex      = 0;
    int         nedge        = 0;   
    int         indegree     = 0;
    int         outdegree    = 0;
    int         total_degree = 0;  
    int         weight       = 0;
    int         distances[6] = {0};
    int         prevs[6]     = {0};
    
    ASSERT_EQUAL_INT(e_graph_success, graph_alloc(0, &graphid));

    for (; i < arrsize(vertices); ++i)
        ASSERT_EQUAL_INT(e_graph_success, graph_add_vertex(graphid));

    ASSERT_EQUAL_INT(e_graph_success,             graph_add_edge(graphid, vindex('A'), vindex('B'), 6));
    ASSERT_EQUAL_INT(e_graph_success,             graph_add_edge(graphid, vindex('A'), vindex('C'), 3));

    ASSERT_EQUAL_INT(e_graph_err_edge_duplicated, graph_add_edge(graphid, vindex('B'), vindex('A'), 6));
    ASSERT_EQUAL_INT(e_graph_success,             graph_add_edge(graphid, vindex('B'), vindex('C'), 2));
    ASSERT_EQUAL_INT(e_graph_success,             graph_add_edge(graphid, vindex('B'), vindex('D'), 5));

    ASSERT_EQUAL_INT(e_graph_success,             graph_add_edge(graphid, vindex('C'), vindex('D'), 3));
    ASSERT_EQUAL_INT(e_graph_success,             graph_add_edge(graphid, vindex('C'), vindex('E'), 4));

    ASSERT_EQUAL_INT(e_graph_err_edge_duplicated, graph_add_edge(graphid, vindex('D'), vindex('B'), 5));
    ASSERT_EQUAL_INT(e_graph_success,             graph_add_edge(graphid, vindex('D'), vindex('E'), 2));
    ASSERT_EQUAL_INT(e_graph_success,             graph_add_edge(graphid, vindex('D'), vindex('F'), 3));

    ASSERT_EQUAL_INT(e_graph_err_edge_duplicated, graph_add_edge(graphid, vindex('E'), vindex('C'), 4));
    ASSERT_EQUAL_INT(e_graph_success,             graph_add_edge(graphid, vindex('E'), vindex('F'), 5));

    ASSERT_EQUAL_INT(e_graph_success, graph_get_vertex_num(graphid, &nvertex));
    ASSERT_EQUAL_INT(nvertex, arrsize(vertices));

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_num(graphid, &nedge));
    ASSERT_EQUAL_INT(9, nedge);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_vertex_indegree(graphid,     vindex('A'), &indegree));
    ASSERT_EQUAL_INT(e_graph_success, graph_get_vertex_outdegree(graphid,    vindex('B'), &outdegree));    
    ASSERT_EQUAL_INT(e_graph_success, graph_get_vertex_total_degree(graphid, vindex('C'), &total_degree));

    ASSERT_EQUAL_INT(2, indegree);
    ASSERT_EQUAL_INT(3, outdegree);
    ASSERT_EQUAL_INT(4, total_degree);   

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, vindex('D'), vindex('E'), &weight));
    ASSERT_EQUAL_INT(2, weight);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, vindex('E'), vindex('D'), &weight));
    ASSERT_EQUAL_INT(2, weight);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, vindex('E'), vindex('F'), &weight));
    ASSERT_EQUAL_INT(5, weight);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, vindex('F'), vindex('E'), &weight));
    ASSERT_EQUAL_INT(5, weight);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, vindex('B'), vindex('E'), &weight));
    ASSERT_EQUAL_INT(M_GRAPH_INFINITE_WEIGHT, weight);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, vindex('A'), vindex('F'), &weight));
    ASSERT_EQUAL_INT(M_GRAPH_INFINITE_WEIGHT, weight);

    ASSERT_EQUAL_INT(e_graph_success, graph_get_edge_weight(graphid, vindex('A'), vindex('A'), &weight));
    ASSERT_EQUAL_INT(0, weight);
    
    ASSERT_EQUAL_INT(e_graph_success, graph_dijkstra(graphid, vindex('A'), distances, prevs));
    ASSERT_EQUAL_INT(0, distances[vindex('A')]);
    ASSERT_EQUAL_INT(5, distances[vindex('B')]);
    ASSERT_EQUAL_INT(3, distances[vindex('C')]);
    ASSERT_EQUAL_INT(6, distances[vindex('D')]);
    ASSERT_EQUAL_INT(7, distances[vindex('E')]);
    ASSERT_EQUAL_INT(9, distances[vindex('F')]);

    ASSERT_EQUAL_INT(vindex('A'), prevs[vindex('A')]);
    ASSERT_EQUAL_INT(vindex('C'), prevs[vindex('B')]);
    ASSERT_EQUAL_INT(vindex('A'), prevs[vindex('C')]);
    ASSERT_EQUAL_INT(vindex('C'), prevs[vindex('D')]);
    ASSERT_EQUAL_INT(vindex('C'), prevs[vindex('E')]);
    ASSERT_EQUAL_INT(vindex('D'), prevs[vindex('F')]);

    ASSERT_EQUAL_INT(0, graph_get_shortest_path_len(graphid, vindex('A'), vindex('A'), prevs));
    ASSERT_EQUAL_INT(5, graph_get_shortest_path_len(graphid, vindex('A'), vindex('B'), prevs));
    ASSERT_EQUAL_INT(3, graph_get_shortest_path_len(graphid, vindex('A'), vindex('C'), prevs));
    ASSERT_EQUAL_INT(6, graph_get_shortest_path_len(graphid, vindex('A'), vindex('D'), prevs));
    ASSERT_EQUAL_INT(7, graph_get_shortest_path_len(graphid, vindex('A'), vindex('E'), prevs));
    ASSERT_EQUAL_INT(9, graph_get_shortest_path_len(graphid, vindex('A'), vindex('F'), prevs));

    ASSERT_EQUAL_INT(5, graph_get_shortest_path_len(graphid, vindex('B'), vindex('A'), prevs));
    ASSERT_EQUAL_INT(0, graph_get_shortest_path_len(graphid, vindex('B'), vindex('B'), prevs));
    ASSERT_EQUAL_INT(2, graph_get_shortest_path_len(graphid, vindex('B'), vindex('C'), prevs));
    ASSERT_EQUAL_INT(5, graph_get_shortest_path_len(graphid, vindex('B'), vindex('D'), prevs));
    ASSERT_EQUAL_INT(6, graph_get_shortest_path_len(graphid, vindex('B'), vindex('E'), prevs));
    ASSERT_EQUAL_INT(8, graph_get_shortest_path_len(graphid, vindex('B'), vindex('F'), prevs));

    ASSERT_EQUAL_INT(3, graph_get_shortest_path_len(graphid, vindex('C'), vindex('A'), prevs));
    ASSERT_EQUAL_INT(2, graph_get_shortest_path_len(graphid, vindex('C'), vindex('B'), prevs));
    ASSERT_EQUAL_INT(0, graph_get_shortest_path_len(graphid, vindex('C'), vindex('C'), prevs));
    ASSERT_EQUAL_INT(3, graph_get_shortest_path_len(graphid, vindex('C'), vindex('D'), prevs));
    ASSERT_EQUAL_INT(4, graph_get_shortest_path_len(graphid, vindex('C'), vindex('E'), prevs));
    ASSERT_EQUAL_INT(6, graph_get_shortest_path_len(graphid, vindex('C'), vindex('F'), prevs));

    ASSERT_EQUAL_INT(6, graph_get_shortest_path_len(graphid, vindex('D'), vindex('A'), prevs));
    ASSERT_EQUAL_INT(5, graph_get_shortest_path_len(graphid, vindex('D'), vindex('B'), prevs));
    ASSERT_EQUAL_INT(3, graph_get_shortest_path_len(graphid, vindex('D'), vindex('C'), prevs));
    ASSERT_EQUAL_INT(0, graph_get_shortest_path_len(graphid, vindex('D'), vindex('D'), prevs));
    ASSERT_EQUAL_INT(2, graph_get_shortest_path_len(graphid, vindex('D'), vindex('E'), prevs));
    ASSERT_EQUAL_INT(3, graph_get_shortest_path_len(graphid, vindex('D'), vindex('F'), prevs));

    ASSERT_EQUAL_INT(7, graph_get_shortest_path_len(graphid, vindex('E'), vindex('A'), prevs));
    ASSERT_EQUAL_INT(6, graph_get_shortest_path_len(graphid, vindex('E'), vindex('B'), prevs));
    ASSERT_EQUAL_INT(4, graph_get_shortest_path_len(graphid, vindex('E'), vindex('C'), prevs));
    ASSERT_EQUAL_INT(2, graph_get_shortest_path_len(graphid, vindex('E'), vindex('D'), prevs));
    ASSERT_EQUAL_INT(0, graph_get_shortest_path_len(graphid, vindex('E'), vindex('E'), prevs));
    ASSERT_EQUAL_INT(5, graph_get_shortest_path_len(graphid, vindex('E'), vindex('F'), prevs));

    ASSERT_EQUAL_INT(9, graph_get_shortest_path_len(graphid, vindex('F'), vindex('A'), prevs));
    ASSERT_EQUAL_INT(8, graph_get_shortest_path_len(graphid, vindex('F'), vindex('B'), prevs));
    ASSERT_EQUAL_INT(6, graph_get_shortest_path_len(graphid, vindex('F'), vindex('C'), prevs));
    ASSERT_EQUAL_INT(3, graph_get_shortest_path_len(graphid, vindex('F'), vindex('D'), prevs));
    ASSERT_EQUAL_INT(5, graph_get_shortest_path_len(graphid, vindex('F'), vindex('E'), prevs));
    ASSERT_EQUAL_INT(0, graph_get_shortest_path_len(graphid, vindex('F'), vindex('F'), prevs));  

    ASSERT_EQUAL_INT(e_graph_success, graph_free(graphid));
}

static void _graph_test_cases(void)
{
    _graph_test_case01();
    _graph_test_case02();
}

int main(int argc, char *argv[])
{

    fprintf(stderr, "graph test begin\n");
    _graph_test_cases();
    fprintf(stderr, "graph test end\n\n");

    return 0;    
}

