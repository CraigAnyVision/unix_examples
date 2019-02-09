#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void make_temp(char *template);

int main()
{
	// allocated on stack
	char good_template[] = "/tmp/dirXXXXXX";

	// only pointer allocated on stack
	// string allocated in readonly section of elf
	char *bad_template = "/tmp/dirXXXXXX";

	printf("trying to create first temp file...\n");
	make_temp(good_template);

	printf("trying to create second temp file...\n");
	make_temp(bad_template);

	exit(0);
}

void make_temp(char *template)
{
	int fd;
	struct stat stat_buf;

	if ((fd = mkstemp(template)) < 0)
	{
		fputs("can't create temp file", stderr);
		exit(1);
	}

	printf("temp name = %s\n", template);
	close(fd);

	if (stat(template, &stat_buf) < 0)
	{
		if (errno == ENOENT)
		{
			printf("file doesn't exist\n");
		}
		else
		{
			fputs("stat failed", stderr);
			exit(1);
		}
	}
	else
	{
		printf("file exists\n");
		unlink(template);
	}
}
