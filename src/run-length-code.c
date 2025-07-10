#include <stdlib.h>
#include "globals.h"
#include <math.h>
#include "dynamic_array.h"
#include <stdio.h>

int run_length_code_encode(byte** THE_BUF, int bytesRead){
    /*
    encoding goes as follows:
        - if there is singular character: copy it as it is
        - if there is more than one character in a row: encode it as two of those characters followed by
            how many times is appeared
    */
    darray* NEW_BUF = make_darray(bytesRead);
    int i = 0;
    while(i < bytesRead){
        byte current = (*THE_BUF)[i];
        int count = 1;
        while(i + count < bytesRead && count < 255 && (*THE_BUF)[i+count] == current){
            count++;
        }

        if(count == 1){
            add_to_darray(NEW_BUF, current);
        }
        else{
            add_to_darray(NEW_BUF, current);
            add_to_darray(NEW_BUF, current);
            add_to_darray(NEW_BUF, (byte)count);
        }
        i += count;
    }

    finalize_size(NEW_BUF);
    free(*THE_BUF);
    *THE_BUF = NEW_BUF->array;
    int new_size = NEW_BUF->size;
    free(NEW_BUF);
    return new_size;
}

int run_length_code_decode(byte** THE_BUF, int bytes){
    darray* NEW_BUF = make_darray(bytes);
    int i = 0;
    while(i < bytes){
        byte considered = (*THE_BUF)[i];
        if(i+1<bytes){
            if((*THE_BUF)[i+1] == considered){
                if(!(i+2 < bytes)){
                    throw_fatal_error("Incorrectly encoded input");
                }
                int count = (*THE_BUF)[i+2];
                for(int j = 0; j < count; j++){
                    add_to_darray(NEW_BUF, considered);
                }
                i += 3;
            }
            else{
                add_to_darray(NEW_BUF, considered);
                i++;
            }
        }
        else{
            add_to_darray(NEW_BUF, considered);
            i++;
        }
    }
    finalize_size(NEW_BUF);
    free(*THE_BUF);
    *THE_BUF = NEW_BUF->array;
    int new_size = NEW_BUF->elem_count;
    free(NEW_BUF);
    return new_size;
}