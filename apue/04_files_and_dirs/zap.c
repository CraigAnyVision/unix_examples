#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	struct stat statbuf;
	struct timespec times[2];

	for (int i = 1; i < argc; i++)
	{
		if (stat(argv[i], &statbuf) < 0)
		{
			// fetch current times
			fprintf(stderr, "%s: stat error\n", argv[i]);
			continue;
		}

		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0)
		{
			// truncate
			fprintf(stderr, "%s: open error\n", argv[i]);
			continue;
		}

		times[0] = statbuf.st_atim;  // access time
		times[1] = statbuf.st_mtim;  // modification time

		if (futimens(fd, times) < 0)
		{
			// reset times
			fprintf(stderr, "%s: futimens error\n", argv[i]);
		}

		close(fd);
	}
}
