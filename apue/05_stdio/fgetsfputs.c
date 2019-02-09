#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 4096

int main(void)
{
	char buf[MAX_LINE];

	while (fgets(buf, MAX_LINE, stdin) != NULL)
	{
		if (fputs(buf, stdout) == EOF)
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
