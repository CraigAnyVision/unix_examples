#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    int c = 0;

    // getc(), putc() and printf() are buffered IO operations
    while ((c = getc(stdin)) != EOF)
    {
        if (putc(c, stdout) == EOF)
        {
            printf("output error");
            exit(EXIT_FAILURE);
        }
    }

    if (ferror(stdin))
    {
        printf("input error");
        exit(EXIT_FAILURE);
    }
}
