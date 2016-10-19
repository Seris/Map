#include <types/disco.h>

Discotheque (*creer_discotheque)(void);
Discotheque (*inserer)(Discotheque, Titre, Interprete, Label, Date, Style);
Discotheque (*supprimer)(Discotheque, Titre);
Discotheque (*rechercher)(Discotheque, Titre);
int         (*compter_interpretes)(Discotheque);
void        (*afficher)(Discotheque);
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
      //afficher                = &hash_afficher;
        detruire_discotheque    = &hash_detruire_discotheque;
        break;

        case METHODE_ARBRE:
        creer_discotheque       = &arbre_creer_discotheque;
        inserer                 = &arbre_inserer;
        supprimer               = &arbre_supprimer;
        rechercher              = &arbre_rechercher;
        compter_interpretes     = &arbre_compter_interpretes;
        afficher                = &arbre_afficher;
        detruire_discotheque    = &arbre_detruire_discotheque;
        break;
/*
        case METHODE_LISTE:
        creer_discotheque       = &liste_creer_discotheque;
        inserer                 = &liste_inserer;
        supprimer               = &liste_supprimer;
        rechercher              = &liste_rechercher;
        compter_interpretes     = &liste_compter_interpretes;
        afficher                = &liste_afficher;
        detruire_discotheque    = &liste_detruire_discotheque;
        break;
*/
        default:
        status = 0;
    }

    return status;
}

