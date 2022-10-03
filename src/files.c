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
#include <errno.h>

#include "files.h"

#define FILE 1
#define FOLDER 0
#define BUFFER_SIZE 256

int islevel(char *);
int filetype(const char*);
void addargument(Arguments*, char*);
char *returnlevel(int);

int
islevel(char *argument)
/* returns LEVEL(0) if *argument has the string used to indicate levels, returns FILE(1) if not */
{
    if(strncmp(argument, "||LEVEL_", 8) == LEVEL)
	return LEVEL;
    else
	return NOTLEVEL;
}

int 
filetype(const char *path)
/* return if file on given path is FILE(1) or FOLDER(0) */
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
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
returnlevel(int number)
/* Adds an indication of the dirlevel with a very specific string which no sane person would use to name directories */
{
    const char   *prefix;
    char    charnumber;
    char   *concatbuffer;

    concatbuffer = 0;
    /* allocs non-local memory */
    concatbuffer = (char*)malloc(BUFFER_SIZE * sizeof(char*));

    /* prefix for string concat */
    prefix = "||LEVEL_";
    strcpy(concatbuffer, prefix);
    /* turns int to char */
    charnumber = '0' + number;
    strncat(concatbuffer, &charnumber, 1);
    strcat(concatbuffer, "||");

    return concatbuffer;
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
initarguments(Arguments *a, size_t initialsize)
/* initialize dynamic array */
{
    a->array = malloc(initialsize * sizeof(char*));
    a->used = 0;
    a->size = initialsize;
}

void
freearguments(Arguments *a)
/* free dynamic array */
{
    int us = a->used;

    for (int i = 0; i < us; i++) {
	if((islevel(a->array[i])) == 0)
	    free(a->array[i]);
    }

    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}


void
resolvepath(const char* basepath, int indentlevel, Arguments *arg)
/* recursively parse directories and keep track of hierarchy */
/* TODO: Fix path parsing issue */
{
    char           path[PATH_MAX];
    struct dirent *entry;
    DIR           *folder;
    char          *filename;
    char          *dirlevel;

    dirlevel = returnlevel(indentlevel);
    g_print("dirlevel: %s\n", dirlevel);
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
	    if (filetype(path) == FILE) {
		addargument(arg, filename);
		g_print("File: %s\n", filename);
	    } else if (filetype(path) == FOLDER) {
		g_print("Indent level: %d\n", indentlevel);
		g_print("Folder: %s\n", filename);
		addargument(arg, filename);
		resolvepath(path, indentlevel+1, arg);
		dirlevel = returnlevel(indentlevel);
		g_print("dirlevel: %s\n", dirlevel);
		addargument(arg, dirlevel);
	    }
	}
    }
    closedir(folder);
}

