#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/disco.h>

int main(int argc, char* argv[]){
    discotheque_methode(METHODE_ARBRE);
   
    Discotheque d = creer_discotheque_fichier("./database");
    printf("Discothèque chargée D:\n");

    printf("%d artist\n", compter_interpretes(d));

    //detruire_discotheque(d);

    return EXIT_SUCCESS;
}

