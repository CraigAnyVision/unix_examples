#pragma once

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifdef  PATH_MAX
static long path_max = PATH_MAX;
#else
static long path_max = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

// If PATH_MAX is indeterminate, no guarantee this is adequate
#define PATH_MAX_GUESS  1024

// also return allocated size, if nonnull
char *path_alloc (size_t *path_size)
{
    char *ptr;
    size_t size;

    if (posix_version == 0)
    {
        posix_version = sysconf(_SC_VERSION);
    }

    if (xsi_version == 0)
    {
        xsi_version = sysconf(_SC_XOPEN_VERSION);
    }

    if (path_max == 0)
    {
        // first time through
        errno = 0;
        if ((path_max = pathconf("/", _PC_PATH_MAX)) < 0)
        {
            if (errno == 0)
            {
                path_max = PATH_MAX_GUESS;
            }
            else
            {
                // it's indeterminate
                fprintf(stderr, "pathconf error for _PC_PATH_MAX\n");
            }
        }
        else
        {
            // add one since it's relative to root
            path_max++;
        }
    }

    /*
     * Before POSIX.1-2001, we aren't guaranteed that PATH_MAX includes
     * the terminating null byte.  Same goes for XPG3.
     */
    if ((posix_version < 200112L) && (xsi_version < 4))
    {
        size = path_max + 1;
    }
    else
    {
        size = path_max;
    }

    if ((ptr = malloc(size)) == NULL)
    {
        fprintf(stderr, "malloc error for pathname\n");
    }

    if (path_size != NULL)
    {
        *path_size = size;
    }

    return (ptr);
}
