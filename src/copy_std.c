#include <stdio.h>
#define BSIZE 16384

void main()
{
    FILE *fin, *fout; // File descriptors are now pointers to a file, not int
    char buf[BSIZE];
    int count;

    /* Now we are using fopen() to open the files. Notice the use of text string
     * "r" and "w" to indicate the open mode either read or write.
     */
    fin = fopen("foo", "r");
    fout = fopen("bar", "w");

    while ((count = fread(buf, 1, BSIZE, fin)) > 0)
    {
        fwrite(buf, 1, count, fout);
    }

    fclose(fin);
    fclose(fout);
}

/*
One of the differences between the low level IO stuff like read() and write()
and the Standard Library IO stuff like fread() and fwrite() is that fwrite()
for example doesn't dive down into the kernel every time you call it. 
It accumulates the output into a buffer and only troubles the kernel when it 
has got a worth amount of data to write.
*/