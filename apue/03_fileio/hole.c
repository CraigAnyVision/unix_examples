#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main (void)
{
    int fd;

    // S_IRUSR: Read permission bit for the owner of the file
    // S_IWUSR: Write permission bit for the owner of the file
    // S_IRGRP: Read permission bit for the group owner of the file
    // S_IROTH: Read permission bit for other users
    if ((fd = creat("file.hole", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
        fprintf(stderr, "creat error\n");
        exit(EXIT_FAILURE);
    }

    // write 10 characters from buf1 to the file
    if (write(fd, buf1, 10) != 10)
    {
        fprintf(stderr, "buf1 write error\n");
        exit(EXIT_FAILURE);
    }

    // offset now = 10

    // If whence is SEEK_SET, the file’s offset is set to offset bytes from the beginning of the file
    if (lseek(fd, 16384, SEEK_SET) == -1)
    {
        fprintf(stderr, "lseek error\n");
        exit(EXIT_FAILURE);
    }

    // offset now = 16384

    if (write(fd, buf2, 10) != 10)
    {
        fprintf(stderr, "buf2 write error\n");
        exit(EXIT_FAILURE);
    }

    // offset now = 16394

    exit(EXIT_SUCCESS);
}
