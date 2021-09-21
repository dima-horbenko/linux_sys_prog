#include <stdio.h>

void main()
{
    /* This function is like printf() except that its first parameter is 
     * file descriptor (FILE*), stderr stream in this case.
     * It prints error message in the stderr and exits with status 15.
     * You can check last program exit status with "echo $?" command.
     */
    fprintf(stderr, "Error message!\n");
}
