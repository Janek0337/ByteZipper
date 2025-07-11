#ifndef RLC_H
#define RLC_H

#include "globals.h"
#include "dynamic_array.h"

int run_length_code_encode(byte** THE_BUF, int bytesRead);
int run_length_code_decode(byte** THE_BUF, int bytesRead);
DECLARE_DYNAMIC_ARRAY_FOR_TYPE(byte,byte);
#endif