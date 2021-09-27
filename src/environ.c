/* This program prints out all  environment variables */

#include <stdio.h>

extern char **environ;
/* INVESTIGATE ME: extern char *environ[] doesn't behave the same way!
Does this mean that (char **p) and (char *p[]) are not the same thing ? */

void main(int argc, char *argv[])
{

    char **p = environ;

    while (*p != NULL)
    {
        printf("%s\n", *p);
        p++;
    }
}

















