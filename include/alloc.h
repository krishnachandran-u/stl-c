#include <stdio.h>
#include <stdlib.h>

#define ALLOC(type) ((type*)malloc(sizeof(type)))
#define ALLOC_ARRAY(type, size) ((type*)malloc(sizeof(type) * size))
#define REALLOC_ARRAY(type, ptr, size) ((type*)realloc(ptr, sizeof(type) * size))

#define FREE(ptr) free(ptr)