#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "common.h"

void unix_random(void *random, size_t size)
{
    int    fd = -1;
    size_t nread = 0;

    if (!random || size <= 0)
        return;

    if ( (fd = open("/dev/urandom", O_RDONLY)) < 0)
        return;

    fcntl(fd, F_SETFL, O_NONBLOCK);
    while (nread < size)
    {
        ssize_t n = read(fd, random, size - nread);
        if (n <= 0)
            break;
        nread += n;
    }
    
    close(fd);
}

void random_array(void *arr, size_t n, size_t size)
{
    size_t idx = 0;

    if (!arr || n <= 0 || size <= 0)
        return;

    for (; idx < n; ++idx)
        unix_random(elememt_at(arr, size, idx), size);
}

void dump_int_array(int arr[], size_t size)
{
    size_t idx = 0;

    for (; idx < size; ++idx)
    {
        fprintf(stderr, "%11d ", arr[idx]);
        if (0 == ((idx + 1) % 16))
            fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
}

