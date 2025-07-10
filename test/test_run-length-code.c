#include <stdlib.h>
#include <assert.h>
#include "globals.h"
#include <string.h>
#include "run-length-code.h"
#include <stdio.h>

void assert_rlc_encoding_works(byte** original, byte* expected, int bytesRead, int expected_new_size){
    int result_size = run_length_code_encode(&(*original), bytesRead);
    assert(result_size == expected_new_size);
    assert(!memcmp(*original, expected, bytesRead));
}

void assert_rlc_decoding_works(byte** original, byte* expected, int bytesRead, int expected_new_size){
    int result_size = run_length_code_decode(&(*original), bytesRead);
    assert(result_size == expected_new_size);
    assert(!memcmp(*original, expected, result_size));
}


int main(void){
    int old_size = 9;
    byte orig[] = {'b','b','b','a','a','c','d','e','e'};
    byte* original = malloc_check(malloc(old_size));
    memcpy(original, orig, old_size);

    int new_size = 11;
    byte exp[] = {'b','b',3,'a','a',2,'c','d','e','e',2};
    byte* expected = malloc_check(malloc(new_size));
    memcpy(expected, exp, new_size);

    assert_rlc_encoding_works(&original, expected, old_size, new_size);
    
    memcpy(original, orig, old_size);

    assert_rlc_decoding_works(&expected, original, new_size, old_size);
    return 0;
}
