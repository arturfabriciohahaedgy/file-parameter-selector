#include <stdlib.h>
#include <stdio.h>

#define LEVEL 0
#define NOTLEVEL 99

typedef struct {
    char   **array;
    size_t  used;
    size_t  size;
} Arguments;

/* filename arrays */
void returndir(void);
void initarguments(Arguments*, size_t);
void freearguments(Arguments*);

/* path */
void resolvepath(const char*, int, Arguments*);
