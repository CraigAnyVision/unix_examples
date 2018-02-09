#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main (void)
{
    struct stat stat_buf;

    // turn on set-group-ID and turn off group-execute
    if (stat("foo", &stat_buf) < 0)
    {
        fprintf(stderr, "stat error for foo\n");
        exit(1);
    }

    if (chmod("foo", (stat_buf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
    {
        fprintf(stderr, "chmod error for foo\n");
        exit(1);
    }

    // set absolute mode to "rw-r--r--"
    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
    {
        fprintf(stderr, "chmod error for bar\n");
        exit(1);
    }

    exit(0);
}
