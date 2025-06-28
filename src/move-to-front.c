#include <stdlib.h>
#include "globals.h"
#include <string.h>

void move_to_front(byte* THE_BUF, int bytesRead){
    // create a reference array of symbols where we will move observed byte to front
    byte symbols[256];
    for(int i = 0; i < 256; i++){
        symbols[i] = i;
    }
    byte considered;
    int indx;
    // perform a move to front on a considered byte
    for(int i = 0; i < bytesRead; i++){
        considered = THE_BUF[i];
        for(int j = 0; j < 256; j++){
            if(symbols[j] == considered){
                indx = j;
                break;
            }
        } 

        memmove(symbols+1, symbols, indx);
        symbols[0] = considered;

        //encode
        THE_BUF[i] = indx;
    }
}

void decode_move_to_front(byte* THE_BUF, int bytesRead){
    
}