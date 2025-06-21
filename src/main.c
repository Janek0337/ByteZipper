#include <stdio.h>
#include "burrows-wheeler.h"
#include "globals.h"
#include <stdlib.h>
int main(int argc, char** argv){
    if(argc < 1){
        fprintf(stderr, "Za mala liczba argumentow\n");
        return 1;
    }
    FILE* in = fopen(argv[1], "rb");
    if(in == NULL){
        fprintf(stderr, "Nie udalo sie otworzyc pliku \"%s\"\n", argv[1]);
        return 1;
    }
    THE_BUF = malloc(BUFSIZE*sizeof(unsigned char));
    while((bytesRead = fread(THE_BUF, sizeof(unsigned char), BUFSIZE, in)) > 0){
        burrows_wheeler_encode(bytesRead);
    }

    fclose(in);
    return 0;
}