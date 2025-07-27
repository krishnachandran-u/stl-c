#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "alloc.h"
#include "error.h"
#include "vector.h"

#define VECTOR_INIT_CAPACITY 2

Vector *vector_create() {
    Vector* vec = ALLOC(Vector);
    if (!vec) {
        handle_error("Memory allocation failed. Cannot create vector.", __func__);
    }
    vec->size = 0;
    vec->capacity = VECTOR_INIT_CAPACITY;
    void **data = ALLOC_ARRAY(void*, vec->capacity);
    if (!data) {
        handle_error("Memory allocation failed. Cannot create vector.", __func__);
    }
    vec->data = data;
    return vec;
}

void vector_resize(Vector* vec, size_t new_capacity) {
    void **data = REALLOC_ARRAY(void*, vec->data, new_capacity);
    if (!data) {
        handle_error("Memory allocation failed. Cannot resize.", __func__);
    }
    vec->data = data;
}

void vector_push_back(Vector* vec, void* ptr) {
    if (vec->size >= vec->capacity) {
        vector_resize(vec, (vec->capacity == 0)? 1: (vec->capacity << 1));
    } 
    vec->data[vec->size++] = ptr;
}

bool vector_empty(Vector* vec) {
    if (!vec) {
        handle_error("Cannot operate on a NULL vector.", __func__);
    }
    return vec->size == 0;
}

void *vector_pop_back(Vector* vec) {
    void* retval = vector_get(vec, vec->size - 1);
    vec->size -= 1;
    return retval;
}

void *vector_get(Vector* vec, int index) {
    if (vector_empty(vec)) {
        handle_error("Cannot access an element from an empty vector.", __func__);
    } else if (index < 0 || index >= vec->size) {
        handle_error("Index out of bounds.", __func__);
    } else return vec->data[index];
}

void vector_clear(Vector* vec) {
    vec->size = 0;
}

void vector_free(Vector* vec) {
    for (size_t i = 0; i < vec->size; ++i) {
        free(vec->data[i]);
    }
    free(vec->data);
    free(vec);
}