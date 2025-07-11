#include <stdlib.h>
#include "priority_queue.h"
#include <assert.h>

void assert_building_heap_words(node_darray* pq){
    build_heap(pq);
    for(int i = pq->elem_count; i >= 0; i--){
        assert(pq->array[i]->count > pq->array[(i-1)/2]->count);
    }
}

int main(void){
    node_darray* pq = node_darray_init(8);
    for(int i = 5; i > 0; i--){
        node_t* new = make_node('a',i);
        node_add_to_darray(pq, new);
    }
    assert_building_heap_words(pq);
}