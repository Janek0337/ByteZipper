#include <stdio.h>
#include "burrows-wheeler.h"
#include "globals.h"
#include <stdlib.h>
int main(){
    FILE* in = fopen("./dane.txt", "rb");
    if(in == NULL){
        return 1;
    }
    THE_BUF = malloc(BUFSIZE*sizeof(unsigned char));
    while((bytesRead = fread(THE_BUF, sizeof(unsigned char), BUFSIZE, in)) > 0){
        burrows_wheeler_encode(bytesRead);
    }

    fclose(in);
    return 0;
}