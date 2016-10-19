#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/tree.h>
#include <types/mlist.h>
#include <types/disco.h>

/* Fonction : afficher
 *            Affiche de manière infixe la discothèque
 *
 * Arguments : dvoid - La discothèque à afficher
 */
void arbre_afficher(Discotheque dvoid)
{
    arbre_afficher_rec(dvoid, 0);
}

/* Fonction : afficher_rec
 *            Affiche de manière infixe la discothèque. Est codée pour fonctionner récursivement.
 *
 * Arguments : dvoid - La discothèque à afficher
               profondeur - La différence de niveau par rapport à celui de la racine
 */
void arbre_afficher_rec(Discotheque dvoid, int profondeur)
{
    struct NoeudSt * d = (struct NoeudSt *)dvoid;

    if(d == NULL)
    {
        return;
    }

    arbre_afficher_rec(d->fils_g, profondeur + 1);

    int i;
    for(i = 0; i < profondeur; i++)
        printf("--> ");
    printf("%s | %s | %s | %s | %s\n", d->titre, d->interprete, d->label, d->date, d->style);

    arbre_afficher_rec(d->fils_d, profondeur + 1);

    return;
}

/*
 * Fonction : creer_discotheque
 *            Crée une discothèque vide. Et valide.
 *
 * Retourne : le pointeur nul. Qui correspond à une discothèque vide avec cette implémentation.
 */
Discotheque arbre_creer_discotheque(){
    return NULL;
}


/* Fonction : creer_noeud
 *            Crée une discotheque correspondant à un seul album aux caractéristiques données en paramètres
 *
 * Arguments : titre - Un pointeur vers une chaîne de caractères correspondant au titre de l'album
 *             interprete - Un pointeur vers une chaîne de caractères correspondant à l'interprête de l'album
 *             label - Un pointeur vers une chaîne de caractères correspondant au label de l'album
 *             date - Un pointeur vers une chaîne de caractères correspondant à la date de sortie de l'album
 *             style - Un pointeur vers une chaîne de caractères correspondant au style de l'album
 *             f_g - Une discothèque à placer en tant qu'enfant à gauche de la discothèque créée, dans le cadre de l'arbre binaire de recherche
 *             f_d - Une discothèque à placer en tant qu'enfant à droite de la discothèque créée, dans le cadre de l'arbre binaire de recherche
 *
 * Retourne : La discothèque créée contenant l'album.
 */
Discotheque arbre_creer_noeud(char * titre, char * interprete, char * label, char * date, char * style, Discotheque f_g, Discotheque f_d)
{
    struct NoeudSt * d = (struct NoeudSt *) malloc(sizeof(struct NoeudSt));

    d->fils_g       = f_g;
    d->fils_d       = f_d;
    d->titre        = strdup(titre);
    d->interprete   = strdup(interprete);
    d->label        = strdup(label);
    d->date         = strdup(date);
    d->style        = strdup(style);

    return d;
}

/*
 * Fonction : inserer
 *            Place de manière optimisée l'album passé en paramètre dans la discothèque, et renvoie la discothèque ainsi modifiée.
              Attention, les chaines de caractères ne sont pas dupliquées, les pointeurs sont entrés tels quels dans la discothèque.
 *
 * Arguments : dvoid - La discothèque dans laquelle la fonction doit insérer l'album. Attention, la fonction ne duplique pas la discothèque initiale. Ainsi, parfois elle restera inchangée, parfois non.
 *             titre - Un pointeur vers une chaîne de caractères correspondant au titre de l'album
 *             interprete - Un pointeur vers une chaîne de caractères correspondant à l'interprête de l'album
 *             label - Un pointeur vers une chaîne de caractères correspondant au label de l'album
 *             date - Un pointeur vers une chaîne de caractères correspondant à la date de sortie de l'album
 *             style - Un pointeur vers une chaîne de caractères correspondant au style de l'album
 *
 * Retourne : La discothèque dans laquelle l'album a été inséré
 */
Discotheque arbre_inserer(Discotheque dvoid, Titre titre, Interprete interprete, Label label, Date date, Style style)
{
    struct NoeudSt * d = (struct NoeudSt *)dvoid;

    if(d == NULL)
    {
        return arbre_creer_noeud(titre, interprete, label, date, style, NULL, NULL); // Toujours une feuille
    }

    if(strcmp(titre, d->titre) < 0)
    {
        d->fils_g = arbre_inserer(d->fils_g, titre, interprete, label, date, style);
    }
    else if(strcmp(titre, d->titre) > 0)
    {
        d->fils_d = arbre_inserer(d->fils_d, titre, interprete, label, date, style);
    }
    else
        printf("Il y a deja le nom '%s'.\n", titre);

    return d;
}

/* Fonction : supprimer
 *            Supprime un unique album de la discothèque entrée en paramètre, tout en laissant la discothèque fonctionnelle.
 *
 * Arguments : dvoid - La discothèque dans laquelle supprimer l'album
 *             t - Un pointeur vers une chaîne de caractères correspondant au titre de l'album à supprimer
 *
 * Retourne : La discothèque denuée de l'album. Attention, la fonction ne duplique pas la discothèque initiale. Ainsi, parfois la discothèque initiale restera inchangée, parfois non.
 */
Discotheque arbre_supprimer(Discotheque dvoid, char * t)
{
    struct NoeudSt * d = (struct NoeudSt *)dvoid;

    if(d == NULL)
        return NULL;

    if(strcmp(t, d->titre) < 0) // Placement au bon endroit de l'arbre, on veut que d soit le noeud à supprimer
        d->fils_g = arbre_supprimer(d->fils_g, t);
    else if(strcmp(t, d->titre) > 0)
        d->fils_d = arbre_supprimer(d->fils_d, t);
    else if(d->fils_g == NULL && d->fils_d == NULL) // Le cas facile, où d est une feuille
    {
        arbre_detruire_album(d);
        return NULL;
    }
    else if(d->fils_g == NULL) // Les cas où d n'a pas deux enfants
    {
        Discotheque d0 = d->fils_d;
        arbre_detruire_album(d);
        return d0;
    }
    else if(d->fils_d == NULL)
    {
        Discotheque d0 = d->fils_g;
        arbre_detruire_album(d);
        return d0;
    }
    else
    {
        // d->fils_d est à insérer le plus à droite de d->fils_g
        struct NoeudSt * i = d->fils_g;

        while(i->fils_d != NULL)
        {
            i = i->fils_d;
        }
        i->fils_d = d->fils_d;

        Discotheque d0 = d->fils_g;
        arbre_detruire_album(d);
        return d0;
    }


    return d;
}

/* Fonction : rechercher_album
 *            Recherche un album dans une discothèque
 *
 * Arguments : dvoid - La discothèque dans laquelle rechercher l'album
 *             titre - Un pointeur vers une chaîne de caractères correspondant au titre de l'album à rechercher
 *
 * Retourne : La discothèque possédant l'album à sa racine.
 */
Discotheque arbre_rechercher(Discotheque dvoid, char * titre)
{
    struct NoeudSt * d = (struct NoeudSt *)dvoid;

    if(d == NULL)
    {
        return NULL;
    }
    else if(strcmp(titre, d->titre) < 0)
    {
        return arbre_rechercher(d->fils_g, titre);
    }
    else if(strcmp(titre, d->titre) > 0)
    {
        return arbre_rechercher(d->fils_d, titre);
    }
    else
    {
        return d;
    }
}

/* Fonction : compter_interpretes
 *            Cherche le nombre d'interpretes uniques dans la discothèque entrée en paramètre
 *
 * Arguments : d - La discothèque dans laquelle compter les interprêtes
 *
 * Retourne : Le nombre d'inteprêtes uniques de la discothèque
 */
int arbre_compter_interpretes(Discotheque d)
{
    mlist_t* l = mlist_empty(); // Liste dans laquelle on stocke les interpretes
    int incr = 0; // Permet de compter, car ça devient trèèèèèèèèèèèèèèèèèèèès long avec de grandes bases de données
    int nb = arbre_compter_interpretes_rec(d, &l, &incr);
    mlist_delete(l);
    return nb;
}

/* Fonction : compter_interpretes_rec
 *            Cherche le nombre d'interpretes uniques dans la discothèque entrée en paramètre après les avoir comparés à une liste. Fonctionne de manière récursive.
 *
 * Arguments : dvoid - La discothèque dans laquelle compter les interprêtes
 *             pl - Un pointeur vers une liste contenant les noms des interprêtes déjà comptés
 *             pIncr - Un pointeur vers un entier contenant le nombre de noeuds déjà traités
 *
 * Retourne : Le nombre d'inteprêtes uniques de la discothèque
 */
int arbre_compter_interpretes_rec(Discotheque dvoid, mlist_t** pl, int * pIncr)
{
    struct NoeudSt * d = (struct NoeudSt *)dvoid;

    if(d == NULL)
        return 0;

    int nb = arbre_compter_interpretes_rec(d->fils_g, pl, pIncr) + arbre_compter_interpretes_rec(d->fils_d, pl, pIncr);

    if(!mlist_key_exist(*pl, d->interprete)) // Si l'interprete n'est pas encore compté, on le compte et on l'ajoute
    {
        nb++;
        mlist_add(pl, d->interprete, MLIST_EXIST);
    }

    (*pIncr)++;
    
    return nb;
}

/* Fonction : detruire_discotheque
 *            Supprime complètement la discothèque de la mémoire
 *
 * Arguments : dvoid - La discothèque à supprimer
 */
void arbre_detruire_discotheque(Discotheque dvoid)
{
    struct NoeudSt * d = (struct NoeudSt *)dvoid;

    if(d != NULL){
        arbre_detruire_discotheque(d->fils_g);
        arbre_detruire_discotheque(d->fils_d);
        arbre_detruire_album(d);
    }
}

/* Fonction : detruire_album
 *            Supprime seulement un album de la mémoire, sans prendre en compte les eventuels enfants de la discothèque
 *
 * Arguments : dvoid - La discothèque à supprimer
 */
void arbre_detruire_album(Discotheque dvoid)
{
    struct NoeudSt * d = (struct NoeudSt *)dvoid;

    if(d == NULL)
        return;

    free(d->titre);
    free(d->interprete);
    free(d->label);
    free(d->date);
    free(d->style);
    free(d);
}
