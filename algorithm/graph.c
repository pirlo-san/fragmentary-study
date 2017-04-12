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

static inline int _graph_is_vertex_index_valid(const graph_t *pgraph, int vertex_index)
{
    if (!pgraph)
        return 0;

	return ((vertex_index >= 0) && (vertex_index < pgraph->nvertex));
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
        {
            if (row == col)
                weight[row][col] = 0;
            else
			    weight[row][col]= M_GRAPH_INFINITE_WEIGHT;
        }
}

static void _graph_dijkstra_init_su(graph_t *pgraph, int vertex_index, int s[], int u[])
{
    int i  = 0;
    int nu = 0;
    
    if (!pgraph)
        return;

    if (!_graph_is_vertex_index_valid(pgraph, vertex_index))
        return;

    if (!s || !u)
        return;

    s[0] = vertex_index;
    for (i = 0; i < pgraph->nvertex; ++i)
    {
        if (i == vertex_index)
            continue;

        u[nu++] = i;
    }
}

static void _graph_dijkstra_init_distances(graph_t *pgraph, int vertex_index, int *distances, int *prevs)
{
    int i  = 0;
    
    if (!pgraph)
        return;

    if (!_graph_is_vertex_index_valid(pgraph, vertex_index))
        return;

    if (!distances || !prevs)
        return;

    for (i = 0; i < pgraph->nvertex; ++i)
    {
        distances[i] = pgraph->weight[vertex_index][i];
        prevs[i]     = vertex_index;
    }
}

static int _graph_dijkstra_get_next_vertex(int u[], int nu, int *distances)
{
    int i            = 0;
    int min_distance = M_GRAPH_INFINITE_WEIGHT;
    int result       = 0;

    for (; i < nu; ++i)
    {
        int v = u[i];

        if (distances[v] < min_distance)
        {
            min_distance = distances[v];
            result       = v;
        }
        
    }
    
    return result;
}

static void _graph_dijkstra_append_s(int s[], int ns, int k)
{
    s[ns] = k;
}

static void _graph_dijkstra_rmv_u(int u[], int nu, int k)
{
    int i = 0;

    for (; i < nu; ++i)
        if (u[i] == k)
            break;
    
    if (i + 1 >= nu)
        return;
    
    memmove(&u[i], &u[i + 1], (nu - 1 - i) * sizeof(int));
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

int graph_add_vertex(int graphid)
{
	graph_t *pgraph = 0;

	if (!(pgraph = _graph_get_instance(graphid)))
		return e_graph_err_id_not_found;

	if (_graph_is_vertex_full(pgraph))
		return e_graph_err_vertex_full;

	++pgraph->nvertex;
	return e_graph_success;
}

int graph_rmv_vertex(int graphid, int vertex_index)
{
    graph_t *pgraph       = 0;
    int      index        = -1;
    int      degree       = 0;
    int      ret          = e_graph_success;

    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if (!_graph_is_vertex_index_valid(pgraph, vertex_index))
        return e_graph_err_vertex_index_invalid;

    if ( (ret = graph_get_vertex_total_degree(graphid, vertex_index, &degree)) != e_graph_success)
        return ret;

    pgraph->nedge -= degree;

    if (vertex_index < pgraph->nvertex - 1)
    {
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
        if (pgraph->nvertex - 1 == index)
        {
            pgraph->weight[pgraph->nvertex - 1][index] = 0;
        }
        else
        {
            pgraph->weight[pgraph->nvertex - 1][index] = M_GRAPH_INFINITE_WEIGHT;
            pgraph->weight[index][pgraph->nvertex - 1] = M_GRAPH_INFINITE_WEIGHT;
        }
    }

    --pgraph->nvertex;
    return e_graph_success;
}

int graph_add_edge(int      graphid, 
	                     int      src_vertex_index, 
	                     int      dst_vertex_index, 
	                     int      weight)
{
    graph_t *pgraph           = 0; 
    int      temp_weight      = M_GRAPH_INFINITE_WEIGHT;
    int      ret              = e_graph_success;

    if (!graph_is_valid_weight(weight))
        return e_graph_err_weight_invalid;

    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if (!_graph_is_vertex_index_valid(pgraph, src_vertex_index)
        || !_graph_is_vertex_index_valid(pgraph, dst_vertex_index))
        return e_graph_err_vertex_index_invalid;

    ret = graph_get_edge_weight(graphid, src_vertex_index, dst_vertex_index, &temp_weight);
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
	                     int         src_vertex_index, 
	                     int         dst_vertex_index)
{
    graph_t *pgraph           = 0; 
    int      temp_weight      = M_GRAPH_INFINITE_WEIGHT;
    int      ret              = e_graph_success;

    if (src_vertex_index == dst_vertex_index)
        return e_graph_success;

    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if (!_graph_is_vertex_index_valid(pgraph, src_vertex_index)
        || !_graph_is_vertex_index_valid(pgraph, dst_vertex_index))
        return e_graph_err_vertex_index_invalid;

    ret = graph_get_edge_weight(graphid, src_vertex_index, dst_vertex_index, &temp_weight);
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

int graph_update_edge_weight(int      graphid, 
               	                       int      src_vertex_index, 
               	                       int      dst_vertex_index, 
               	                       int      weight)
{
    int ret = graph_rmv_edge(graphid, src_vertex_index, dst_vertex_index);

    if (ret != e_graph_success)
        return ret;

    return graph_add_edge(graphid, src_vertex_index, dst_vertex_index, weight);
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

int graph_get_edge_weight(int      graphid, 
                                   int      src_vertex_index, 
                                   int      dst_vertex_index,
                                   int     *weight)
{
    graph_t *pgraph           = 0;

    if (!weight)
        return e_graph_err_null_ptr;

    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if (!_graph_is_vertex_index_valid(pgraph, src_vertex_index)
        || !_graph_is_vertex_index_valid(pgraph, dst_vertex_index))
        return e_graph_err_vertex_index_invalid;

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

int graph_get_vertex_indegree(int  graphid, 
                                         int  vertex_index,
                                         int *indegree)
{
    graph_t *pgraph       = 0;
    int      index        = 0;

    if (!indegree)
        return e_graph_err_null_ptr;
        
    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if (!_graph_is_vertex_index_valid(pgraph, vertex_index))
        return e_graph_err_vertex_index_invalid;

    *indegree = 0;
    for (index = 0; index < pgraph->nvertex; ++index)
        if (index != vertex_index
            && graph_is_valid_weight(pgraph->weight[index][vertex_index]))
            ++(*indegree);

    return e_graph_success; 
}

int graph_get_vertex_outdegree(int  graphid, 
                                          int  vertex_index,
                                          int *outdegree)
{
    graph_t *pgraph       = 0;
    int      index        = 0;

    if (!outdegree)
        return e_graph_err_null_ptr;
        
    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if (!_graph_is_vertex_index_valid(pgraph, vertex_index))
        return e_graph_err_vertex_index_invalid;

    *outdegree = 0;
    for (index = 0; index < pgraph->nvertex; ++index)
        if (index != vertex_index
            && graph_is_valid_weight(pgraph->weight[vertex_index][index]))
            ++(*outdegree);

    return e_graph_success; 

}

int graph_get_vertex_total_degree(int  graphid, 
                                              int  vertex_index,
                                              int *degree)
{
    int indegree  = 0;
    int outdegree = 0;
    int bdirected = 0;
    int ret       = e_graph_success;

    ret = graph_get_vertex_indegree(graphid, vertex_index, &indegree);
    if (ret != e_graph_success)
        return ret;

    if ( (ret = _graph_get_directed(graphid, &bdirected)) != e_graph_success)
        return ret;

    if (!bdirected)
    {
        *degree = indegree;
        return e_graph_success;
    }

    ret = graph_get_vertex_outdegree(graphid, vertex_index, &outdegree);
    if (ret != e_graph_success)
        return ret;

    *degree = indegree + outdegree;
    return e_graph_success;
}

int graph_dijkstra(int  graphid, 
                   int  vertex_index,
                   int *distances,
                   int *prevs)
{
    graph_t *pgraph = 0;
    int      s[M_GRAPH_MAX_VERTEX_NUM] = {0};
    int      u[M_GRAPH_MAX_VERTEX_NUM] = {0}; 
    int      ns = 0;
    int      nu = 0;

    if (!distances || !prevs)
        return e_graph_err_null_ptr;
    
    if (!(pgraph = _graph_get_instance(graphid)))
        return e_graph_err_id_not_found;

    if (!_graph_is_vertex_index_valid(pgraph, vertex_index))    
        return e_graph_err_vertex_index_invalid;

    if (pgraph->nvertex < 2)
        return e_graph_err_vertex_num_too_few;

    _graph_dijkstra_init_su(pgraph, vertex_index, s, u);
    ns = 1;
    nu = pgraph->nvertex - 1;
    
    _graph_dijkstra_init_distances(pgraph, vertex_index, distances, prevs);
    while (nu > 0)
    {
        int k = _graph_dijkstra_get_next_vertex(u, nu, distances);
        int distance_sk = distances[k];
        int index       = 0;

        _graph_dijkstra_append_s(s, ns, k);
        ++ns;

        _graph_dijkstra_rmv_u(u, nu, k);
        --nu;
        for (index = 0; index < nu; ++index)
        {
            int v = u[index];
            int distance_sv = distances[v];
            int distance_kv = pgraph->weight[k][v];

            if (M_GRAPH_INFINITE_WEIGHT == distance_kv)
                continue;
            
            if (distance_sk + distance_kv < distance_sv)
            {
                distances[v] = distance_sk + distance_kv;
                prevs[v]     = k;
            }
        }
    }
    
    return e_graph_success;
}

int graph_get_shortest_path_len(int  graphid, 
                                            int  src_vertex_index,
                                            int  dst_vertex_index,
                                            int *prevs)
{
    graph_t *pgraph                            = 0;
    int      distances[M_GRAPH_MAX_VERTEX_NUM] = {0};
    
    if (!prevs)
        return M_GRAPH_INFINITE_WEIGHT;

    if (!(pgraph = _graph_get_instance(graphid)))
        return M_GRAPH_INFINITE_WEIGHT;    

    if (!_graph_is_vertex_index_valid(pgraph, src_vertex_index)
        || !_graph_is_vertex_index_valid(pgraph, dst_vertex_index))
        return M_GRAPH_INFINITE_WEIGHT;

    if (e_graph_success != graph_dijkstra(graphid, src_vertex_index, distances, prevs))
        return M_GRAPH_INFINITE_WEIGHT;

    return distances[dst_vertex_index];
}

