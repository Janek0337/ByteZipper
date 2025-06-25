#include "globals.h"
#include <stdlib.h>
#include <stdio.h>

void* malloc_check(void* ptr){
    if(ptr == NULL){
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}