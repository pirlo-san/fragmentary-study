#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "common.h"

#define valid_para(base, n, size, cmp)    ((base) && (n) > 1 && (size) > 0 && (cmp))

static size_t _partition(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg)
{
    void *pivot = 0;
    size_t      left  = 0;
    size_t      right = n -1;

    if (n <= 1)
        return 0;

    if (!(pivot = calloc(1, size)))
        return 0;

    memcpy(pivot, base, size);
    while (left < right)
    {
        while (left < right
               && cmp(const_elememt_at(base, size, right), pivot, arg) >= 0)
            --right;
        memcpy(elememt_at(base, size, left), elememt_at(base, size, right), size);

        while (left < right
               && cmp(const_elememt_at(base, size, left), pivot, arg) <= 0)
            ++left;
        memcpy(elememt_at(base, size, right), elememt_at(base, size, left), size);
    }
    memcpy(elememt_at(base, size, left), pivot, size);

    free(pivot);
    return left;
}

static void _heap_adjust(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg, size_t idx)
{
    size_t left  = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    while (left < n)
    {
        size_t maxidx = idx;

        if (left < n
            && cmp(const_elememt_at(base, size, left), const_elememt_at(base, size, maxidx), arg) > 0)
            maxidx = left;

        if (right < n
            && cmp(const_elememt_at(base, size, right), const_elememt_at(base, size, maxidx), arg) > 0)
            maxidx = right;

        if (maxidx == idx)
            break;

        swap_element(elememt_at(base, size, maxidx), elememt_at(base, size, idx), size);

        idx = maxidx;
        left  = 2 * idx + 1;
        right = 2 * idx + 2;
    }
}

static void _build_heap(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg)
{
    ssize_t idx = (n - 1) / 2;

    for (; idx >= 0; --idx)
        _heap_adjust(base, n, size, cmp, arg, idx);
}

void bubble_sort(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg)
{
    size_t loop = 0;

    if (!valid_para(base, n, size, cmp))
        return;

    for (; loop < n - 1; ++loop)
    {
        size_t idx = n - 1;
        for (; idx > loop; --idx)
            if (cmp(const_elememt_at(base, size, idx), const_elememt_at(base, size, idx - 1), arg) < 0)
                swap_element(elememt_at(base, size, idx), 
                             elememt_at(base, size, idx - 1),
                             size);
    }
}

void select_sort(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg)
{
    size_t idx = 0;

    if (!valid_para(base, n, size, cmp))
        return;

    for (; idx < n - 1; ++idx)
    {
        size_t minidx    = idx;
        size_t inner_idx = idx + 1;

        for (; inner_idx < n ; ++inner_idx)
            if (cmp(const_elememt_at(base, size, inner_idx), const_elememt_at(base, size, minidx), arg) < 0)
                minidx = inner_idx;

        if (minidx != idx)
            swap_element(elememt_at(base, size, minidx), elememt_at(base, size, idx), size);
    }
}

void insert_sort(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg)
{
    size_t idx = 1;

    if (!valid_para(base, n, size, cmp))
        return;

    for (; idx < n; ++idx)
    {
        size_t inner_idx = 0;
        for (; inner_idx < idx; ++inner_idx)
            if (cmp(const_elememt_at(base, size, idx), const_elememt_at(base, size, inner_idx), arg) < 0)
                break;
        if (inner_idx >= idx)
            continue;

        void *tmp = calloc(1, size);
        memcpy(tmp, const_elememt_at(base, size, idx), size);
        memmove(elememt_at(base, size, inner_idx + 1), 
                elememt_at(base, size, inner_idx),
                size * (idx - inner_idx));
        memcpy(elememt_at(base, size, inner_idx), tmp, size);
        free(tmp);
    }
}

void quick_sort(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg)
{
    size_t mid = 0;

    if (!valid_para(base, n, size, cmp))
        return;

    mid = _partition(base, n, size, cmp, arg);
    quick_sort(elememt_at(base, size, 0),       mid,         size, cmp, arg);
    quick_sort(elememt_at(base, size, mid + 1), n - mid - 1, size, cmp, arg);    
}

void heap_sort(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg)
{
    ssize_t idx = n - 1;

    if (!valid_para(base, n, size, cmp))
        return;

    _build_heap(base, n, size, cmp, arg);

    for (; idx > 0; --idx)
    {
        swap_element(elememt_at(base, size, idx), elememt_at(base, size, 0), size);
        _heap_adjust(base, idx, size, cmp, arg, 0);
    }
}

