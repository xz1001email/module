
#include <stdio.h>

#define FILE_PATH "./"


extern int traverse_directory(char *path);

int main()
{

    traverse_directory(FILE_PATH);

    return 0;
}
