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

#define arrsize(arr) (sizeof(arr) / sizeof(arr[0]))

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
                    "[%s:%d], assertion failure: %d >= %d\n",     \
                    __FUNCTION__,                                 \
                    __LINE__,                                     \
                    (int)(exp1),                                  \
                    (int)(exp2));                                 \
    }while (0)        


EXTERN void unix_random(void *random, size_t size);
EXTERN void dump_int_array(int arr[], size_t size);

#endif /* _COMMON_H */

