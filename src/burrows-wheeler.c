#include <stdlib.h>
#include <stdio.h>
#include "globals.h"

int cmp(const void* a, const void* b){
    int ia = *(int*)a;
    int ib = *(int*)b;
    for(int i = 0; i < bytesRead; i++){
        if(THE_BUF[ia] > THE_BUF[ib]){
            return 1; 
        }
        else if (THE_BUF[ia] < THE_BUF[ib]){
            return -1;
        }
        ia = (ia + 1) % bytesRead;
        ib = (ib + 1) % bytesRead;
    }
    return 0;
}

void burrows_wheeler_encode(){
    int elems[bytesRead];
    for(int i = 0; i < bytesRead; i++){
        elems[i] = i;
    }
       
    qsort(elems, bytesRead, sizeof(int), cmp);
    
    unsigned char*  NEW_BUF = malloc(bytesRead*sizeof(unsigned char));
    for(int i = 0; i < bytesRead; i++){
        int last_idx = elems[i] - 1 >= 0 ? elems[i]-1 : bytesRead-1;
        NEW_BUF[i] = THE_BUF[last_idx];
    }
}