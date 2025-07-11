#include <stdlib.h>
#include "globals.h"
#include "dynamic_array.h"
#include "priority_queue.h"

node_t* make_node(byte byte, int count){
    node_t* elem = malloc_check(malloc(sizeof(node_t)));
    elem->count = count;
    elem->symbol = byte;
    elem->left = NULL;
    elem->right = NULL;
    return elem;
}

void heapUp(node_darray* arr){
    int i = arr->elem_count-1;
    while(i > 0 && arr->array[(i-1)/2]->count > arr->array[i]->count){
        node_swap(arr, i, (i-1)/2);
        i = (i-1)/2;
    }
}

void heapDown(node_darray* arr, int start_indx){
    int i = start_indx;
    while(2*i+1 < arr->elem_count){
        int min_indx = i;
        if(arr->array[2*i+1]->count < arr->array[min_indx]->count) min_indx = 2*i+1;
        if(2*i+2 < arr->elem_count){
            if(arr->array[2*i+2]->count < arr->array[min_indx]->count) min_indx = 2*i+2;
        }
        if (min_indx != i){
            node_swap(arr, i, min_indx);
            i = min_indx;
        }
        else{
            break;
        }
    }
}

void add_to_queue(node_darray* arr, node_t* elem){
    node_add_to_darray(arr, elem);
    heapUp(arr);
}

node_t* extract_min(node_darray* arr){
    node_t* min = arr->array[0];
    node_swap(arr, 0, arr->elem_count-1);
    arr->elem_count--;
    heapDown(arr, 0);
    return min;
}

void build_heap(node_darray* arr){
    for(int i = (arr->elem_count-2)/2; i > 0; i--){
        heapDown(arr, i);
    }
}
