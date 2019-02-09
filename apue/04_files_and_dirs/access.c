#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Usage:
//    ./access /etc/passwd
//        read access OK
//        open for reading OK
//    ./access /etc/shadow
//        access error for /etc/shadow
//        open error for /etc/shadow
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (access(argv[1], R_OK) < 0)
	{
		fprintf(stderr, "access error for %s\n", argv[1]);
	}
	else
	{
		printf("read access OK\n");
	}

	if (open(argv[1], O_RDONLY) < 0)
	{
		fprintf(stderr, "open error for %s\n", argv[1]);
	}
	else
	{
		printf("open for reading OK\n");
	}
}
