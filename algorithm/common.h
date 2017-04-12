#ifndef _COMMON_H
#define _COMMON_H

#include <string.h>

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN extern
#endif

#ifndef bzero
#define bzero(p, size) memset((p), 0, (size))
#endif

#define arrsize(arr) (sizeof(arr) / sizeof(arr[0]))

#define ASSERT_EQUAL_INT(exp1, exp2)                              \
    do                                                            \
    {                                                             \
        int value1 = (exp1);                                      \
        int value2 = (exp2);                                      \
        if (value1 != value2)                                     \
            fprintf(stderr,                                       \
                    "[%s:%d], assertion failure: %d != %d\n",     \
                    __FUNCTION__,                                 \
                    __LINE__,                                     \
                    value1,                                       \
                    value2);                                      \
    }while (0)

#define ASSERT_EQUAL_PTR(p1, p2)                                  \
    do                                                            \
    {                                                             \
        const void *ptr1 = (p1);                                  \
        const void *ptr2 = (p2);                                  \
        if (ptr1 != ptr2)                                         \
            fprintf(stderr,                                       \
                    "[%s:%d], assertion failure: %p != %p\n",     \
                    __FUNCTION__,                                 \
                    __LINE__,                                     \
                    ptr1,                                         \
                    ptr2);                                        \
    }while (0)

#endif /* _COMMON_H */

