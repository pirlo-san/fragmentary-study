#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "common.h"

#define valid_para(base, n, size, cmp)    ((base) && (n) > 1 && (size) > 0 && (cmp))

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
