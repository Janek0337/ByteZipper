#include <stdio.h>
#include "burrows-wheeler.h"
#include "globals.h"
#include <stdlib.h>
#include <string.h>
#include "move-to-front.h"
#include "run-length-code.h"
#include "dynamic_array.h"
#include "priority_queue.h"
#define BUFSIZE 400

int main(int argc, char** argv){
    if(argc < 1){
        fprintf(stderr, "Too few arguments\n");
        return 1;
    }
    FILE* in = fopen(argv[1], "rb");
    if(in == NULL){
        fprintf(stderr, "Couldn't open file: \"%s\"\n", argv[1]);
        return 1;
    }
    byte* THE_BUF = malloc_check(malloc(BUFSIZE*sizeof(byte)));
    int bytesRead, BWT_start;
    while((bytesRead = fread(THE_BUF, sizeof(byte), BUFSIZE, in)) > 0){
        BWT_start = burrows_wheeler_encode(&THE_BUF, bytesRead);
        MTF_encode(THE_BUF, bytesRead);
    }

    fclose(in);
    free(THE_BUF);
    return 0;
}