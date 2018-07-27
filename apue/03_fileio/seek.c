#include <stdio.h>
#include <unistd.h>

// Usage:
//    ./seek < /etc/passwd
//        seek OK
//    cat < /etc/passwd | seek
//        cannot seek
//        cat: write error: Broken pipe
//    ./seek /var/spool/cron/FIFO
//        cannot seek
int main (void)
{
    off_t curr_pos = lseek(STDIN_FILENO, 0, SEEK_CUR);

    // If whence is SEEK_CUR, the file’s offset is set to its current value plus the offset
    if (curr_pos == -1)
        printf("cannot seek\n");
    else
        printf("seek OK\n");
}
