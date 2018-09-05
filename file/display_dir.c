#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

int getFileId(char *filename)
{
    printf("filename = %s\n", filename);
    
    return strtol(filename, NULL, 10);
}



int printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    int maxid = 0;
    int tmpid = 0;

    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "Can`t open directory %s\n", dir);
        return -1;
    }

    chdir(dir);
    while ((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode)) {
#if 0
            if (strcmp(entry->d_name, ".") == 0 || 
                    strcmp(entry->d_name, "..") == 0 )  
                continue;
            printf("    %*s%s/\n", depth, "", entry->d_name);
            printdir(entry->d_name, depth+4);
#endif
        } else{
            printf("%*s%s\n", depth, "", entry->d_name);
            tmpid = getFileId(entry->d_name);
            maxid = maxid > tmpid ? maxid : tmpid;
            printf("%*s%d\n", depth, "", maxid);
        }
    }
    chdir("..");
    closedir(dp);

    return maxid;
}


int main(int argc, char *argv[])
{
    char *topdir = "    .";
    if (argc >= 2)
        topdir = argv[1];

    printf("Directory scan of %s\n", topdir);
    printdir(topdir, 0);
    printf("done.\n");
    exit(0);
}


