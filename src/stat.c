#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

void main()
{
    struct stat stat_buf;

    stat("foo", &stat_buf);

    printf("Last accessed: %s", ctime((time_t*)&stat_buf.st_atim));
    printf("Last modified: %s", ctime((time_t*)&stat_buf.st_mtim));
    printf("Last changed:  %s", ctime((time_t*)&stat_buf.st_ctim));
}

