#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 4096

// Usage: ./mycat < infile > outfile
int main (void)
{
    ssize_t n = 0;
    char buf[BUFF_SIZE];

    // read(), write() and close() are unbuffered IO operations
    while ((n = read(STDIN_FILENO, buf, BUFF_SIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, (size_t) n) != n)
        {
            printf("write error");
            exit(EXIT_FAILURE);
        }
    }

    if (n < 0)
    {
        printf("read error");
        exit(EXIT_FAILURE);
    }
}
