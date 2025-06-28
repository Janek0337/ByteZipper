#ifndef MTF_H
#define MTF_H
#include "globals.h"

void MTF_encode(byte* THE_BUF, int bytesRead);
void MTF_decode(byte* THE_BUF, int bytesRead);
int move_to_front_decode (byte* symbols, int indx);
int move_to_front_encode(byte* symbols, byte considered);
byte* prepare_symbol_table();

#endif