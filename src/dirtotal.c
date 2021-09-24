/* This program prints total size of all files in the current directory */

#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

void main()
{
    DIR *d; // Directory descriptor, it is similar to FILE*.

    /* This is the pointer to dirent structure that holds single directory 
    entry. This sructure is the the return type from the readdir(). */
    struct dirent *entry;

    /* We are going to do a stat() on each of these files to get its size,
    so we need a buffer to return the stat results in. */
    struct stat stat_buf;

    /* And then total is going to accumulate the total of all file sizes. */
    long int total = 0;

    /* We begin by opening a current directory ".". We're keeping things as
    simple as we can here. */
    d = opendir(".");

    /* Perform some minimal error checking. */
    if (d == NULL)
    {
        fprintf(stderr, "Directory cannot be opened.\n");
        exit(1);
    }

    /*
    (1) Now we're going into one of these classic loops doing a perform,
    assign and test reading that directory entries one by one, storing them in
    entry and continuing to loop until readdir() tells us that we've reach the
    end by returning a NULL pointer.

    (2) Each time round we get one file entry,
    we're doing stat() on that file passing in its name from the dirent
    structure and the result will be returned to the stat structure called
    stat_buf. I've made things deliberately easy here by operating on the
    current directory -- we do not need to do concatenating the directory name
    with the file name in order to build the name that we're going to pass
    to stat().

    (3) The stat structure contains the size of the file and we're adding these
    sizes into the running total here. */
    while ((entry = readdir(d)) != NULL) // (1)
    {
        lstat(entry->d_name, &stat_buf);  // (2)
        total += stat_buf.st_size;       // (3)

        printf("%d\t%s\n", stat_buf.st_size, entry->d_name); // For debug
    }

    closedir(d);
    printf("\nTotal size = %d bytes.\n", total);
}