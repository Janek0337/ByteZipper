#include "globals.h"
#include <stdlib.h>
#include "dynamic_array.h"

darray* make_darray(int init_size){
    darray* da = malloc_check(malloc(sizeof(darray)));
    da->size = init_size;
    da->array = malloc_check(malloc(init_size*sizeof(byte)));
    da->elem_count = 0;
    return da;
}

void double_size(darray* arr){
    arr->array = malloc_check(realloc(arr->array, (arr->size)*2*sizeof(byte)));
    arr->size *= 2;
}

void add_to_darray(darray* arr, byte elem){
    if(arr->elem_count == arr->size){
        double_size(arr);
    }
    arr->array[arr->elem_count++] = elem;
}

void finalize_size(darray* arr){
    malloc_check(realloc(arr->array, arr->elem_count));
    arr->size = arr->elem_count;
}