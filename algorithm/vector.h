#ifndef _VECTOR_H
#define _VECTOR_H

typedef enum
{
    e_vector_success,
    e_vector_err_null_ptr,
    e_vector_err_full,
    e_vector_err_id_not_found,
    e_vector_err_element_full,
    e_vector_err_element_empty,
    e_vector_err_index_invalid,
    e_vector_err_other
}e_vector_err_code;

typedef int  (*compare_func_t)(const void *e1, const void *e2);
typedef void (*traverse_func_t)(const void *e);

#ifdef __cplusplus
extern "C" {
#endif

int vector_alloc(compare_func_t compare_func, int *vid);
int vector_free(int vid);
int vector_push_back(int vid, const void *e);
int vector_pop_back(int vid);
int vector_size(int vid);
int vector_insert(int vid, int index, const void *e);
int vector_erase(int vid, int index);
int vector_sort(int vid, compare_func_t compare_func);
int vector_traverse(int vid, traverse_func_t traverse_func);
int vector_reverse(int vid);
int vector_find_elememt(int vid, const void *e);
int vector_rfind_elememt(int vid, const void *e);
int vector_empty(int vid);
const void *vector_at(int vid, int index);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _VECTOR_H */

