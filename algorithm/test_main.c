#include <stdio.h>
#include <string.h>
#include "test_graph.h"

typedef void (*test_func_t)(void);

typedef struct
{
    const char  *module_name;
    test_func_t  test_func;
}test_case_t;

int main(int argc, char *argv[])
{
    int i = 0;
    
    test_case_t testcases[] =
    {
        {"graph",  graph_test_cases},
    };

    if (argc <= 1)
    {
        fprintf(stderr, "module not specified, do nothing\n");
        return 0;
    }

    if (!strcmp(argv[1], "all"))
    {
        int i = 0;
        for (; i < sizeof(testcases) / sizeof(testcases[0]); ++i)
        {
            fprintf(stderr, "\ntest %s begin\n", testcases[i].module_name);
            testcases[i].test_func();
            fprintf(stderr, "test %s end\n\n", testcases[i].module_name);
        }
        
        return 0;
    }

    for (; i < sizeof(testcases) / sizeof(testcases[0]); ++i)
    {
        if (!strcmp(argv[1], testcases[i].module_name))
        {
            fprintf(stderr, "\ntest %s begin\n", testcases[i].module_name);
            testcases[i].test_func();
            fprintf(stderr, "test %s end\n\n", testcases[i].module_name);
            return 0;
        }
    }

    fprintf(stderr, "module \"%s\" not found, do nothing\n", argv[1]);
    return 0;
    
}

