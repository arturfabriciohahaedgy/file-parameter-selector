#include <gtk/gtk.h>

#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <error.h>

#include "files.h"

int filetype(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void
returndir(void)
{
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
	printf("Current working dir: %s\n", buffer);
    } else {
	perror("getcwd() error");
    }
}

void
resolvepath(char* basepath)
{
    char path[PATH_MAX];
    struct dirent *entry;
    DIR           *folder;
    char          *filename;

    folder = opendir(basepath);

    if (folder == NULL) {
	fprintf(stderr, "ERROR: Could not open selected directory %s: %d", basepath, errno);
    }

    while ((entry = readdir(folder))) {
	filename = entry->d_name;
	if (filename[0] != '.') {
	    strcpy(path, basepath);
	    #ifdef __WIN32
	    strcat(path, "\\");
	    #elif __unix__
	    strcat(path "/");
	    #endif
	    strcat(path, filename);
	    if (filetype(path) == 1) {
		g_print("File: %s\n", filename);
	    } else if (filetype(path) == 0) {
		g_print("Folder: %s\n", filename);
		resolvepath(path);
	    }
	}
    }
    closedir(folder);
}

