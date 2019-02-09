#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (truncate(argv[1], 10))
	{
		fprintf(stderr, "truncate error\n");
		exit(EXIT_FAILURE);
	}

	printf("Truncated %s to 10 chars\n", argv[1]);
}
