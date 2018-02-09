#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "modflags.h"

#define BUFF_SIZE 4096

// Use:
//    ./mycat < infile > outfile
int main (void)
{
    // turn on sync write flag
    // this causes each write to wait for data to be written to disc before returning
    // normally a write only queues the data for writing
    set_flags(STDOUT_FILENO, O_SYNC);

    int n;
    char buf[BUFF_SIZE];

    while ((n = read(STDIN_FILENO, buf, BUFF_SIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, (size_t) n) != n)
        {
            fprintf(stderr, "write error");
            exit(1);
        }
    }

    if (n < 0)
    {
        fprintf(stderr, "read error");
        exit(1);
    }
}
