#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void print_time (const char *description, time_t time)
{
    struct tm *time_info = localtime(&(time));
    char time_buf[20];

    strftime(time_buf, 20, "%d/%m/%Y %H:%M:%S", time_info);
    printf("%s: %s\n", description, time_buf);
}

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat stat_buf;
    struct timespec times[2];

    if (stat(argv[1], &stat_buf) < 0)
    {
        // fetch current times
        fprintf(stderr, "%s: stat error\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    print_time("status change time", stat_buf.st_ctime);
    print_time("access time", stat_buf.st_atime);
    print_time("modification time", stat_buf.st_mtime);
}
