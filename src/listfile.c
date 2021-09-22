#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

/* Macro for shifting st_mode field of stat structure by 12 bits.
Then we can use this shifted value to iterate through the filetype array
to print the corresponding file type. */
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

    /* We use lstat() here.
    lstat() is identical to stat(), except that if pathname is a symbolic link, 
    then it returns information about the link itself, not the file that 
    the link refers to. */
    if (lstat(argv[1], &stat_buf) < 0) // This time we test for errors
    {
        perror(argv[1]);
        exit(2);
    }

    /* Tricky stuff here! Look how we print-out the file type. 
    We take the st_mode field of the stat structure and shift it right 
    by 12 bits. And just to be certain we mask out everything except the bottom 
    four bits to end up with the number between 0 and 15 to be 
    the array index. */
    printf("%s\nFile type: %s\n", 
            argv[1],
            filetype[(stat_buf.st_mode >> STAT_MODE_TYPE_OFFSET) & 0xF]
            );

    printf("Permissions: %c%c%c%c%c%c%c%c%c\n",
            (stat_buf.st_mode & S_IRUSR) ? 'r' : '-',
            (stat_buf.st_mode & S_IWUSR) ? 'w' : '-',
            (stat_buf.st_mode & S_IXUSR) ? 'x' : '-',
            (stat_buf.st_mode & S_IRGRP) ? 'r' : '-',
            (stat_buf.st_mode & S_IWGRP) ? 'w' : '-',
            (stat_buf.st_mode & S_IXGRP) ? 'x' : '-',
            (stat_buf.st_mode & S_IROTH) ? 'r' : '-',
            (stat_buf.st_mode & S_IWOTH) ? 'w' : '-',
            (stat_buf.st_mode & S_IXOTH) ? 'x' : '-'
            );

}

