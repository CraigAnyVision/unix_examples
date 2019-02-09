#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(void)
{
	mode_t old_umask = umask(0);

	printf("Old umask: %04d\n", old_umask);

	// -rw-rw-rw-  1 craig craig     0 Feb  9 21:42 foo
	if (creat("foo", RWRWRW) < 0)
	{
		fprintf(stderr, "creat error for foo\n");
		exit(EXIT_FAILURE);
	}

	old_umask = umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	printf("Old umask: %04d\n", old_umask);

	// -rw-------  1 craig craig     0 Feb  9 21:42 bar
	if (creat("bar", RWRWRW) < 0)
	{
		fprintf(stderr, "creat error for bar\n");
		exit(EXIT_FAILURE);
	}
}
