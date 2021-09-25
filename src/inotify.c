/* 03_09
Monitor specified files for changes using inotify and log changes to file */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <limits.h>

/* A buffer big enough to read 100 events in one go */
#define BUFSIZE (100 * (sizeof(struct inotify_event) +  NAME_MAX + 1))

void main()
{
    /* Descriptor of the log file */
    FILE *fout;
    char eventbuf[BUFSIZE];
    int n;
    char *p;
    struct inotify_event *event;


    /* Descriptor of the file that contains a list of monitored files*/
    FILE *fconfig;
    /* Open the config file for reading and check for errors*/
    if ((fconfig = fopen("monitor.conf", "r")) == NULL)
    {
        fprintf(stderr, "Unable to open the file.\n");
        exit(1);
    }

    char watchname[PATH_MAX];
    struct stat sb;
    int watchfd;
    int notifyfd = inotify_init();
    /* Here we hold the names of the watched files,
    indexed by the watch descriptor */
    char watchednames[100][NAME_MAX + 1];
    /* Read all watched file names from config file */
    while (fgets(watchname, sizeof(watchname), fconfig) != NULL)
    {
        if (stat(watchname, &sb) < 0)
        {
            printf("Cannot stat file %s. Ignored.\n", watchname);
            continue;
        }

        if (S_ISREG(sb.st_mode))
        {
            /* Regular file, so add to watchlist */
            if ((watchfd = inotify_add_watch(notifyfd, watchname, IN_MODIFY | IN_DELETE_SELF)) < 0)
            {
                printf("Error! Watch for %s not added.\n", watchname);
            }
            else
            {

            }
        }
    }


}















