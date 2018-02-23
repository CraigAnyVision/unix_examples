#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "path_alloc.h"

// function type that is called for each filename
typedef int MyFunc (const char *, const struct stat *, int);

static MyFunc file_counter;

static int my_ftw (char *, MyFunc *);

static int process_path (MyFunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage:  ftw  <starting-pathname>\n");
    }

    int ret = my_ftw(argv[1], file_counter);

    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;

    if (ntot == 0)
    {
        // avoid divide by 0; print 0 for all counts
        ntot = 1;
    }

    printf("regular files  = %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
    printf("directories    = %7ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
    printf("block special  = %7ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
    printf("char special   = %7ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
    printf("FIFOs          = %7ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
    printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
    printf("sockets        = %7ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);

    exit(ret);
}

/*
 * Descend through the hierarchy, starting at "path_name".
 * The caller's func() is called for every file.
 */
#define    FTW_F    1      // file other than directory
#define    FTW_D    2      // directory
#define    FTW_DNR  3      // directory that can't be read
#define    FTW_NS   4      // file that we can't stat

// contains full pathname for every file
static char *full_path;
static size_t path_len;

// we return whatever func() returns
static int my_ftw (char *path_name, MyFunc *func)
{
    // malloc PATH_MAX+1 bytes
    full_path = path_alloc(&path_len);

    if (path_len <= strlen(path_name))
    {
        path_len = strlen(path_name) * 2;
        if ((full_path = realloc(full_path, path_len)) == NULL)
        {
            fprintf(stderr, "realloc failed\n");
        }
    }
    strcpy(full_path, path_name);
    return (process_path(func));
}

/*
 * Descend through the hierarchy, starting at "full_path".
 * If "fullpath" is anything other than a directory, we lstat() it,
 * call func(), and return.  For a directory, we call ourself
 * recursively for each name in the directory.
 * we return whatever func() returns
 */
static int process_path (MyFunc *func)
{
    struct stat stat_buf;
    struct dirent *dirp;
    DIR *dp;
    int ret, n;

    // stat error
    if (lstat(full_path, &stat_buf) < 0)
        return (func(full_path, &stat_buf, FTW_NS));

    // not a directory
    if (S_ISDIR(stat_buf.st_mode) == 0)
        return (func(full_path, &stat_buf, FTW_F));

    /*
     * It's a directory.  First call func() for the directory,
     * then process each filename in the directory
     */
    if ((ret = func(full_path, &stat_buf, FTW_D)) != 0)
        return (ret);

    n = (int) strlen(full_path);
    if (n + NAME_MAX + 2 > path_len)
    {    // expand path buffer
        path_len *= 2;
        if ((full_path = realloc(full_path, path_len)) == NULL)
            fprintf(stderr, "realloc failed\n");
    }

    full_path[n++] = '/';
    full_path[n] = 0;

    if ((dp = opendir(full_path)) == NULL)
    {
        // can't read directory
        return (func(full_path, &stat_buf, FTW_DNR));
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
        {
            // ignore dot and dot-dot
            continue;
        }

        // append name after "/"
        strcpy(&full_path[n], dirp->d_name);

        // recursive
        if ((ret = process_path(func)) != 0)
        {
            // time to leave
            break;
        }
    }

    // erase everything from slash onward
    full_path[n - 1] = 0;

    if (closedir(dp) < 0)
    {
        fprintf(stderr, "can't close directory %s\n", full_path);
    }
    return (ret);
}

static int file_counter (const char *pathname, const struct stat *statptr, int type)
{
    switch (type)
    {
        case FTW_F:
            switch (statptr->st_mode & S_IFMT)
            {
                case S_IFREG:
                    nreg++;
                    break;
                case S_IFBLK:
                    nblk++;
                    break;
                case S_IFCHR:
                    nchr++;
                    break;
                case S_IFIFO:
                    nfifo++;
                    break;
                case S_IFLNK:
                    nslink++;
                    break;
                case S_IFSOCK:
                    nsock++;
                    break;
                case S_IFDIR:
                    // directories should have type = FTW_D
                    fprintf(stderr, "for S_IFDIR for %s\n", pathname);
                    exit(1);
                default:
                    fprintf(stderr, "unrecognized file type %d\n", statptr->st_mode);
                    exit(1);
            }
            break;
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            fprintf(stderr, "can't read directory %s\n", pathname);
            break;
        case FTW_NS:
            fprintf(stderr, "stat error for %s\n", pathname);
            break;
        default:
            fprintf(stderr, "unknown type %d for pathname %s\n", type, pathname);
    }
    return (0);
}
