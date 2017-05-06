#include <stdlib.h>
#include <string.h>
#include "sort.h"

#define valid_para(base, n, size, cmp)    ((base) && (n) > 1 && (size) > 0 && (cmp))
#define elememt_at(base, size, pos)       ((void *)((unsigned char *)(base) + (pos) * (size)))
#define const_elememt_at(base, size, pos) ((const void *)elememt_at(base, size, pos))
#define swap_element(e1, e2, size)    \
    do                                \
    {                                 \
        void *tmp = calloc(1, size);  \
        memcpy(tmp, e1, size);        \
        memcpy(e1, e2, size);         \
        memcpy(e2, tmp, size);        \
        free(tmp);                    \
    }while (0)

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

