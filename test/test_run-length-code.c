#include <stdlib.h>
#include <assert.h>
#include "globals.h"
#include <string.h>
#include "run-length-code.h"

void assert_rlc_encoding_works(byte** original, byte* expected,int bytesRead, int expected_new_size){
    int result_size = run_length_code_encode(&(*original), bytesRead);
    assert(!memcmp(*original, expected, bytesRead));
    assert(result_size == expected_new_size);
}

int main(void){
    int old_size = 10;
    byte orig[] = {'b','b','b','a','c','c','d','e','f','f'};
    byte* original = malloc_check(malloc(old_size));
    memcpy(original, orig, old_size);

    int new_size = 12;
    byte exp[] = {'b','b',3,'a','c','c',2,'d','e','f','f',2};
    byte* expected = malloc_check(malloc(new_size));
    memcpy(expected, exp, new_size);

    assert_rlc_encoding_works(&original, expected, old_size, new_size);
    return 0;
}