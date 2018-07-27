#include <fcntl.h>
#include <stdio.h>

// flags are file status flags to turn on
void set_flags (int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        fprintf(stderr, "fcntl F_GETFL error\n");

    // turn on flags
    val |= flags;

    if (fcntl(fd, F_SETFL, val) < 0)
        fprintf(stderr, "fcntl F_SETFL error\n");
}

// flags are file status flags to turn off
void clear_flags (int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        fprintf(stderr, "fcntl F_GETFL error\n");

    // turn off flags
    val &= ~flags;

    if (fcntl(fd, F_SETFL, val) < 0)
        fprintf(stderr, "fcntl F_SETFL error\n");
}
