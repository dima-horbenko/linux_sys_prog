#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#define STAT_MODE_TYPE_OFFSET 12

char *filetype[] = {
    "unknown",
    "FIFO pipe",
    "Character device",
    "unknown",
    "Directory",
    "unknown",
    "Block device",
    "unknown",
    "File",
    "unknown",
    "Symlink",
    "unknown",
    "Socket"
};


void main(int argc, char *argv[])
{
    struct stat stat_buf;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: listfile <filename>\n");
        exit(1);
    }

    if (stat(argv[1], &stat_buf) < 0)
    {
        perror(argv[1]);
        exit(2);
    }

    printf("%s\nFile type: %s\n", 
            argv[1],
            filetype[(stat_buf.st_mode >> STAT_MODE_TYPE_OFFSET) & 0xF]);

}

