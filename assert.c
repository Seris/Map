#include <stdio.h>
#include <stdlib.h>

void assert_malloc(void* ptr, char* obj){
    if(ptr == NULL){
        perror("malloc");
        fprintf(stderr, "Can't allocate memory for %s !\nAborting...\n", obj);
    }
}

