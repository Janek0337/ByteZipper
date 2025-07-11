#ifndef DA_H
#define DA_H

#include "globals.h"
#include <stdlib.h>

#define DECLARE_DYNAMIC_ARRAY_FOR_TYPE(TYPE, PREFIX) \
typedef struct { \
    TYPE* array; \
    int size; \
    int elem_count; \
} PREFIX##_darray; \
\
PREFIX##_darray* PREFIX##_darray_init(int init_size); \
void PREFIX##_double_size(PREFIX##_darray* arr); \
void PREFIX##_add_to_darray(PREFIX##_darray* arr, TYPE elem); \
void PREFIX##_finalize_size(PREFIX##_darray* arr); \
void PREFIX##_free(PREFIX##_darray* arr); \
void PREFIX##_swap(PREFIX##_darray* arr, int i, int j);


#define DEFINE_DYNAMIC_ARRAY_FOR_TYPE(TYPE, PREFIX) \
PREFIX##_darray* PREFIX##_darray_init(int init_size){ \
    PREFIX##_darray* da = malloc_check(malloc(sizeof(PREFIX##_darray))); \
    da->size = init_size; \
    da->array = malloc_check(malloc(init_size*sizeof(TYPE))); \
    da->elem_count = 0; \
    return da; \
} \
 \
void PREFIX##_double_size(PREFIX##_darray* arr){ \
    arr->array = malloc_check(realloc(arr->array, (arr->size)*2*sizeof(TYPE))); \
    arr->size *= 2; \
} \
 \
void PREFIX##_add_to_darray(PREFIX##_darray* arr, TYPE elem){ \
    if(arr->elem_count == arr->size){ \
        PREFIX##_double_size(arr); \
    } \
    arr->array[arr->elem_count++] = elem; \
} \
 \
void PREFIX##_finalize_size(PREFIX##_darray* arr){ \
    arr->array = malloc_check(realloc(arr->array, arr->elem_count*sizeof(TYPE))); \
    arr->size = arr->elem_count; \
} \
 \
void PREFIX##_free(PREFIX##_darray* arr){ \
    free(arr->array); \
    free(arr); \
} \
 \
void PREFIX##_swap(PREFIX##_darray* arr, int i, int j){ \
    if(i >= 0 && i < arr->elem_count && j >= 0 && j < arr->elem_count){ \
        TYPE tmp = arr->array[i]; \
        arr->array[i] = arr->array[j]; \
        arr->array[j] = tmp; \
    } \
    else{ \
        throw_fatal_error("Illegal access out of bounds"); \
    } \
}
#endif