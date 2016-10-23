#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/disco.h>
#include <types/disco_intern.h>

Discotheque (*creer_discotheque)(void);
Discotheque (*inserer)(Discotheque, Titre, Interprete, Label, Date, Style);
Discotheque (*supprimer)(Discotheque, Titre);
Discotheque (*rechercher)(Discotheque, Titre);
int         (*album_present)(Discotheque);
int         (*compter_interpretes)(Discotheque);
void        (*afficher)(Discotheque);
void        (*afficher_album)(Discotheque);
void        (*detruire_discotheque)(Discotheque);

int discotheque_methode(methode_t method){
    int status = 1;
    switch(method){
        case METHODE_HASH:
        creer_discotheque       = &hash_creer_discotheque;
        inserer                 = &hash_inserer;
        supprimer               = &hash_supprimer;
        rechercher              = &hash_rechercher;
        compter_interpretes     = &hash_compter_interpretes;
        album_present           = &hash_album_present;
        afficher_album          = &hash_afficher_album;
        afficher                = &hash_afficher;
        detruire_discotheque    = &hash_detruire_discotheque;
        break;

        case METHODE_ARBRE:
        creer_discotheque       = &arbre_creer_discotheque;
        inserer                 = &arbre_inserer;
        supprimer               = &arbre_supprimer;
        rechercher              = &arbre_rechercher;
        compter_interpretes     = &arbre_compter_interpretes;
        album_present           = &arbre_album_present;
        afficher                = &arbre_afficher;
        afficher_album          = &arbre_afficher;
        detruire_discotheque    = &arbre_detruire_discotheque;
        break;

        case METHODE_LISTE:
        creer_discotheque       = &liste_creer_discotheque;
        inserer                 = &liste_inserer;
        supprimer               = &liste_supprimer;
        rechercher              = &liste_rechercher;
        compter_interpretes     = &liste_compter_interpretes;
        album_present           = &arbre_album_present;
        afficher_album          = &liste_afficher;
        afficher                = &liste_afficher;
        detruire_discotheque    = &liste_detruire_discotheque;
        break;

        default:
        status = 0;
    }

    return status;
}


int charger_discotheque_fichier(char* file, Discotheque* d){
    FILE* db_fd = fopen(file, "r"); 
    char* line;
    music_t music;
    int status = 0;
    Discotheque disco = *d;

    if(db_fd != NULL){
        status = 1;
        fscanf(db_fd, "%m[^\n]", &line);
        while(line != NULL) { 
            music.title  = strtok(line, "|");
            music.author = strtok(NULL, "|");
            music.label  = strtok(NULL, "|");
            music.date   = strtok(NULL, "|");
            music.style  = strtok(NULL, "|");

            disco = inserer(disco,
                music.title,
                music.author,
                music.label,
                music.date,
                music.style);

            free(line);

            fseek(db_fd, 1, SEEK_CUR);
            fscanf(db_fd, "%m[^\n]", &line);
        }

        free(line);
        fclose(db_fd);
    }

    *d = disco;

    return status;
}

