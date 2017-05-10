#ifndef _SORT_H
#define _SORT_H

#include "common.h"

typedef int (*cmpfunc_t)(const void *, const void *, void *);

EXTERN void bubble_sort(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg);
EXTERN void select_sort(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg);
EXTERN void insert_sort(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg);
EXTERN void quick_sort(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg);
EXTERN void heap_sort(void *base, size_t n, size_t size, cmpfunc_t cmp, void *arg);

#endif /* _SORT_H */

