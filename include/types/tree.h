#ifndef ARBRES_H_INCLUDED
#define ARBRES_H_INCLUDED

#include <types/disco.h>
#include <types/mlist.h>

/// Début de l'implémentation de Discotheque par arbre de recherche.

struct NoeudSt
{
    char * titre;
    char * interprete;
    char * label;
    char * date;
    char * style;
    struct NoeudSt * fils_g;
    struct NoeudSt * fils_d;
};

void        arbre_afficher_rec(Discotheque d, int profondeur);
int         arbre_compter_interpretes_rec(Discotheque d, mlist_t** pl, int * pIncr);
Discotheque arbre_creer_noeud(char * titre, char * interprete, char * label, char * date, char * style, Discotheque f_g, Discotheque f_d);
void        arbre_detruire_album(Discotheque d);
void        arbre_afficher_album(Discotheque dvoid);
void        arbre_afficher_stats(Discotheque dvoid);
int         arbre_hauteur(Discotheque dvoid);
int         arbre_taille(Discotheque dvoid);

#endif // ARBRES_H_INCLUDED
