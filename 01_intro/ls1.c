#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: %s directory_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    DIR *dp;

    if ((dp = opendir(argv[1])) == NULL)
    {
        printf("can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    struct dirent *dir_entry;

    while ((dir_entry = readdir(dp)) != NULL)
    {
        printf("%s\t(%lu)\n", dir_entry->d_name, dir_entry->d_ino);
    }

    closedir(dp);
}
