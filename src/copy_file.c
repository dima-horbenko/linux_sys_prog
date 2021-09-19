/* This program uses unbuffered IO */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For read(), write() to work

#define BSIZE 16384

void main()
{
    int fin, fout; // Input and output file handles
    char buf[BSIZE];
    int count;

    // Open existing file "source_file" for read only (file name is hardcoded)
    // Check if we open file successfully
    if ((fin = open("source_file", O_RDONLY)) < 0) // System calls return -1 on failure
    {
        perror("source_file"); // Routine to print error message based on errno value
        exit(1);
    }

    // Creating new file "dest_file" and open it for write only
                                                    // 0644 means octal system!
    if ((fout  = open("dest_file", O_WRONLY | O_CREAT, 0644)) < 0)
    {
        perror("dest_file");
        exit(2);
    }

    /* All exciting stuff happens in this loop.
     * We are reading BSIZE bytes from the input file into the buffer, 
     * assigning count of bytes that given back to the count variable and 
     * test to see if it's positive. If it is, in the body of the loop we 
     * write that number of bytes into the output file. */
    while ((count = read(fin, buf, BSIZE)) > 0)
    {
        write(fout, buf, count);
    }

    close(fin);
    close(fout);
}




























