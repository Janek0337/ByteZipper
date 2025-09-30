#include "node_dynamic_array.h"
#include "globals.h"
#include <stdlib.h>
#include "priority_queue.h"

node_darray* node_darray_init(int init_size){ 
    node_darray* da = malloc_check(malloc(sizeof(node_darray))); 
    da->size = init_size; 
    da->array = malloc_check(malloc(init_size*sizeof(node_t*))); 
    da->elem_count = 0; 
    return da; 
} 
 
void node_double_size(node_darray* arr){ 
    arr->array = malloc_check(realloc(arr->array, (arr->size)*2*sizeof(node_t*))); 
    arr->size *= 2; 
} 
 
void node_add_to_darray(node_darray* arr, node_t* elem){ 
    if(arr->elem_count == arr->size){ 
        node_double_size(arr); 
    } 
    arr->array[arr->elem_count++] = elem; 
} 
 
void node_finalize_size(node_darray* arr){ 
    arr->array = malloc_check(realloc(arr->array, arr->elem_count*sizeof(node_t*))); 
    arr->size = arr->elem_count; 
} 
 
void node_free(node_darray* arr){ 
    free(arr->array); 
    free(arr); 
} 
 
void node_swap(node_darray* arr, int i, int j){ 
    if(i >= 0 && i < arr->elem_count && j >= 0 && j < arr->elem_count){ 
        node_t* tmp = arr->array[i]; 
        arr->array[i] = arr->array[j]; 
        arr->array[j] = tmp; 
    } 
    else{ 
        throw_fatal_error("Illegal access out of bounds"); 
    } 
}