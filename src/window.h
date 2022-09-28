#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char   **array;
    size_t  used;
    size_t  size;
} Arguments;

int initialize();
