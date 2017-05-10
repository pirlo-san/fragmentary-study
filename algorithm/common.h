#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <string.h>

#define IN
#define OUT
#define INOUT

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN extern
#endif

#ifndef bzero
#define bzero(p, size) memset((p), 0, (size))
#endif

#define arrsize(arr)                      (sizeof(arr) / sizeof(arr[0]))
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

#define ASSERT_INT_EQUAL(exp1, exp2)                              \
    do                                                            \
    {                                                             \
        if ((exp1) != (exp2))                                     \
            fprintf(stderr,                                       \
                    "[%s:%d], assertion failure: %d != %d\n",     \
                    __FUNCTION__,                                 \
                    __LINE__,                                     \
                    (int)(exp1),                                  \
                    (int)(exp2));                                 \
    }while (0)

#define ASSERT_INT_LESS(exp1, exp2)                               \
    do                                                            \
    {                                                             \
        if ((exp1) >= (exp2))                                     \
            fprintf(stderr,                                       \
                    "[%s:%d], assertion failure: %d >= %d\n",     \
                    __FUNCTION__,                                 \
                    __LINE__,                                     \
                    (int)(exp1),                                  \
                    (int)(exp2));                                 \
    }while (0)

#define ASSERT_INT_LESSEQUAL(exp1, exp2)                          \
    do                                                            \
    {                                                             \
        if ((exp1) > (exp2))                                      \
            fprintf(stderr,                                       \
                    "[%s:%d], assertion failure: %d > %d\n",      \
                    __FUNCTION__,                                 \
                    __LINE__,                                     \
                    (int)(exp1),                                  \
                    (int)(exp2));                                 \
    }while (0)        

#define ASSERT_INCREASE_INT_ARRAY(arr)                            \
    do                                                            \
    {                                                             \
        size_t idx = 0;                                           \
        for (; idx < arrsize(arr) - 1; ++idx)                     \
            ASSERT_INT_LESSEQUAL(arr[idx], arr[idx + 1]);         \
    }while (0)

#define ASSERT_INTARR_EQUAL(arr1, arr2)                           \
    do                                                            \
    {                                                             \
        size_t idx = 0;                                           \
        for (; idx < arrsize(arr1) - 1; ++idx)                    \
            ASSERT_INT_EQUAL(arr1[idx], arr2[idx]);               \
    }while (0)

EXTERN void unix_random(void *random, size_t size);
EXTERN void random_array(void *arr, size_t n, size_t size);
EXTERN void dump_int_array(int arr[], size_t size);

#endif /* _COMMON_H */

