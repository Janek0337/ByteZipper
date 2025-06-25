#ifndef BW_H
#define BW_H
#include "globals.h"
int burrows_wheeler_encode(byte** BUF, int bytesRead);
void burrows_wheeler_decode(byte** BUF, int bytesRead, int BWT_start);

typedef struct{
    byte* BUF;
    int bytesRead;
} context;

#endif