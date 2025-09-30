#ifndef RLC_H
#define RLC_H

#include "globals.h"

int run_length_code_encode(byte** THE_BUF, int bytesRead);
int run_length_code_decode(byte** THE_BUF, int bytesRead);

#endif