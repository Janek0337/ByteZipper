#include <stdlib.h>
#include "globals.h"
#include <math.h>

int run_length_code_encode(byte** THE_BUF, int bytesRead){
    /*
    encoding goes as follows:
        - if there is singular character: copy it as it is
        - if there is more than one character in a row: encode it as two of those characters followed by
            how many times is appeared
    */
    int new_size = 0;
    byte* NEW_BUF = malloc_check(malloc(ceil(3*bytesRead/2)));
    int count;
    byte considered, current;
    for(int i = 0; i < bytesRead; i++){
        // i for iterating over THE_BUF (original buffer), new_size to access to NEW_BUF (new buffer)
        considered = (*THE_BUF)[i];
        if (i + 1 < bytesRead && (*THE_BUF)[i+1] != considered){
            NEW_BUF[new_size++] = considered;
        }
        else{
            count = 0;
            current = (*THE_BUF)[i];
            while(current == considered && i + count < bytesRead){
                count++;
                current = (*THE_BUF)[i+count];
            }
            NEW_BUF[new_size++] = considered;
            NEW_BUF[new_size++] = considered;
            NEW_BUF[new_size++] = count;
            i += count-1;
        } 
    }
    NEW_BUF = malloc_check(realloc(NEW_BUF, new_size*sizeof(byte)));
    free(*THE_BUF);
    *THE_BUF = NEW_BUF;
    NEW_BUF = NULL;
    return new_size;
}