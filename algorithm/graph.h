#ifndef _GRAPH_H
#define _GRAPH_H

#include "algorithm_common.h"

#define M_GRAPH_INVALID_WEIGHT -1
#define is_graph_weight_valid(weight) ((weight) != M_GRAPH_INVALID_WEIGHT)

typedef enum
{
	e_graph_success,
	e_graph_err_null_ptr,
	e_graph_err_full,
	e_graph_err_id_not_found,
	e_graph_err_vertex_full,
	e_graph_err_vertex_duplicated,
	e_graph_err_other
}e_graph_err_code;

#ifdef __cplusplus
extern "C" {
#endif

int alloc_graph(IN int bdirected, OUT int *pid);
int free_graph(IN int id);
int add_graph_vertex(IN int graphid, IN const void *pvertex);
int add_graph_edge(IN int         graphid, 
                         IN const void *src_vertex, 
                         IN const void *dst_vertex, 
                         IN int         weight);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _GRAPH_H */

