#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "path_alloc.h"

int main (void)
{
    char *ptr;
    size_t size;

    if (chdir("/proc/thread-self/fd") < 0)
    {
        fprintf(stderr, "chdir failed\n");
        exit(EXIT_FAILURE);
    }

    ptr = path_alloc(&size);

    if (getcwd(ptr, size) == NULL)
    {
        fprintf(stderr, "getcwd failed\n");
    }

    printf("cwd = %s\n", ptr);
}
