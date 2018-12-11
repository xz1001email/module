#include <stdio.h>
#include <time.h>
#include <stdio.h>






int record_run_time()
{
    char logbuf[200];
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = localtime(&t);
    if (tmp == NULL) {
        perror("localtime");
        return -1;
    }

//#define STR_FORMAT  "run time: %A %a %B %b %C %c"
#define STR_FORMAT  "run time: %F %T"

    if (strftime(logbuf, sizeof(logbuf), STR_FORMAT, tmp) == 0) {
        fprintf(stderr, "strftime returned 0");
        return -1;
    }

    printf("Result string is \"%s\"\n", logbuf);
    return 0;
}


int main()
{
    record_run_time();
    return 0;
}
