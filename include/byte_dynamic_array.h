#ifndef BDA_H
#define BDA_H

#include "globals.h"
#include <stdlib.h>
#include "priority_queue.h"
#include "structs.h"

byte_darray* byte_darray_init(int init_size); 
void byte_double_size(byte_darray* arr); 
void byte_add_to_darray(byte_darray* arr, byte elem); 
void byte_finalize_size(byte_darray* arr); 
void byte_free(byte_darray* arr); 
void byte_swap(byte_darray* arr, int i, int j);

#endif