#ifndef PQ_H
#define PQ_H
#include "globals.h"
#include "dynamic_array.h"
#include "node_dynamic_array.h"
#include "structs.h"

node_t* make_node(byte byte, int count);
void heapUp(node_darray* arr);
void add_to_queue(node_darray* arr, node_t* elem);
node_t* extract_min(node_darray* arr);
void build_heap(node_darray* arr);
void heapDown(node_darray* arr, int start_indx);
#endif