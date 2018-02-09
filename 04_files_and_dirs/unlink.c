#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	if (open("tempfile", O_RDWR) < 0)
	{
		fprintf(stderr, "open error\n");
	}

	if (unlink("tempfile") < 0)
	{
		fprintf(stderr, "unlink error\n");
	}

	printf("file unlinked\n");
	sleep(15);
	printf("done\n");
	exit(0);
}
