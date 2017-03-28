#ifndef _TEST_API_H
#define _TEST_API_H

#include <stdio.h>

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

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _TEST_API_H */

