#include "globals.h"
#include <stdlib.h>
#include <stdio.h>

void* malloc_check(void* ptr){
    if(ptr == NULL){
        throw_fatal_error("Memory allocation error\n");
    }
    return ptr;
}

void throw_fatal_error(const char message[]){
    fputs(stderr, message);
    exit(EXIT_FAILURE);
}