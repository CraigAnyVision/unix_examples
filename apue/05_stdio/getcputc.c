#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int c;

	while ((c = getc(stdin)) != EOF)
	{
		if (putc(c, stdout) == EOF)
		{
			fputs("output error", stderr);
			exit(1);
		}
	}

	if (ferror(stdin))
	{
		fputs("input error", stderr);
		exit(1);
	}

	exit(0);
}
