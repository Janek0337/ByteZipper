#ifndef NDA_H
#define NDA_H

#include "globals.h"
#include <stdlib.h>
#include "priority_queue.h"
#include "structs.h"

node_darray* node_darray_init(int init_size); 
void node_double_size(node_darray* arr); 
void node_add_to_darray(node_darray* arr, node_t* elem); 
void node_finalize_size(node_darray* arr); 
void node_free(node_darray* arr); 
void node_swap(node_darray* arr, int i, int j);

#endif