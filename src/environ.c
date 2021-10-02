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

/*
Investigation complete.
There actually is a difference between (char **p) and (char *p[]). This
difference lays in the constantness of these two pointers.

(char *p[])
acts as a reference or constant pointer so you cannot modify it,
when you try to code p++, its compile error because ++ is destructive operator,
it contains assignment it it, so compiler doesn't let you to do p++ to access
the next array element.

(char **p)
acts as a regular ponter. This means that you can modify it and use p++ to
access to the next array element.
*/
















