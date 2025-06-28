#include "globals.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <move-to-front.h>

void assert_MTF_encode_works(byte* original, byte* expected, int bytes){
    MTF_encode(original, bytes);
    assert(!memcmp(original, expected, bytes));
}

void assert_MTF_decode_works(byte* transformed, byte* expected, int bytes){
    MTF_decode(transformed, bytes);
    assert(!memcmp(transformed, expected, bytes));
}

int main(void){
    int bytes = 6;
    byte orig[] = {'b','a','n','a','n','a'};
    byte* original = malloc_check(malloc(bytes));
    memcpy(original, orig, bytes);

    byte trans[] = {98,98,110,1,1,1};
    byte* transponed = malloc_check(malloc(bytes));
    memcpy(transponed, trans, bytes);

    assert_MTF_encode_works(original, transponed, bytes);

    memcpy(original, orig, bytes);
    assert_MTF_decode_works(transponed, original, bytes);
    
    return 0;
}