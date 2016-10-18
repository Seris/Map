#include <stdio.h>
#include <stdlib.h>
#include <assert_malloc.h>

void assert_malloc(void* ptr, const char* target){
    if(ptr == NULL){
        perror("malloc");
        fprintf(stderr, "failed to allocate memory for %s\naborting...\n", target);
        exit(EXIT_FAILURE);
    }
}
