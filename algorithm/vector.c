#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define M_VECTOR_MAX_VECTOR_NUM  100
#define M_VECTOR_MAX_ELEMENT_NUM 1000

typedef struct
{
    int             id;
    int             nelement;
    const void     *elememts[M_VECTOR_MAX_ELEMENT_NUM];
    compare_func_t  compare_func;
}vector_t;

vector_t g_vectors[M_VECTOR_MAX_VECTOR_NUM] = {0};
int      g_vector_num                       = 0;
int      g_vector_current_id                = 0;

static inline int _vector_get_index(int vid)
{
    int i = 0;

    for (; i < g_vector_num; ++i)
        if (vid == g_vectors[i].id)
            return i;

    return -1;
}

static vector_t *_vector_get_ptr(int vid)
{
    int index = _vector_get_index(vid);

    if (index < 0)
        return 0;

    return &g_vectors[index];
}


int vector_alloc(compare_func_t compare_func, int *vid)
{
    vector_t *v = 0;
    
    if (!compare_func || !vid)
        return e_vector_err_null_ptr;

    if (g_vector_num >= M_VECTOR_MAX_VECTOR_NUM)
        return e_vector_err_full;

    v = &g_vectors[g_vector_num++];
    memset(v, 0, sizeof(vector_t));
    v->id = *vid    = g_vector_current_id++;
    v->compare_func = compare_func;
    return e_vector_success;
}

int vector_free(int vid)
{
    int index = _vector_get_index(vid);

    if (index < 0)
        return e_vector_err_id_not_found;


    if (index < g_vector_num - 1)
        memmove(&g_vectors[index],
                &g_vectors[index + 1],
                sizeof(vector_t) * (g_vector_num - 1 - index));

    --g_vector_num;
    return e_vector_success;
}

int vector_push_back(int vid, const void *e)
{
    vector_t *v = 0;

    if (!e)
        return e_vector_err_null_ptr;

    if (!(v = _vector_get_ptr(vid)))
        return e_vector_err_id_not_found;

    if (v->nelement >= M_VECTOR_MAX_ELEMENT_NUM)
        return e_vector_err_element_full;

    v->elememts[v->nelement++] = e;
    return e_vector_success;
}

int vector_pop_back(int vid)
{
    vector_t *v = 0;

    if (!(v = _vector_get_ptr(vid)))
        return e_vector_err_id_not_found;

    return vector_erase(vid, v->nelement - 1);
}

int vector_clear(int vid)
{
    vector_t *v = _vector_get_ptr(vid);

    if (!v)
        return e_vector_err_id_not_found;

    memset(v, 0, sizeof(vector_t));
    return e_vector_success; 
}

int vector_size(int vid)
{
    vector_t *v = 0;

    if (!(v = _vector_get_ptr(vid)))
        return -1;

    return v->nelement;
}

int vector_insert(int vid, int index, const void *e)
{
    vector_t *v = 0;

    if (!e)
        return e_vector_err_null_ptr;

    if (!(v = _vector_get_ptr(vid)))
        return e_vector_err_id_not_found;

    if (v->nelement >= M_VECTOR_MAX_ELEMENT_NUM)
        return e_vector_err_element_full;

    if (index < 0 || index > v->nelement)
        return e_vector_err_index_invalid;

    if (index < v->nelement)
        memmove(&v->elememts[index + 1],
                &v->elememts[index],
                sizeof(const void *) * (v->nelement - index));

    v->elememts[v->nelement++] = e;
    return e_vector_success;
}

int vector_erase(int vid, int index)
{
    vector_t *v = 0;

    if (!(v = _vector_get_ptr(vid)))
        return e_vector_err_id_not_found;

    if (v->nelement <= 0)
        return e_vector_err_element_empty;

    if (index < 0 || index >= v->nelement)
        return e_vector_err_index_invalid;

    if (index + 1 < v->nelement)
        memmove(&v->elememts[index],
                &v->elememts[index + 1],
                sizeof(const void *) * (v->nelement - 1 - index));

    --v->nelement;
    return e_vector_success;
}


int vector_sort(int vid, compare_func_t compare_func)
{
    vector_t *v = 0;

    if (!compare_func)
        return e_vector_err_null_ptr;

    if (!(v = _vector_get_ptr(vid)))
        return e_vector_err_id_not_found;

    qsort(v->elememts, v->nelement, sizeof(const void *), compare_func);
    return e_vector_success;
}

int vector_traverse(int vid, traverse_func_t traverse_func)
{
    vector_t *v = 0;
    int       i = 0;

    if (!traverse_func)
        return e_vector_err_null_ptr;

    if (!(v = _vector_get_ptr(vid)))
        return e_vector_err_id_not_found;


    for (; i < v->nelement; ++i)
        traverse_func(v->elememts[i]);

    return e_vector_success;
}

int vector_reverse(int vid)
{
    vector_t *v = 0;
    int       i = 0;

    if (!(v = _vector_get_ptr(vid)))
        return e_vector_err_id_not_found;

    for (; i < v->nelement / 2; ++i)
    {
        const void *tmp                  = v->elememts[i];
        v->elememts[i]                   = v->elememts[v->nelement - 1 - i];
        v->elememts[v->nelement - 1 - i] = tmp;
    }

    return e_vector_success;
}

int vector_find_elememt(int vid, const void *e)
{
    vector_t *v = 0;
    int       i = 0;

    if (!e)
        return -1;

    if (!(v = _vector_get_ptr(vid)))
        return -1;

    for (; i < v->nelement; ++i)
        if (!v->compare_func(e, v->elememts[i]))
            return i;

    return -1;
}

int vector_rfind_elememt(int vid, const void *e)
{
    vector_t *v = 0;
    int       i = 0;

    if (!e)
        return -1;

    if (!(v = _vector_get_ptr(vid)))
        return -1;

    for (i = v->nelement - 1; i >= 0; --i)
        if (!v->compare_func(e, v->elememts[i]))
            return i;

    return -1;
}

int vector_empty(int vid)
{
    vector_t *v = 0;

    if (!(v = _vector_get_ptr(vid)))
        return 0;

    return ((0 == v->nelement) ? 1 : 0);
}

const void *vector_at(int vid, int index)
{
    vector_t *v = 0;

    if (!(v = _vector_get_ptr(vid)))
        return 0;

    if (v->nelement <= 0)
        return 0;

    if (index < 0 || index >= v->nelement)
        return 0;

    return v->elememts[index];    
}

