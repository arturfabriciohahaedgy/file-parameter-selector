#include <stdlib.h>

#define LEVEL 0
#define NOTLEVEL 99

typedef struct {
    char   **array;
    size_t  used;
    size_t  size;
} Arguments; /* struct used for dynamic array of filenames */

/* filename arrays */
void returndir(void);
void initarguments(Arguments*, size_t);
void freearguments(Arguments*);
int getlevel(char*);

/* path */
void resolvepath(const char*, int, Arguments*);
