#include <stdlib.h>
#include "priority_queue.h"
#include <assert.h>
#include <stdio.h>
void assert_building_heap_words(node_darray* pq){
    // this also tests whether adding heapUp and heapDown work
    build_heap(pq);
    for(int i = pq->elem_count-1; i > 0; i--){
        if((i-1)/2 >= 0){
            assert(pq->array[i]->count > pq->array[(i-1)/2]->count);
        }
    }
    assert(pq->array[0]->count < pq->array[1]->count && pq->array[0]->count < pq->array[2]->count);
}

void assert_extracting_min_words(node_darray* pq){
    // this also tests whether heapDown works
    node_t* before = extract_min(pq);
    for(int i = 0; i < pq->elem_count-1; i++){
        node_t* after = extract_min(pq);
        assert(before->count < after->count);
        before = after;
    }
}

int main(void){
    node_darray* pq = node_darray_init(8);
    for(int i = 7; i > 0; i--){
        node_t* new = make_node('a',i);
        node_add_to_darray(pq, new);
    }
    assert_building_heap_words(pq);
}