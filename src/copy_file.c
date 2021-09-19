#include <fcntl.h>
#include <stdlib.h>

#define BSIZE 16384

void main()
{
    int fin, fout; // Input and output file handles
    char buf[BSIZE];
    int count;

    if ((fin = open("foo", O_RDONLY)) < 0) {
        perror("foo");
        exit(1);
    }

}




























