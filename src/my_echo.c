/* This program just prints its arguments, like echo command */

#include <stdio.h>

void main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
}










