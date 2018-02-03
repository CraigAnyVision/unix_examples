#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 4096

int main (void)
{
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
