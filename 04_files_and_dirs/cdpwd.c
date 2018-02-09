#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "path_alloc.h"

int main (void)
{
    char *ptr;
    size_t size;

    if (chdir("/usr/spool/uucppublic") < 0)
    {
        fprintf(stderr, "chdir failed\n");
        exit(1);
    }

    ptr = path_alloc(&size);

    if (getcwd(ptr, size) == NULL)
    {
        fprintf(stderr, "getcwd failed\n");
    }

    printf("cwd = %s\n", ptr);
    exit(0);
}
