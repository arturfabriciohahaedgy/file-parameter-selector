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

#define FILE 1
#define FOLDER 0

int filetype(const char*);
void addargument(Arguments*, char*);
char *addlevel(int);

int 
filetype(const char *path)
/* return if file on given path is FILE(1) or FOLDER(0) */
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void
returndir(void)
/* TODO: Remove function after project is finalized */
{
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
	printf("Current working dir: %s\n", buffer);
    } else {
	perror("getcwd() error");
    }
}

void
addargument(Arguments *arg, char *insertvalue)
/* Adds *insertvalue in argument array, double the size of the array if it is at max */
{
    if (arg->used == arg->size) {
	arg->size *= 2;
	arg->array = realloc(arg->array, arg->size * sizeof(char*));
    }
    arg->array[arg->used++] = insertvalue;
}

char *
addlevel(int number)
/* Adds an indication of the dirlevel with a very specific string which no sane person would use to name directories */
{
    char   *prefix;
    char   *stringnumber;
    char    charnumber;
    size_t  sizenumber;
    size_t  sizeprefix;
    /* result of concatenation using memcpy() */
    char   *concatenated;

    /* prefix for string concat */
    prefix = "||LEVEL_";
    /* turns int to char */
    charnumber = '0' + number;
    /* really dumb solution but... it is what it is, it isn't what it isn't */
    stringnumber = &charnumber;

    /* gets size of chars */
    sizeprefix = sizeof(prefix);
    sizenumber = sizeof(stringnumber);

    concatenated = malloc(sizenumber + sizeprefix + 1);
    if (!concatenated)
	return concatenated;

    memcpy(concatenated, prefix, sizeprefix);
    memcpy(concatenated + sizeprefix, stringnumber, sizenumber + 1);

    /* printf("concat: %s\n", concatenated); */

    return concatenated;
}

void
resolvepath(char* basepath, int indentlevel, Arguments *arg)
/* recursively parse directories and keep track of hierarchy */
/* TODO: Fix path parsing issue */
{
    char           path[PATH_MAX];
    struct dirent *entry;
    DIR           *folder;
    char          *filename;
    char          *dirlevel;

    dirlevel = addlevel(indentlevel);
    addargument(arg, dirlevel);

    folder = opendir(basepath);
    if (folder == NULL) {
	fprintf(stderr, "ERROR: Could not open selected directory %s: %d", basepath, errno);
    }

    while ((entry = readdir(folder))) {
	filename = entry->d_name;
	if (filename[0] != '.') {
	    strcpy(path, basepath);
	    /* if it's on windows, concat the "\" path separator, if on Linux/BSD use "/" */
	    #ifdef __WIN32
	    strcat(path, "\\");
	    #elif __unix__
	    strcat(path, "/");
	    #endif 
	    strcat(path, filename);
	    g_print("sdasdasdsad: %s\n", path);
	    if (filetype(path) == FILE) {
		addargument(arg, filename);
		/* g_print("File: %s\n", filename); */
	    } else if (filetype(path) == FOLDER) {
		/* g_print("Indent level: %d\n", indentlevel); */
		/* g_print("Folder: %s\n", filename); */
		addargument(arg, filename);
		resolvepath(path, indentlevel+1, arg);
	    }
	}
    }
    closedir(folder);
}

