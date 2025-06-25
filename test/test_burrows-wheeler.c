#include <assert.h>
#include <stdlib.h>
#include <burrows-wheeler.h>
#include <string.h>

void assert_transform_works(byte* original, byte* expected, int bytes, int expectedIndx){
    int result = burrows_wheeler_encode(&original, bytes);
    assert(!memcmp(original, expected, bytes));
    assert(result == expectedIndx);
}

void assert_reversed_transform_works(byte* transform, byte* original, int bytes, int indx){
    burrows_wheeler_decode(&transform, bytes, indx);
    assert(!memcmp(transform, original, bytes));
}

int main(void){
    int bytes = 9;
    byte* original = malloc(bytes);
    byte orig[] = {'b','e','n','i','o','w','s','k','i'};
    memcpy(original, orig, bytes);

    byte* expected = malloc(bytes);
    byte exp[] = {'i','b','k','n','s','e','i','w','o'};
    memcpy(expected, exp, bytes);

    int expectedIndx = 1;
    assert_transform_works(original, expected, bytes, expectedIndx);
    assert_reversed_transform_works(expected, original, bytes, expectedIndx);
    return 0;
}