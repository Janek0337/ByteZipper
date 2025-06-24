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
    // each number in elems represents how many bytes has the buf been rotated
    int elems[bytesRead];
    for(int i = 0; i < bytesRead; i++){
        elems[i] = i;
    }
       
    qsort(elems, bytesRead, sizeof(int), cmp);
    
    byte*  NEW_BUF = malloc(bytesRead*sizeof(byte));

    // NEW_BUF contains the last column
    for(int i = 0; i < bytesRead; i++){
        int last_idx = elems[i] - 1 >= 0 ? elems[i]-1 : bytesRead-1;
        NEW_BUF[i] = THE_BUF[last_idx];
    }

    // finding which rotation is the one with original first byte at the last column (one move to the left)
    for(int i = 0; i < bytesRead; i++){
        if(elems[i] == 1){
            BWT_start = i;
            break;
        }
    }

    free(THE_BUF);
    THE_BUF = NEW_BUF;
    NEW_BUF = NULL;
}


void burrows_wheeler_decode(){
    // creating first column via count sort and indexing bytes to differentiate between the same ones
    int count[256] = {0};
    int rank_L[bytesRead];
    int rank_F[bytesRead];

    for (int i = 0; i < bytesRead; i++){
        rank_L[i] = count[THE_BUF[i]]++;
    }

    int count_sort[256] = {0};
    for (int i = 0; i < bytesRead; i++) {
        count_sort[THE_BUF[i]]++;
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
            if(THE_BUF[i] == first_col[j] && rank_L[i] == rank_F[j]){
                lf_map[j] = i;
                break;
            }
        }
    }
    int pos = BWT_start;
    byte* NEW_BUF = malloc(bytesRead*sizeof(byte));
    for (int i = 0; i < bytesRead; i++) {
        NEW_BUF[i] = THE_BUF[pos];
        pos = lf_map[pos];
    }
    free(THE_BUF);
    THE_BUF = NEW_BUF;
    NEW_BUF = NULL;
}