#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    const int arr_orig[10]   = {1, 8, 2, 7, 3, 6, 4, 5, 0, 9};
    const int arr_sorted[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
          int arr[10]        = {0};

    memcpy(arr, arr_orig, sizeof(arr_orig));
    bubble_sort(arr, arrsize(arr), sizeof(int), cmpint, 0);
    ASSERT_INTARR_EQUAL(arr, arr_sorted);

    memcpy(arr, arr_orig, sizeof(arr_orig));
    select_sort(arr, arrsize(arr), sizeof(int), cmpint, 0);  
    ASSERT_INTARR_EQUAL(arr, arr_sorted);

    memcpy(arr, arr_orig, sizeof(arr_orig));
    insert_sort(arr, arrsize(arr), sizeof(int), cmpint, 0);  
    ASSERT_INTARR_EQUAL(arr, arr_sorted);

    memcpy(arr, arr_orig, sizeof(arr_orig));
    quick_sort(arr, arrsize(arr), sizeof(int), cmpint, 0);  
    ASSERT_INTARR_EQUAL(arr, arr_sorted);

    memcpy(arr, arr_orig, sizeof(arr_orig));
    heap_sort(arr, arrsize(arr), sizeof(int), cmpint, 0);  
    ASSERT_INTARR_EQUAL(arr, arr_sorted);

}

/* random interger */
static void _sort_test_case02(void)
{
    int arr[1000] = {0};

    unix_random(arr, sizeof(arr));
    bubble_sort(arr, arrsize(arr), sizeof(int), cmpint, 0);
    ASSERT_INCREASE_INT_ARRAY(arr);

    unix_random(arr, sizeof(arr));  
    select_sort(arr, arrsize(arr), sizeof(int), cmpint, 0);  
    ASSERT_INCREASE_INT_ARRAY(arr);

    unix_random(arr, sizeof(arr));  
    insert_sort(arr, arrsize(arr), sizeof(int), cmpint, 0);  
    ASSERT_INCREASE_INT_ARRAY(arr);

    unix_random(arr, sizeof(arr));  
    quick_sort(arr, arrsize(arr), sizeof(int), cmpint, 0);  
    ASSERT_INCREASE_INT_ARRAY(arr);

    unix_random(arr, sizeof(arr));  
    heap_sort(arr, arrsize(arr), sizeof(int), cmpint, 0);  
    ASSERT_INCREASE_INT_ARRAY(arr);

}

static void _sort_test_cases(void)
{
    fprintf(stderr, "sort test begin\n");
    _sort_test_case01();
    _sort_test_case02();
    fprintf(stderr, "sort test end\n");
}

int main(int argc, char *argv[])
{
    _sort_test_cases();
    return 0;
}

