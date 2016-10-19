#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/disco.h>

int main(int argc, char* argv[]){
    Discotheque d = creer_discotheque_fichier("./database");
    printf("Discothèque chargée D:\n");

    printf("%d artist\n", hash_compter_interpretes(d));

    hash_detruire_discotheque(d);

    return EXIT_SUCCESS;
}

