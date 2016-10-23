#ifndef TYPES_DISCO_INTERN_H
#define TYPES_DISCO_INTERN_H

#include <types/disco.h>

/**
 * Hash Table Prototypes
 **/
Discotheque hash_creer_discotheque(void);
Discotheque hash_inserer(Discotheque, Titre, Interprete, Label, Date, Style);
Discotheque hash_supprimer(Discotheque, Titre);
Discotheque hash_rechercher(Discotheque, Titre);
int         hash_compter_interpretes(Discotheque);
int         hash_album_present(Discotheque);
void        hash_afficher(Discotheque);
void        hash_afficher_album(Discotheque);
void        hash_detruire_discotheque(Discotheque);

/**
 * Tree Prototypes
 **/
Discotheque arbre_creer_discotheque();
Discotheque arbre_inserer(Discotheque, Titre, Interprete, Label, Date, Style);
Discotheque arbre_supprimer(Discotheque, Titre);
Discotheque arbre_rechercher(Discotheque, Titre);
int         arbre_compter_interpretes(Discotheque);
int         arbre_album_present(Discotheque);
void        arbre_afficher(Discotheque);
void        arbre_detruire_discotheque(Discotheque);

/**
 * List Prototypes
 **/
Discotheque liste_creer_discotheque();
Discotheque liste_inserer(Discotheque, Titre, Interprete, Label, Date, Style);
Discotheque liste_supprimer(Discotheque, Titre);
Discotheque liste_rechercher(Discotheque, Titre);
int         liste_compter_interpretes(Discotheque);
int         liste_album_present(Discotheque);
void        liste_afficher(Discotheque);
void        liste_detruire_discotheque(Discotheque);


#endif // TYPES_DISCO_INTERN_H

