#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	time_t t;
	time(&t);
	struct tm *tmp = localtime(&t);

	printf("unix time: %lu\n", t);

	char buf[64];
	if (strftime(buf, 64, "formatted: %r, %a %b %d, %Y", tmp) == 0)
	{
		printf("buffer length 64 is too small\n");
		exit(EXIT_FAILURE);
	}

	puts(buf);
}
