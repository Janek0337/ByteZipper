#ifndef STRUCTS_H
#define STRUCTS_H
#include "globals.h"

typedef struct nodzik{
    byte symbol;
    int count;
    struct nodzik* left;
    struct nodzik* right;
} node_t;

typedef struct{
    byte* BUF;
    int bytesRead;
} context;

typedef struct { 
    node_t** array; 
    int size; 
    int elem_count; 
} node_darray;

typedef struct { 
    byte* array; 
    int size; 
    int elem_count; 
} byte_darray; 

#endif