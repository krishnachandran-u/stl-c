#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void handle_error(const char *message, const char *function_name) {
    fprintf(stderr, "Error in %s: %s\n", function_name, message);
    exit(1);
}
