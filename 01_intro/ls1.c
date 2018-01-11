#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ls directory_name\n");
        exit(EXIT_FAILURE);
    }

    DIR *dp;

    if ((dp = opendir(argv[1])) == NULL)
    {
        printf("can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    struct dirent *dir_entryp;

    while ((dir_entryp = readdir(dp)) != NULL)
    {
        printf("%s\t(%lu)\n", dir_entryp->d_name, dir_entryp->d_ino);
    }

    closedir(dp);
}
