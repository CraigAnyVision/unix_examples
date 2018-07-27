#pragma once

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

static void print_sysconf (char *mesg, int name)
{
    long val;

    fputs(mesg, stdout);
    errno = 0;
    if ((val = sysconf(name)) < 0)
    {
        if (errno != 0)
        {
            if (errno == EINVAL)
                fputs(" (not supported)\n", stdout);
            else
                fprintf(stderr, "sysconf error");
        }
        else
        {
            fputs(" (no limit)\n", stdout);
        }
    }
    else
    {
        printf(" %ld\n", val);
    }
}

static void print_pathconf (char *mesg, char *path, int name)
{
    long val;

    fputs(mesg, stdout);
    errno = 0;
    if ((val = pathconf(path, name)) < 0)
    {
        if (errno != 0)
        {
            if (errno == EINVAL)
                fputs(" (not supported)\n", stdout);
            else
                fprintf(stderr, "pathconf error, path = %s", path);
        }
        else
        {
            fputs(" (no limit)\n", stdout);
        }
    }
    else
    {
        printf(" %ld\n", val);
    }
}
