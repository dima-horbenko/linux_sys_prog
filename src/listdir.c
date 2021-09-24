/* This program lists all files in a given directory.
It is something like ls command. */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define SHIFT_TO_TYPE 12

void listfile(const char *name);


void main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: listdir <dirname>\n");
        exit(1);
    }

    chdir(argv[1]);
    DIR *d = opendir(".");

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL)
    {
        listfile(entry->d_name);
    }
}


void listfile(const char *name)
{
    struct stat stat_buf;
    if (lstat(name, &stat_buf) < 0)
    {
        perror(name);
        exit(2);
    }

    char *filetype[] = {"?", "p", "c", "?", "d", "?", "b", "?", "-", "?", "l", 
                        "?", "s"};
    printf("%s", filetype[(stat_buf.st_mode >> SHIFT_TO_TYPE) & 0xF]);

    printf("%c%c%c%c%c%c%c%c%c",
            (stat_buf.st_mode & S_IRUSR) ? 'r' : '-',
            (stat_buf.st_mode & S_IWUSR) ? 'w' : '-',
            (stat_buf.st_mode & S_IXUSR) ? 'x' : '-',
            (stat_buf.st_mode & S_IRGRP) ? 'r' : '-',
            (stat_buf.st_mode & S_IWGRP) ? 'w' : '-',
            (stat_buf.st_mode & S_IXGRP) ? 'x' : '-',
            (stat_buf.st_mode & S_IROTH) ? 'r' : '-',
            (stat_buf.st_mode & S_IWOTH) ? 'w' : '-',
            (stat_buf.st_mode & S_IXOTH) ? 'x' : '-');

    printf("%8ld", stat_buf.st_size);

    char *modtime = ctime((time_t*)&stat_buf.st_mtim);
    /*ctime() returns string with \n at the end so we need to replace that \n
    with \0 */
    modtime[strlen(modtime) - 1] = '\0';
    printf(" %s ", modtime);

    printf("%s\n", name);
}



