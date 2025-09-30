#include "byte_dynamic_array.h"
#include "globals.h"
#include <stdlib.h>
#include "priority_queue.h"

byte_darray* byte_darray_init(int init_size){ 
    byte_darray* da = malloc_check(malloc(sizeof(byte_darray))); 
    da->size = init_size; 
    da->array = malloc_check(malloc(init_size*sizeof(byte))); 
    da->elem_count = 0; 
    return da; 
} 
 
void byte_double_size(byte_darray* arr){ 
    arr->array = malloc_check(realloc(arr->array, (arr->size)*2*sizeof(byte))); 
    arr->size *= 2; 
} 
 
void byte_add_to_darray(byte_darray* arr, byte elem){ 
    if(arr->elem_count == arr->size){ 
        byte_double_size(arr); 
    } 
    arr->array[arr->elem_count++] = elem; 
} 
 
void byte_finalize_size(byte_darray* arr){ 
    arr->array = malloc_check(realloc(arr->array, arr->elem_count*sizeof(byte))); 
    arr->size = arr->elem_count; 
} 
 
void byte_free(byte_darray* arr){ 
    free(arr->array); 
    free(arr); 
} 
 
void byte_swap(byte_darray* arr, int i, int j){ 
    if(i >= 0 && i < arr->elem_count && j >= 0 && j < arr->elem_count){ 
        byte tmp = arr->array[i]; 
        arr->array[i] = arr->array[j]; 
        arr->array[j] = tmp; 
    } 
    else{ 
        throw_fatal_error("Illegal access out of bounds"); 
    } 
}