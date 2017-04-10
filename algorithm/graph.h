#ifndef _GRAPH_H
#define _GRAPH_H

#include "common.h"

#define M_GRAPH_INFINITE_WEIGHT       (0x7FFFFFFF)
#define graph_is_valid_weight(weight) ((weight) >= 0 && (weight) < M_GRAPH_INFINITE_WEIGHT)

typedef enum
{
	e_graph_success,
	e_graph_err_null_ptr,
	e_graph_err_full,
	e_graph_err_id_not_found,
	e_graph_err_vertex_full,
	e_graph_err_vertex_index_invalid,
	e_graph_err_vertex_num_too_few,
	e_graph_err_edge_not_found,
	e_graph_err_edge_duplicated,
	e_graph_err_weight_invalid,
	e_graph_err_other
}e_graph_err_code;

EXTERN int graph_alloc(IN int bdirected, OUT int *graphid);
EXTERN int graph_free(IN int id);
EXTERN int graph_add_vertex(IN int graphid);
EXTERN int graph_rmv_vertex(IN int graphid, IN int vertex_index);
EXTERN int graph_add_edge(IN int      graphid, 
                                IN int      src_vertex_index, 
                                IN int      dst_vertex_index, 
                                IN int      weight);
EXTERN int graph_rmv_edge(IN int         graphid, 
	                            IN int      src_vertex_index, 
                                IN int      dst_vertex_index);
EXTERN int graph_update_edge_weight(IN int         graphid, 
                   	                   IN int      src_vertex_index, 
                   	                   IN int      dst_vertex_index, 
                   	                   IN int         weight);
EXTERN int graph_get_edge_num(IN int graphid, OUT int *nedge);
EXTERN int graph_get_edge_weight(IN  int         graphid, 
                                   IN  int      src_vertex_index, 
                                   IN  int      dst_vertex_index,
                                   OUT int        *weight);
EXTERN int graph_get_vertex_num(IN int graphid, OUT int *nvertex);
EXTERN int graph_get_vertex_indegree(IN  int         graphid, 
                                         IN  int vertex_index,
                                         OUT int        *indegree);
EXTERN int graph_get_vertex_outdegree(IN  int         graphid, 
                                          IN  int  vertex_index,
                                          OUT int        *outdegree);
EXTERN int graph_get_vertex_total_degree(IN  int         graphid, 
                                              IN  int vertex_index,
                                              OUT int        *degree);
int graph_dijkstra(IN int  graphid, 
                         IN  int  vertex_index,
                         OUT int *distances,
                         OUT int *prevs);
int graph_get_shortest_path_len(IN  int  graphid, 
                                            IN  int  src_vertex_index,
                                            IN  int  dst_vertex_index,
                                            OUT int *prevs);

#endif /* _GRAPH_H */

