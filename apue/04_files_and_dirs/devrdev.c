#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

int main(int argc, char *argv[])
{
	struct stat stat_buf;

	for (int i = 1; i < argc; i++)
	{
		printf("%s: ", argv[i]);
		if (stat(argv[i], &stat_buf) < 0)
		{
			fprintf(stderr, "stat error\n");
			continue;
		}

		printf("dev = %d/%d", major(stat_buf.st_dev), minor(stat_buf.st_dev));

		if (S_ISCHR(stat_buf.st_mode) || S_ISBLK(stat_buf.st_mode))
		{
			printf(" (%s) rdev = %d/%d", (S_ISCHR(stat_buf.st_mode)) ? "character" : "block", major(stat_buf.st_rdev),
			       minor(stat_buf.st_rdev));
		}
		printf("\n");
	}

	exit(0);
}
