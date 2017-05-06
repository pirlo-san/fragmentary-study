#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "sort.h"

static int cmpint(const void *e1, const void *e2, void *arg)
{
    int ival1 = *((const int *)e1);
    int ival2 = *((const int *)e2);

    if (ival1 < ival2)
        return -1;
    if (ival1 > ival2)
        return 1;
    return 0;
}

/* interger */
static void _sort_test_case01(void)
{
    int    arr[20] = {0};
    size_t idx = 0;

    unix_random(arr, sizeof(arr));  
    /* dump_int_array(arr, arrsize(arr)); */
    bubble_sort(arr, arrsize(arr), sizeof(int), cmpint, 0);  
    /* dump_int_array(arr, arrsize(arr)); */
    for (idx = 0; idx < arrsize(arr) - 1; ++idx)
    {
        ASSERT_INT_LESSEQUAL(arr[idx], arr[idx + 1]);
    }
}

static void _sort_test_cases(void)
{
    fprintf(stderr, "sort test begin\n");
    _sort_test_case01();
    fprintf(stderr, "sort test end\n");
}

int main(int argc, char *argv[])
{
    _sort_test_cases();
    return 0;
}

