#include <assert.h>
#include <string.h>
#include "graph.h"

#define M_GRAPH_MAX_GRAPH_NUM  100
#define M_GRAPH_MAX_VERTEX_NUM 100

typedef struct
{
	int         id;
	int         nvertex;
	int         nedge;
	int         bdirected;
	const void *vertices[M_GRAPH_MAX_VERTEX_NUM];
	int         weight[M_GRAPH_MAX_VERTEX_NUM][M_GRAPH_MAX_VERTEX_NUM];
}graph_t;

static graph_t g_graphs[M_GRAPH_MAX_GRAPH_NUM] = {0};
static int     g_graph_num                     = 0;
static int     g_graph_current_id              = 0;

static inline int _graph_get_index(int id)
{
	int index = 0;

	for (; index < g_graph_num; ++index)
	{
		if (id == g_graphs[index].id)
			return index;
	}

	return -1;
}

static inline graph_t *_graph_get_instance(int graphid)
{
	int index = _graph_get_index(graphid);

	if (index < 0)
		return 0;

	return &g_graphs[index];
}

static inline int _graph_get_vertex_index(const graph_t *pgraph, const void *pvertex)
{
	int index = 0;
	
	assert(pgraph);
	assert(pvertex);

	for (; index < pgraph->nvertex; ++index)
		if (pvertex == pgraph->vertices[index])
			return index;

	return -1;
}

static inline int _graph_is_vertex_exist(const graph_t *pgraph, const void *pvertex)
{
	return _graph_get_vertex_index(pgraph, pvertex) >= 0;
}

static inline int _graph_is_vertex_full(const graph_t * pgraph)
{
	assert(pgraph);

	return pgraph->nvertex >= M_GRAPH_MAX_VERTEX_NUM;
}

static inline int _graph_get_directed(int graphid, int *bdirected)
{
    graph_t *pgraph = _graph_get_instance(graphid);

    if (!pgraph)
        return e_graph_err_id_not_found;

    *bdirected = pgraph->bdirected;
    return e_graph_success;
}

static void _graph_init_weight(int weight[M_GRAPH_MAX_VERTEX_NUM][M_GRAPH_MAX_VERTEX_NUM])
{
	int row = 0;
	int col = 0;

	for (row = 0; row < M_GRAPH_MAX_VERTEX_NUM; ++row)
		for (col = 0; col < M_GRAPH_MAX_VERTEX_NUM; ++col)
			weight[row][col]= M_GRAPH_INFINITE_WEIGHT;
}

int graph_alloc(int bdirected, int *graphid)
{
	graph_t *graph = 0;

	if (!graphid)
		return e_graph_err_null_ptr;

	if (g_graph_num >= M_GRAPH_MAX_GRAPH_NUM)
		return e_graph_err_full;

	
	graph = &g_graphs[g_graph_num++];
	bzero(graph, sizeof(*graph));
	graph->id = *graphid = g_graph_current_id++;
	graph->bdirected     = bdirected;
	_graph_init_weight(graph->weight);
	
	return e_graph_success;
}

int graph_free(int id)
{
	int index = _graph_get_index(id);

	if (index < 0)
		return e_graph_err_id_not_found;

	if (index < g_graph_num - 1)
		memmove(&g_graphs[index], 
                &g_graphs[index + 1], 
                sizeof(graph_t) * (g_graph_num - 1 - index));
	--g_graph_num;
	return e_graph_success;
}

int graph_add_vertex(int graphid, const void *pvertex)
{
	graph_t *pgraph = 0;

	if (!pvertex)
		return e_graph_err_null_ptr;

	if (!(pgraph = _graph_get_instance(graphid)))
		return e_graph_err_id_not_found;

	if (_graph_is_vertex_full(pgraph))
		return e_graph_err_vertex_full;

	if (_graph_is_vertex_exist(pgraph, pvertex))
		return e_graph_err_vertex_duplicated;

	pgraph->vertices[pgraph->nvertex++] = pvertex;
	return e_graph_success;
}

int graph_rmv_vertex(int graphid, const void *pvertex)
{
    graph_t *pgraph       = 0;
    int      vertex_index = -1;
    int      index        = -1;
    int      degree       = 0;
    int      ret          = e_graph_success;

    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if ( (vertex_index = _graph_get_vertex_index(pgraph, pvertex)) < 0)
        return e_graph_err_vertex_not_found;

    if ( (ret = graph_get_vertex_total_degree(graphid, pvertex, &degree)) != e_graph_success)
        return ret;

    pgraph->nedge -= degree;

    if (vertex_index < pgraph->nvertex - 1)
    {
        memmove(&pgraph->vertices[vertex_index],
                &pgraph->vertices[vertex_index + 1],
                sizeof(void *) * (pgraph->nvertex - 1 - vertex_index));

        /* delete all edges start from or end to this vertex */
        memmove(pgraph->weight[vertex_index],
                pgraph->weight[vertex_index + 1],
                sizeof(int) * M_GRAPH_MAX_VERTEX_NUM * (M_GRAPH_MAX_VERTEX_NUM - 1 - vertex_index));
        for (index = 0; index < pgraph->nvertex; ++index)
            memmove(&pgraph->weight[index][vertex_index],
                    &pgraph->weight[index][vertex_index + 1],
                    sizeof(int) * (pgraph->nvertex - 1 - vertex_index));
    }

    for (index = 0; index < pgraph->nvertex; ++index)
    {
        pgraph->weight[pgraph->nvertex - 1][index] = M_GRAPH_INFINITE_WEIGHT;
        pgraph->weight[index][pgraph->nvertex - 1] = M_GRAPH_INFINITE_WEIGHT;
    }

    --pgraph->nvertex;
    return e_graph_success;
}

int graph_add_edge(int         graphid, 
	                     const void *src_vertex, 
	                     const void *dst_vertex, 
	                     int         weight)
{
    graph_t *pgraph           = 0;
    int      src_vertex_index = -1;
    int      dst_vertex_index = -1;    
    int      temp_weight      = M_GRAPH_INFINITE_WEIGHT;
    int      ret              = e_graph_success;

    if (!graph_is_valid_weight(weight))
        return e_graph_err_weight_invalid;

    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if ( (src_vertex_index = _graph_get_vertex_index(pgraph, src_vertex)) < 0
        || (dst_vertex_index = _graph_get_vertex_index(pgraph, dst_vertex)) < 0)
        return e_graph_err_vertex_not_found;

    ret = graph_get_edge_weight(graphid, src_vertex, dst_vertex, &temp_weight);
    if (ret != e_graph_success)
        return ret;

    if (graph_is_valid_weight(temp_weight))
        return e_graph_err_edge_duplicated;

    pgraph->weight[src_vertex_index][dst_vertex_index] = weight;
    if (!pgraph->bdirected)
        pgraph->weight[dst_vertex_index][src_vertex_index] = weight;

    ++pgraph->nedge;
    return e_graph_success;    
}

int graph_rmv_edge(int         graphid, 
	                     const void *src_vertex, 
	                     const void *dst_vertex)
{
    graph_t *pgraph           = 0;
    int      src_vertex_index = -1;
    int      dst_vertex_index = -1;    
    int      temp_weight      = M_GRAPH_INFINITE_WEIGHT;
    int      ret              = e_graph_success;

    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if ( (src_vertex_index = _graph_get_vertex_index(pgraph, src_vertex)) < 0
        || (dst_vertex_index = _graph_get_vertex_index(pgraph, dst_vertex)) < 0)
        return e_graph_err_vertex_not_found;

    ret = graph_get_edge_weight(graphid, src_vertex, dst_vertex, &temp_weight);
    if (ret != e_graph_success)
        return ret;

    if (!graph_is_valid_weight(temp_weight))
        return e_graph_err_edge_not_found;

    pgraph->weight[src_vertex_index][dst_vertex_index] = M_GRAPH_INFINITE_WEIGHT;
    if (!pgraph->bdirected)
        pgraph->weight[dst_vertex_index][src_vertex_index] = M_GRAPH_INFINITE_WEIGHT;

    --pgraph->nedge;
    return e_graph_success;  
}

int graph_update_edge_weight(int         graphid, 
                   	                   const void *src_vertex, 
                   	                   const void *dst_vertex, 
                   	                   int         weight)
{
    int ret = graph_rmv_edge(graphid, src_vertex, dst_vertex);

    if (ret != e_graph_success)
        return ret;

    return graph_add_edge(graphid, src_vertex, dst_vertex, weight);
}

int graph_get_edge_num(int graphid, int *nedge)
{
    graph_t *graph = _graph_get_instance(graphid);

    if (!graph)
        return e_graph_err_id_not_found;

    if (!nedge)
        return e_graph_err_null_ptr;

    *nedge = graph->nedge;
    return e_graph_success;
}

int graph_get_edge_weight(int         graphid, 
                                   const void *src_vertex, 
                                   const void *dst_vertex,
                                   int        *weight)
{
    graph_t *pgraph           = 0;
    int      src_vertex_index = -1;
    int      dst_vertex_index = -1;

    if (!weight)
        return e_graph_err_null_ptr;

    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if ( (src_vertex_index = _graph_get_vertex_index(pgraph, src_vertex)) < 0
        || (dst_vertex_index = _graph_get_vertex_index(pgraph, dst_vertex)) < 0)
        return e_graph_err_vertex_not_found;

    *weight = pgraph->weight[src_vertex_index][dst_vertex_index];
    return e_graph_success;
}

int graph_get_vertex_num(int graphid, int *nvertex)
{
    graph_t *graph = _graph_get_instance(graphid);

    if (!graph)
        return e_graph_err_id_not_found;

    if (!nvertex)
        return e_graph_err_null_ptr;

    *nvertex = graph->nvertex;
    return e_graph_success;
}

int graph_get_vertex_indegree(int         graphid, 
                                         const void *pvertex,
                                         int        *indegree)
{
    graph_t *pgraph       = 0;
    int      vertex_index = 0;
    int      index        = 0;

    if (!indegree)
        return e_graph_err_null_ptr;
        
    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if ( (vertex_index = _graph_get_vertex_index(pgraph, pvertex)) < 0)
        return e_graph_err_vertex_not_found;

    *indegree = 0;
    for (index = 0; index < pgraph->nvertex; ++index)
        if (graph_is_valid_weight(pgraph->weight[index][vertex_index]))
            ++(*indegree);

    return e_graph_success; 
}

int graph_get_vertex_outdegree(int         graphid, 
                                          const void *pvertex,
                                          int        *outdegree)
{
    graph_t *pgraph       = 0;
    int      vertex_index = 0;
    int      index        = 0;

    if (!outdegree)
        return e_graph_err_null_ptr;
        
    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if ( (vertex_index = _graph_get_vertex_index(pgraph, pvertex)) < 0)
        return e_graph_err_vertex_not_found;

    *outdegree = 0;
    for (index = 0; index < pgraph->nvertex; ++index)
        if (graph_is_valid_weight(pgraph->weight[vertex_index][index]))
            ++(*outdegree);

    return e_graph_success; 

}

int graph_get_vertex_total_degree(int         graphid, 
                                              const void *pvertex,
                                              int        *degree)
{
    int indegree  = 0;
    int outdegree = 0;
    int bdirected = 0;
    int ret       = e_graph_success;

    ret = graph_get_vertex_indegree(graphid, pvertex, &indegree);
    if (ret != e_graph_success)
        return ret;

    if ( (ret = _graph_get_directed(graphid, &bdirected)) != e_graph_success)
        return ret;

    if (!bdirected)
    {
        *degree = indegree;
        return e_graph_success;
    }

    ret = graph_get_vertex_outdegree(graphid, pvertex, &outdegree);
    if (ret != e_graph_success)
        return ret;

    *degree = indegree + outdegree;
    return e_graph_success;
}

