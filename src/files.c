#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "files.h"

int filetype(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void
returndir(void) {
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
	printf("Current working dir: %s\n", buffer);
    } else {
	perror("getcwd() error");
    }
}

void
resolvepath(char* path)
{
    struct dirent *entry;
    DIR           *folder;
    char          *filename;

    folder = opendir(path);

    while ((entry = readdir(folder))) {
	filename = entry->d_name;
	if (filename[0] != '.') {
	    printf("type: %d", filetype(filename));
	    if (filetype(filename) == 1) {
		printf("File: %s\n", filename);
	    }
	}
    }
    closedir(folder);
}

