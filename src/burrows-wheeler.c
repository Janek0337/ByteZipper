#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
#include "burrows-wheeler.h"

int cmp(const void* a, const void* b, void* arg){
    int ia = *(int*)a;
    int ib = *(int*)b;
    context* c = (context*)arg;
    for(int i = 0; i < c->bytesRead; i++){
        if(c->BUF [ia] > c->BUF[ib]){
            return 1; 
        }
        else if (c->BUF[ia] < c->BUF[ib]){
            return -1;
        }
        ia = (ia + 1) % c->bytesRead;
        ib = (ib + 1) % c->bytesRead;
    }
    return 0;
}

int burrows_wheeler_encode(byte** THE_BUF, int bytesRead){ // modified *THE_BUF to be transformed data
    // each number in elems represents how many bytes has the buf been rotated
    int elems[bytesRead];
    for(int i = 0; i < bytesRead; i++){
        elems[i] = i;
    }
    context* c = malloc_check((sizeof(context)));
    c->BUF = *THE_BUF;
    c->bytesRead = bytesRead;   
    qsort_r(elems, bytesRead, sizeof(int), cmp, c);
    
    free(c);
    c = NULL;
    byte* NEW_BUF = malloc_check((bytesRead*sizeof(byte)));

    // NEW_BUF contains the last column
    for(int i = 0; i < bytesRead; i++){
        int last_idx = elems[i] - 1 >= 0 ? elems[i]-1 : bytesRead-1;
        NEW_BUF[i] = (*THE_BUF)[last_idx];
    }

    // finding which rotation is the one with original first byte at the last column (one move to the left)
    int BWT_start;
    for(int i = 0; i < bytesRead; i++){
        if(elems[i] == 1){
            BWT_start = i;
            break;
        }
    }

    free(*THE_BUF);
    *THE_BUF = NEW_BUF;
    NEW_BUF = NULL;
    return BWT_start;
}


void burrows_wheeler_decode(byte** THE_BUF, int bytesRead, int BWT_start){
    /*
    modifies *THE_BUF to become the original data
    BWT_start is index of the byte that was ofiginally the first one
    */
    
    // creating first column via count sort and indexing bytes to differentiate between the same ones
    int count[256] = {0};
    int rank_L[bytesRead];
    int rank_F[bytesRead];

    for (int i = 0; i < bytesRead; i++){
        rank_L[i] = count[(*THE_BUF)[i]]++;
    }

    int count_sort[256] = {0};
    for (int i = 0; i < bytesRead; i++) {
        count_sort[(*THE_BUF)[i]]++;
    }

    byte first_col[bytesRead]; 
    int place_idx = 0;
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < count_sort[i]; j++){
            first_col[place_idx++] = (byte)i;
        }
    }
    int count_F[256] = {0};
    for(int i = 0; i < bytesRead; i++){
        rank_F[i] = count_F[first_col[i]]++;
    }

    //creating mapping of byes in last and first columns
    int lf_map[bytesRead];
    for(int i = 0; i < bytesRead; i++){
        for(int j = 0; j < bytesRead; j++){
            if((*THE_BUF)[i] == first_col[j] && rank_L[i] == rank_F[j]){
                lf_map[j] = i;
                break;
            }
        }
    }
    int pos = BWT_start;
    byte* NEW_BUF = malloc_check((bytesRead*sizeof(byte)));
    for (int i = 0; i < bytesRead; i++) {
        NEW_BUF[i] = (*THE_BUF)[pos];
        pos = lf_map[pos];
    }
    
    free(*THE_BUF);
    *THE_BUF = NEW_BUF;
    NEW_BUF = NULL;
}