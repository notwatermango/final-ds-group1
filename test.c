#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char* dir, int depth)
{
    DIR* dp;
    struct dirent* entry;
    struct stat statbuf;
    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    chdir("..");
    closedir(dp);
}

int main()
{
    printf("Directory scan of /images:\n");
    printdir("./test", 0);
    printf("done.\n");
    exit(0);
}