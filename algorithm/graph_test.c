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
    
    ASSERT_INT_EQUAL(e_graph_success, graph_alloc(0, &graphid));

    for (i = 0; i < sizeof(vertices) / sizeof(vertices[0]); ++i)
        ASSERT_INT_EQUAL(e_graph_success, graph_add_vertex(graphid));

    ASSERT_INT_EQUAL(e_graph_success, graph_get_vertex_num(graphid, &nvertex));
    ASSERT_INT_EQUAL(sizeof(vertices) / sizeof(vertices[0]), nvertex);

    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid, 0, 1, 6));
    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid, 0, 2, 2));
    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid, 0, 3, 1));
    
    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid, 1, 2, 6));
    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid, 1, 4, 3));

    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid, 2, 3, 2));
    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid, 2, 4, 2));    
    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid, 2, 5, 4));

    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid, 3, 5, 5));
    
    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid, 4, 5, 3));

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_num(graphid, &nedge));
    ASSERT_INT_EQUAL(10, nedge);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, 2, 0, &weight));
    ASSERT_INT_EQUAL(2, weight);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, 2, 1, &weight));
    ASSERT_INT_EQUAL(6, weight);    

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, 2, 2, &weight));
    ASSERT_INT_EQUAL(0, weight);    

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, 2, 3, &weight));
    ASSERT_INT_EQUAL(2, weight);      

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, 2, 4, &weight));
    ASSERT_INT_EQUAL(2, weight);  

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, 2, 5, &weight));
    ASSERT_INT_EQUAL(4, weight);      

    ASSERT_INT_EQUAL(e_graph_success, graph_rmv_edge(graphid, 2, 0));
    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, 2, 0, &weight));
    ASSERT_INT_EQUAL(M_GRAPH_INFINITE_WEIGHT, weight);
    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, 0, 2, &weight));
    ASSERT_INT_EQUAL(M_GRAPH_INFINITE_WEIGHT, weight);
    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_num(graphid, &nedge));
    ASSERT_INT_EQUAL(9, nedge);    

    ASSERT_INT_EQUAL(e_graph_success, graph_rmv_vertex(graphid, 2));
    ASSERT_INT_EQUAL(e_graph_success, graph_get_vertex_num(graphid, &nvertex));
    ASSERT_INT_EQUAL(sizeof(vertices) / sizeof(vertices[0]) - 1, nvertex);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_num(graphid, &nedge));
    ASSERT_INT_EQUAL(5, nedge);  

    ASSERT_INT_EQUAL(e_graph_success, graph_update_edge_weight(graphid, 0, 1, 100));
    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, 0, 1, &weight));
    ASSERT_INT_EQUAL(100, weight); 
    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, 1, 0, &weight));
    ASSERT_INT_EQUAL(100, weight); 

    ASSERT_INT_EQUAL(e_graph_success, graph_get_vertex_indegree(graphid, 0, &indegree));
    ASSERT_INT_EQUAL(2, indegree);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_vertex_outdegree(graphid, 0, &outdegree));
    ASSERT_INT_EQUAL(2, outdegree);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_vertex_total_degree(graphid, 0, &totaldegree));
    ASSERT_INT_EQUAL(2, totaldegree);    

    ASSERT_INT_EQUAL(e_graph_success, graph_free(graphid));
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
    
    ASSERT_INT_EQUAL(e_graph_success, graph_alloc(0, &graphid));

    for (; i < arrsize(vertices); ++i)
        ASSERT_INT_EQUAL(e_graph_success, graph_add_vertex(graphid));

    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid, vindex('A'), vindex('B'), 6));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid, vindex('A'), vindex('C'), 3));

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid, vindex('B'), vindex('A'), 6));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid, vindex('B'), vindex('C'), 2));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid, vindex('B'), vindex('D'), 5));

    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid, vindex('C'), vindex('D'), 3));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid, vindex('C'), vindex('E'), 4));

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid, vindex('D'), vindex('B'), 5));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid, vindex('D'), vindex('E'), 2));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid, vindex('D'), vindex('F'), 3));

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid, vindex('E'), vindex('C'), 4));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid, vindex('E'), vindex('F'), 5));

    ASSERT_INT_EQUAL(e_graph_success, graph_get_vertex_num(graphid, &nvertex));
    ASSERT_INT_EQUAL(nvertex, arrsize(vertices));

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_num(graphid, &nedge));
    ASSERT_INT_EQUAL(9, nedge);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_vertex_indegree(graphid,     vindex('A'), &indegree));
    ASSERT_INT_EQUAL(e_graph_success, graph_get_vertex_outdegree(graphid,    vindex('B'), &outdegree));    
    ASSERT_INT_EQUAL(e_graph_success, graph_get_vertex_total_degree(graphid, vindex('C'), &total_degree));

    ASSERT_INT_EQUAL(2, indegree);
    ASSERT_INT_EQUAL(3, outdegree);
    ASSERT_INT_EQUAL(4, total_degree);   

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, vindex('D'), vindex('E'), &weight));
    ASSERT_INT_EQUAL(2, weight);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, vindex('E'), vindex('D'), &weight));
    ASSERT_INT_EQUAL(2, weight);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, vindex('E'), vindex('F'), &weight));
    ASSERT_INT_EQUAL(5, weight);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, vindex('F'), vindex('E'), &weight));
    ASSERT_INT_EQUAL(5, weight);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, vindex('B'), vindex('E'), &weight));
    ASSERT_INT_EQUAL(M_GRAPH_INFINITE_WEIGHT, weight);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, vindex('A'), vindex('F'), &weight));
    ASSERT_INT_EQUAL(M_GRAPH_INFINITE_WEIGHT, weight);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid, vindex('A'), vindex('A'), &weight));
    ASSERT_INT_EQUAL(0, weight);
    
    ASSERT_INT_EQUAL(e_graph_success, graph_dijkstra(graphid, vindex('A'), distances, prevs));
    ASSERT_INT_EQUAL(0, distances[vindex('A')]);
    ASSERT_INT_EQUAL(5, distances[vindex('B')]);
    ASSERT_INT_EQUAL(3, distances[vindex('C')]);
    ASSERT_INT_EQUAL(6, distances[vindex('D')]);
    ASSERT_INT_EQUAL(7, distances[vindex('E')]);
    ASSERT_INT_EQUAL(9, distances[vindex('F')]);

    ASSERT_INT_EQUAL(vindex('A'), prevs[vindex('A')]);
    ASSERT_INT_EQUAL(vindex('C'), prevs[vindex('B')]);
    ASSERT_INT_EQUAL(vindex('A'), prevs[vindex('C')]);
    ASSERT_INT_EQUAL(vindex('C'), prevs[vindex('D')]);
    ASSERT_INT_EQUAL(vindex('C'), prevs[vindex('E')]);
    ASSERT_INT_EQUAL(vindex('D'), prevs[vindex('F')]);

    ASSERT_INT_EQUAL(0, graph_get_shortest_path_len(graphid, vindex('A'), vindex('A'), prevs));
    ASSERT_INT_EQUAL(5, graph_get_shortest_path_len(graphid, vindex('A'), vindex('B'), prevs));
    ASSERT_INT_EQUAL(3, graph_get_shortest_path_len(graphid, vindex('A'), vindex('C'), prevs));
    ASSERT_INT_EQUAL(6, graph_get_shortest_path_len(graphid, vindex('A'), vindex('D'), prevs));
    ASSERT_INT_EQUAL(7, graph_get_shortest_path_len(graphid, vindex('A'), vindex('E'), prevs));
    ASSERT_INT_EQUAL(9, graph_get_shortest_path_len(graphid, vindex('A'), vindex('F'), prevs));

    ASSERT_INT_EQUAL(5, graph_get_shortest_path_len(graphid, vindex('B'), vindex('A'), prevs));
    ASSERT_INT_EQUAL(0, graph_get_shortest_path_len(graphid, vindex('B'), vindex('B'), prevs));
    ASSERT_INT_EQUAL(2, graph_get_shortest_path_len(graphid, vindex('B'), vindex('C'), prevs));
    ASSERT_INT_EQUAL(5, graph_get_shortest_path_len(graphid, vindex('B'), vindex('D'), prevs));
    ASSERT_INT_EQUAL(6, graph_get_shortest_path_len(graphid, vindex('B'), vindex('E'), prevs));
    ASSERT_INT_EQUAL(8, graph_get_shortest_path_len(graphid, vindex('B'), vindex('F'), prevs));

    ASSERT_INT_EQUAL(3, graph_get_shortest_path_len(graphid, vindex('C'), vindex('A'), prevs));
    ASSERT_INT_EQUAL(2, graph_get_shortest_path_len(graphid, vindex('C'), vindex('B'), prevs));
    ASSERT_INT_EQUAL(0, graph_get_shortest_path_len(graphid, vindex('C'), vindex('C'), prevs));
    ASSERT_INT_EQUAL(3, graph_get_shortest_path_len(graphid, vindex('C'), vindex('D'), prevs));
    ASSERT_INT_EQUAL(4, graph_get_shortest_path_len(graphid, vindex('C'), vindex('E'), prevs));
    ASSERT_INT_EQUAL(6, graph_get_shortest_path_len(graphid, vindex('C'), vindex('F'), prevs));

    ASSERT_INT_EQUAL(6, graph_get_shortest_path_len(graphid, vindex('D'), vindex('A'), prevs));
    ASSERT_INT_EQUAL(5, graph_get_shortest_path_len(graphid, vindex('D'), vindex('B'), prevs));
    ASSERT_INT_EQUAL(3, graph_get_shortest_path_len(graphid, vindex('D'), vindex('C'), prevs));
    ASSERT_INT_EQUAL(0, graph_get_shortest_path_len(graphid, vindex('D'), vindex('D'), prevs));
    ASSERT_INT_EQUAL(2, graph_get_shortest_path_len(graphid, vindex('D'), vindex('E'), prevs));
    ASSERT_INT_EQUAL(3, graph_get_shortest_path_len(graphid, vindex('D'), vindex('F'), prevs));

    ASSERT_INT_EQUAL(7, graph_get_shortest_path_len(graphid, vindex('E'), vindex('A'), prevs));
    ASSERT_INT_EQUAL(6, graph_get_shortest_path_len(graphid, vindex('E'), vindex('B'), prevs));
    ASSERT_INT_EQUAL(4, graph_get_shortest_path_len(graphid, vindex('E'), vindex('C'), prevs));
    ASSERT_INT_EQUAL(2, graph_get_shortest_path_len(graphid, vindex('E'), vindex('D'), prevs));
    ASSERT_INT_EQUAL(0, graph_get_shortest_path_len(graphid, vindex('E'), vindex('E'), prevs));
    ASSERT_INT_EQUAL(5, graph_get_shortest_path_len(graphid, vindex('E'), vindex('F'), prevs));

    ASSERT_INT_EQUAL(9, graph_get_shortest_path_len(graphid, vindex('F'), vindex('A'), prevs));
    ASSERT_INT_EQUAL(8, graph_get_shortest_path_len(graphid, vindex('F'), vindex('B'), prevs));
    ASSERT_INT_EQUAL(6, graph_get_shortest_path_len(graphid, vindex('F'), vindex('C'), prevs));
    ASSERT_INT_EQUAL(3, graph_get_shortest_path_len(graphid, vindex('F'), vindex('D'), prevs));
    ASSERT_INT_EQUAL(5, graph_get_shortest_path_len(graphid, vindex('F'), vindex('E'), prevs));
    ASSERT_INT_EQUAL(0, graph_get_shortest_path_len(graphid, vindex('F'), vindex('F'), prevs));  

    ASSERT_INT_EQUAL(e_graph_success, graph_free(graphid));
}

/* Dijkstra, 2 graphs */
static void _graph_test_case03(void)
{
#define vindex1(c) ((c) - 'A')
#define vindex2(v) ((v) - 1)


    int        graphid1      = -1;
    int        graphid2      = -1;
    const char vertices1[]   = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int        vertices2[]   = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int        nvertex       = 0;
    int        nedge         = 0;   
    int        indegree      = 0;
    int        outdegree     = 0;
    int        total_degree1 = 0;  
    int        weight        = 0;
    int        distances[10] = {0};
    int        prevs[10]     = {0};    
    int        i             = 0;    

    ASSERT_INT_EQUAL(e_graph_success, graph_alloc(0, &graphid1));
    ASSERT_INT_EQUAL(e_graph_success, graph_alloc(0, &graphid2));

    for (i = 0; i < arrsize(vertices1); ++i)
        ASSERT_INT_EQUAL(e_graph_success, graph_add_vertex(graphid1));

    for (i = 0; i < arrsize(vertices2); ++i)
        ASSERT_INT_EQUAL(e_graph_success, graph_add_vertex(graphid2));    

    ASSERT_INT_EQUAL(e_graph_success, graph_get_vertex_num(graphid1, &nvertex));
    ASSERT_INT_EQUAL(arrsize(vertices1), nvertex);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_vertex_num(graphid2, &nvertex));
    ASSERT_INT_EQUAL(arrsize(vertices2), nvertex);    

    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid1, vindex1('A'), vindex1('B'), 96));
    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid1, vindex1('A'), vindex1('C'), 88));
    ASSERT_INT_EQUAL(e_graph_success, graph_add_edge(graphid1, vindex1('A'), vindex1('D'), 268));

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('B'), vindex1('A'), 2));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('B'), vindex1('C'), 66));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('B'), vindex1('E'), 88));

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('C'), vindex1('A'), 88));
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('C'), vindex1('C'), 88));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('C'), vindex1('D'), 150));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('C'), vindex1('F'), 90));

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('D'), vindex1('A'), 88));
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('D'), vindex1('C'), 88));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('D'), vindex1('F'), 30));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('D'), vindex1('G'), 80));    

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('E'), vindex1('B'), 2));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('E'), vindex1('F'), 60));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('E'), vindex1('I'), 80));  

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('F'), vindex1('C'), 88));  
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('F'), vindex1('D'), 88));  
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('F'), vindex1('E'), 88));  
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('F'), vindex1('G'), 130));  
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('F'), vindex1('H'), 65));  

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('G'), vindex1('D'), 88));
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('G'), vindex1('F'), 88));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('G'), vindex1('H'), 50));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('G'), vindex1('J'), 150));       

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('H'), vindex1('F'), 88));
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('H'), vindex1('G'), 88));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('H'), vindex1('I'), 120));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('H'), vindex1('J'), 80)); 

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('I'), vindex1('E'), 2));
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('I'), vindex1('H'), 60));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid1, vindex1('I'), vindex1('J'), 120));  

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('J'), vindex1('G'), 2));
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('J'), vindex1('H'), 60));
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid1, vindex1('J'), vindex1('I'), 88));      



    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid2, vindex2(1), vindex2(2), 6));      
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid2, vindex2(1), vindex2(3), 4));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid2, vindex2(1), vindex2(4), 5));
    
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid2, vindex2(2), vindex2(1), 1));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid2, vindex2(2), vindex2(5), 1));
    
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid2, vindex2(3), vindex2(1), 1));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid2, vindex2(3), vindex2(5), 1));

    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid2, vindex2(4), vindex2(1), 1));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid2, vindex2(4), vindex2(6), 2));
    
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid2, vindex2(5), vindex2(2), 1));
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid2, vindex2(5), vindex2(3), 1));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid2, vindex2(5), vindex2(7), 9));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid2, vindex2(5), vindex2(8), 7));
    
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid2, vindex2(6), vindex2(4), 1));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid2, vindex2(6), vindex2(8), 4));
    
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid2, vindex2(7), vindex2(5), 1));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid2, vindex2(7), vindex2(9), 2));
    
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid2, vindex2(8), vindex2(5), 1));
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid2, vindex2(8), vindex2(6), 1));
    ASSERT_INT_EQUAL(e_graph_success,             graph_add_edge(graphid2, vindex2(8), vindex2(9), 4));
    
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid2, vindex2(9), vindex2(7), 1));
    ASSERT_INT_EQUAL(e_graph_err_edge_duplicated, graph_add_edge(graphid2, vindex2(9), vindex2(8), 1));

        
    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_num(graphid1, &nedge));
    ASSERT_INT_EQUAL(18, nedge);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_num(graphid2, &nedge));
    ASSERT_INT_EQUAL(11, nedge);    

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid1, vindex1('C'), vindex1('F'), &weight));
    ASSERT_INT_EQUAL(90, weight);

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid1, vindex1('F'), vindex1('C'), &weight));
    ASSERT_INT_EQUAL(90, weight);    

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid1, vindex1('H'), vindex1('G'), &weight));
    ASSERT_INT_EQUAL(50, weight); 

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid1, vindex1('G'), vindex1('H'), &weight));
    ASSERT_INT_EQUAL(50, weight);    

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid1, vindex1('A'), vindex1('G'), &weight));
    ASSERT_INT_EQUAL(M_GRAPH_INFINITE_WEIGHT, weight); 

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid1, vindex1('G'), vindex1('A'), &weight));
    ASSERT_INT_EQUAL(M_GRAPH_INFINITE_WEIGHT, weight);   


    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid2, vindex2(1), vindex2(2), &weight));
    ASSERT_INT_EQUAL(6, weight); 

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid2, vindex2(2), vindex2(1), &weight));
    ASSERT_INT_EQUAL(6, weight);   

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid2, vindex2(8), vindex2(9), &weight));
    ASSERT_INT_EQUAL(4, weight); 

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid2, vindex2(9), vindex2(8), &weight));
    ASSERT_INT_EQUAL(4, weight);    

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid2, vindex2(1), vindex2(9), &weight));
    ASSERT_INT_EQUAL(M_GRAPH_INFINITE_WEIGHT, weight); 

    ASSERT_INT_EQUAL(e_graph_success, graph_get_edge_weight(graphid2, vindex2(9), vindex2(1), &weight));
    ASSERT_INT_EQUAL(M_GRAPH_INFINITE_WEIGHT, weight);     

    ASSERT_INT_EQUAL(e_graph_success, graph_dijkstra(graphid1, vindex1('A'), distances, prevs));
    ASSERT_INT_EQUAL(0,  distances[vindex1('A')]);
    ASSERT_INT_EQUAL(96, distances[vindex1('B')]);
    ASSERT_INT_EQUAL(88, distances[vindex1('C')]);
    ASSERT_INT_EQUAL(208, distances[vindex1('D')]);
    ASSERT_INT_EQUAL(184, distances[vindex1('E')]);
    ASSERT_INT_EQUAL(178, distances[vindex1('F')]);
    ASSERT_INT_EQUAL(288, distances[vindex1('G')]);
    ASSERT_INT_EQUAL(243, distances[vindex1('H')]);
    ASSERT_INT_EQUAL(264, distances[vindex1('I')]);
    ASSERT_INT_EQUAL(323, distances[vindex1('J')]);

    ASSERT_INT_EQUAL(vindex1('A'), prevs[vindex1('A')]);
    ASSERT_INT_EQUAL(vindex1('A'), prevs[vindex1('B')]);
    ASSERT_INT_EQUAL(vindex1('A'), prevs[vindex1('C')]);
    ASSERT_INT_EQUAL(vindex1('F'), prevs[vindex1('D')]);
    ASSERT_INT_EQUAL(vindex1('B'), prevs[vindex1('E')]);
    ASSERT_INT_EQUAL(vindex1('C'), prevs[vindex1('F')]);
    ASSERT_INT_EQUAL(vindex1('D'), prevs[vindex1('G')]);
    ASSERT_INT_EQUAL(vindex1('F'), prevs[vindex1('H')]);
    ASSERT_INT_EQUAL(vindex1('E'), prevs[vindex1('I')]);
    ASSERT_INT_EQUAL(vindex1('H'), prevs[vindex1('J')]);

    ASSERT_INT_EQUAL(e_graph_success, graph_dijkstra(graphid1, vindex1('F'), distances, prevs));
    ASSERT_INT_EQUAL(178,  distances[vindex1('A')]);
    ASSERT_INT_EQUAL(148, distances[vindex1('B')]);
    ASSERT_INT_EQUAL(90, distances[vindex1('C')]);
    ASSERT_INT_EQUAL(30, distances[vindex1('D')]);
    ASSERT_INT_EQUAL(60, distances[vindex1('E')]);
    ASSERT_INT_EQUAL(0, distances[vindex1('F')]);
    ASSERT_INT_EQUAL(110, distances[vindex1('G')]);
    ASSERT_INT_EQUAL(65, distances[vindex1('H')]);
    ASSERT_INT_EQUAL(140, distances[vindex1('I')]);
    ASSERT_INT_EQUAL(145, distances[vindex1('J')]);

    ASSERT_INT_EQUAL(vindex1('C'), prevs[vindex1('A')]);
    ASSERT_INT_EQUAL(vindex1('E'), prevs[vindex1('B')]);
    ASSERT_INT_EQUAL(vindex1('F'), prevs[vindex1('C')]);
    ASSERT_INT_EQUAL(vindex1('F'), prevs[vindex1('D')]);
    ASSERT_INT_EQUAL(vindex1('F'), prevs[vindex1('E')]);
    ASSERT_INT_EQUAL(vindex1('F'), prevs[vindex1('F')]);
    ASSERT_INT_EQUAL(vindex1('D'), prevs[vindex1('G')]);
    ASSERT_INT_EQUAL(vindex1('F'), prevs[vindex1('H')]);
    ASSERT_INT_EQUAL(vindex1('E'), prevs[vindex1('I')]);
    ASSERT_INT_EQUAL(vindex1('H'), prevs[vindex1('J')]);    

    ASSERT_INT_EQUAL(e_graph_success, graph_dijkstra(graphid2, vindex2(9), distances, prevs));
    ASSERT_INT_EQUAL(15,  distances[vindex2(1)]);
    ASSERT_INT_EQUAL(12, distances[vindex2(2)]);
    ASSERT_INT_EQUAL(12, distances[vindex2(3)]);
    ASSERT_INT_EQUAL(10, distances[vindex2(4)]);
    ASSERT_INT_EQUAL(11, distances[vindex2(5)]);
    ASSERT_INT_EQUAL(8, distances[vindex2(6)]);
    ASSERT_INT_EQUAL(2, distances[vindex2(7)]);
    ASSERT_INT_EQUAL(4, distances[vindex2(8)]);
    ASSERT_INT_EQUAL(0, distances[vindex2(9)]);

    ASSERT_INT_EQUAL(vindex2(4), prevs[vindex2(1)]);
    ASSERT_INT_EQUAL(vindex2(5), prevs[vindex2(2)]);
    ASSERT_INT_EQUAL(vindex2(5), prevs[vindex2(3)]);
    ASSERT_INT_EQUAL(vindex2(6), prevs[vindex2(4)]);
    ASSERT_INT_EQUAL(vindex2(7), prevs[vindex2(5)]);
    ASSERT_INT_EQUAL(vindex2(8), prevs[vindex2(6)]);
    ASSERT_INT_EQUAL(vindex2(9), prevs[vindex2(7)]);
    ASSERT_INT_EQUAL(vindex2(9), prevs[vindex2(8)]);
    ASSERT_INT_EQUAL(vindex2(9), prevs[vindex2(9)]); 

    ASSERT_INT_EQUAL(e_graph_success, graph_dijkstra(graphid2, vindex2(3), distances, prevs));
    ASSERT_INT_EQUAL(4,  distances[vindex2(1)]);
    ASSERT_INT_EQUAL(2, distances[vindex2(2)]);
    ASSERT_INT_EQUAL(0, distances[vindex2(3)]);
    ASSERT_INT_EQUAL(9, distances[vindex2(4)]);
    ASSERT_INT_EQUAL(1, distances[vindex2(5)]);
    ASSERT_INT_EQUAL(11, distances[vindex2(6)]);
    ASSERT_INT_EQUAL(10, distances[vindex2(7)]);
    ASSERT_INT_EQUAL(8, distances[vindex2(8)]);
    ASSERT_INT_EQUAL(12, distances[vindex2(9)]);

    ASSERT_INT_EQUAL(vindex2(3), prevs[vindex2(1)]);
    ASSERT_INT_EQUAL(vindex2(5), prevs[vindex2(2)]);
    ASSERT_INT_EQUAL(vindex2(3), prevs[vindex2(3)]);
    ASSERT_INT_EQUAL(vindex2(1), prevs[vindex2(4)]);
    ASSERT_INT_EQUAL(vindex2(3), prevs[vindex2(5)]);
    ASSERT_INT_EQUAL(vindex2(4), prevs[vindex2(6)]);
    ASSERT_INT_EQUAL(vindex2(5), prevs[vindex2(7)]);
    ASSERT_INT_EQUAL(vindex2(5), prevs[vindex2(8)]);
    ASSERT_INT_EQUAL(vindex2(8), prevs[vindex2(9)]);     

    ASSERT_INT_EQUAL(e_graph_success, graph_free(graphid1));
    ASSERT_INT_EQUAL(e_graph_success, graph_free(graphid2));
}

static void _graph_test_cases(void)
{
    _graph_test_case01();
    _graph_test_case02();
    _graph_test_case03();
}

int main(int argc, char *argv[])
{

    fprintf(stderr, "graph test begin\n");
    _graph_test_cases();
    fprintf(stderr, "graph test end\n\n");

    return 0;    
}

