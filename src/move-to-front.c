#include <stdlib.h>
#include "globals.h"
#include <string.h>

byte* prepare_symbol_table(){
    byte* symbols = malloc_check(malloc(256));
    for(int i = 0; i < 256; i++){
        symbols[i] = i;
    }
    return symbols;
}

int move_to_front_encode(byte* symbols, byte considered){
    // moves considered symbol to the beginning of symbols table; returns index of symbol in symbols
    int indx;
    for(int j = 0; j < 256; j++){
        if(symbols[j] == considered){
            indx = j;
            break;
        }
    }
    memmove(symbols+1, symbols, indx);
    symbols[0] = considered;
    return indx;
}

void move_to_front_decode(byte* symbols, int indx){
    // moves requested index of array to front
    byte symbol = symbols[indx];
    memmove(symbols+1, symbols, indx);
    symbols[0] = symbol;
}

void MTF_encode(byte* THE_BUF, int bytesRead){
    // main encoding function
    byte* symbols = prepare_symbol_table();
    byte considered;
    for(int i = 0; i < bytesRead; i++){
        considered = THE_BUF[i];
        THE_BUF[i] = move_to_front_encode(symbols, considered);
    }
    free(symbols);
}

void MTF_decode(byte* THE_BUF, int bytesRead){
    // main decoding function
    byte* symbols = prepare_symbol_table();
    for(int i = 0; i < bytesRead; i++){
        int indx = THE_BUF[i];
        byte considered = symbols[indx];
        THE_BUF[i] = considered;
        move_to_front_decode(symbols, indx);
    }
    free(symbols);
}