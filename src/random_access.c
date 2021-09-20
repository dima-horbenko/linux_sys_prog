#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// Idea is to store an array of these records in a file.
struct record
{
    int id;
    char name[80];
};

void main()
{
    int fd;
    int size = sizeof(struct record);
    struct record info;

    // We start by opening a file for read and write.
    fd = open("datafile", O_RDWR);

    // We are seeking one record along from the beginning of the file --
    // we're skipping the first record
    lseek(fd, size, SEEK_SET);
    read(fd, &info, size); // We read the second record into memory
    info.id = 99; // Make some modifications to the record

    /* And we want to write it out again. But what we need to remember is that
     * read() advanced the file position pointer so it's actually now pointing 
     * to the third record in a file. So we then seek back, effectively we're 
     * backspacing over the record that we've just read. */
    lseek(fd, -size, SEEK_CUR);

    /* This write() will write modified record back to it's original position
     * in the file */
    write(fd, &info, size);

    close(fd);
}
