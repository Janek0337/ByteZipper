#ifndef DA_H
#define DA_H
#include "globals.h"

typedef struct{
    byte* array;
    int size;
    int elem_count;
} darray;

darray* make_darray(int init_size);
void add_to_darray(darray* arr, byte elem);
void finalize_size(darray* arr);

#endif