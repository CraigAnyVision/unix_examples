#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
	struct stat stat_buf;

	if (stat("foo", &stat_buf) < 0)
	{
		fprintf(stderr, "stat error for foo\n");
		exit(EXIT_FAILURE);
	}

	// turn on set-group-ID and turn off group-execute
	//-rw-rwSrw- 1 craig craig 0 Feb  9 21:51 foo
	// uppercase   S signifies that set-group-id is set without group-execute
	if (chmod("foo", (stat_buf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
	{
		fprintf(stderr, "chmod error for foo\n");
		exit(EXIT_FAILURE);
	}

	// set absolute mode
	// -rw-r--r-- 1 craig craig 0 Feb  9 21:51 bar
	if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
	{
		fprintf(stderr, "chmod error for bar\n");
		exit(EXIT_FAILURE);
	}
}
