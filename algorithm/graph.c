#include <assert.h>
#include <string.h>
#include <strings.h>
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

graph_t g_graphs[M_GRAPH_MAX_GRAPH_NUM] = {0};
int     g_graph_num                     = 0;
int     g_graph_current_id              = 0;

static inline int _get_graph_index(int id)
{
	int index = 0;

	for (; index < g_graph_num; ++index)
	{
		if (id == g_graphs[index].id)
			return index;
	}

	return -1;
}

static inline graph_t *_get_graph(int id)
{
	int index = _get_graph_index(id);

	if (index < 0)
		return 0;

	return &g_graphs[index];
}

static inline int _get_graph_vertex_index(const graph_t *pgraph, const void *pvertex)
{
	int index = 0;
	
	assert(!pgraph);
	assert(!pvertex);

	for (; index < pgraph->nvertex; ++index)
		if (pvertex == pgraph->vertices[index])
			return index;

	return -1;
}

static inline int _is_graph_vertex_exist(const graph_t *pgraph, const void *pvertex)
{
	return _get_graph_vertex_index(pgraph, pvertex) >= 0;
}

static inline int _is_graph_vertex_full(const graph_t * pgraph)
{
	assert(pgraph);

	return pgraph->nvertex >= M_GRAPH_MAX_VERTEX_NUM;
}

static void _init_weight(int weight[M_GRAPH_MAX_VERTEX_NUM][M_GRAPH_MAX_VERTEX_NUM])
{
	int row = 0;
	int col = 0;

	for (row = 0; row < M_GRAPH_MAX_VERTEX_NUM; ++row)
		for (col = 0; col < M_GRAPH_MAX_VERTEX_NUM; ++col)
			weight[row][col]= M_GRAPH_INVALID_WEIGHT;
}

int alloc_graph(int bdirected, int *pid)
{
	graph_t *pgraph = 0;

	if (!pid)
		return e_graph_err_null_ptr;

	if (g_graph_num >= M_GRAPH_MAX_GRAPH_NUM)
		return e_graph_err_full;

	
	pgraph = &g_graphs[g_graph_num++];
	bzero(pgraph, sizeof(*pgraph));
	pgraph->id = *pid = g_graph_current_id++;
	pgraph->bdirected = bdirected;
	_init_weight(pgraph->weight);
	
	return e_graph_success;
}

int free_graph(int id)
{
	int index = _get_graph_index(id);

	if (index < 0)
		return e_graph_err_id_not_found;

	if (index < g_graph_num - 1)
		memmove(&g_graphs[index], 
                &g_graphs[index + 1], 
                sizeof(graph_t) * (g_graph_num - 1 - index));
	--g_graph_num;
	return e_graph_success;
}

int add_graph_vertex(int graphid, const void *pvertex)
{
	graph_t *pgraph = 0;

	if (!pvertex)
		return e_graph_err_null_ptr;

	if (!(pgraph = _get_graph(id)))
		return e_graph_err_id_not_found;

	if (_is_graph_vertex_full(pgraph))
		return e_graph_err_vertex_full;

	if (_is_graph_vertex_exist(pgraph, pvertex))
		return e_graph_err_vertex_duplicated;

	pgraph->vertices[pgraph->nvertex++] = pvertex;
	return e_graph_success;
}

int add_graph_edge(int         graphid, 
	                     const void *src_vertex, 
	                     const void *dst_vertex, 
	                     int         weight)
{}

