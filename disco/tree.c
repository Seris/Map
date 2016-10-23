#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/tree.h>
#include <types/mlist.h>
#include <types/disco.h>

/* afficher
 * @brief Affiche de manière infixe la discothèque
 * @param dvoid La discothèque à afficher
 */
void arbre_afficher(Discotheque dvoid)
{
    arbre_afficher_rec(dvoid, 0);
}

/* afficher_rec
 * @brief Affiche de manière infixe la discothèque. Est codée pour fonctionner récursivement.
 * @param dvoid La discothèque à afficher
 * @param profondeur La différence de niveau par rapport à celui de la racine
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

/* creer_discotheque
 * @brief Crée une discothèque vide. Et valide.
 * @pre Aucune
 * @post Crée une dicothèque fonctionnelle
 * @invariant Aucun
 * @return Le pointeur nul. Qui correspond à une discothèque vide avec cette implémentation.
 */
Discotheque arbre_creer_discotheque(){
    return NULL;
}


/* creer_noeud
 * @brief Crée une discotheque correspondant à un seul album aux caractéristiques données en paramètres
 * @param titre Un pointeur vers une chaîne de caractères correspondant au titre de l'album
 * @param interprete Un pointeur vers une chaîne de caractères correspondant à l'interprête de l'album
 * @param label Un pointeur vers une chaîne de caractères correspondant au label de l'album
 * @param date Un pointeur vers une chaîne de caractères correspondant à la date de sortie de l'album
 * @param style Un pointeur vers une chaîne de caractères correspondant au style de l'album
 * @param f_g Une discothèque à placer en tant qu'enfant à gauche de la discothèque créée, dans le cadre de l'arbre binaire de recherche
 * @param f_d Une discothèque à placer en tant qu'enfant à droite de la discothèque créée, dans le cadre de l'arbre binaire de recherche
 * @return La discothèque créée contenant l'album
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
 * inserer
 * @brief Place de manière optimisée l'album passé en paramètre dans la discothèque, et renvoie la discothèque ainsi modifiée.
 * @pre disco, t, i, l, d et s doivent être dans des formats valides. Il ne doit pas déjà y avoir un album de titre t dans disco.
 * @post Retourne une discothèque fonctionnalle contenant le nouvel album
 * @invariant Les autres albums contenus dans disco ne changent pas.
 * @param dvoid La discothèque dans laquelle la fonction doit insérer l'album. Attention, la fonction ne duplique pas la discothèque initiale. Ainsi, parfois elle restera inchangée, parfois non.
 * @param titre Un pointeur vers une chaîne de caractères correspondant au titre de l'album
 * @param interprete Un pointeur vers une chaîne de caractères correspondant à l'interprête de l'album
 * @param label Un pointeur vers une chaîne de caractères correspondant au label de l'album
 * @param date Un pointeur vers une chaîne de caractères correspondant à la date de sortie de l'album
 * @param style Un pointeur vers une chaîne de caractères correspondant au style de l'album
 * @return La discothèque dans laquelle l'album a été inséré
 */
Discotheque arbre_inserer(Discotheque dvoid, Titre titre, Interprete interprete, Label label, Date date, Style style)
{
    struct NoeudSt * d = (struct NoeudSt *)dvoid;

    if(d == NULL)
    {
        return arbre_creer_noeud(titre, interprete, label, date, style, NULL, NULL); // L'album créé est toujours une feuille
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

/* supprimer
 * @brief Supprime un unique album de la discothèque entrée en paramètre, tout en laissant la discothèque fonctionnelle.
 * @pre d et t doivent être dans des formats valides. Un album de titre t doit se trouver dans d.
 * @post La discothèque retournée ne possède plus l'album de titre t, et est toujours fonctionnelle.
 * @invariant Les autres albums contenus dans d sont invariants.
 * @param dvoid La discothèque dans laquelle supprimer l'album
 * @param t Un pointeur vers une chaîne de caractères correspondant au titre de l'album à supprimer
 * @return La discothèque denuée de l'album
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

/* rechercher_album
 * @brief Recherche un album dans une discothèque
 * @pre d et t doivent être dans des formats valides.
 * @post La fonction retourne les éléments descriptifs de l'album de titre t contenu dans d. Elle retourne une constante définie comme nulle si il n'y a pas d'album de titre t dans d.
 * @invariant La discothèque entière ne change pas.
 * @param dvoid La discothèque dans laquelle rechercher l'album
 * @param titre Un pointeur vers une chaîne de caractères correspondant au titre de l'album à rechercher
 * @return La discothèque possédant l'album à sa racine ou NULL si l'album n'est pas trouvé
 */
Discotheque arbre_rechercher(Discotheque dvoid, char * titre)
{
    struct NoeudSt * d = (struct NoeudSt *)dvoid;

    if(d == NULL) {
        return NULL;
    } else if(strcmp(titre, d->titre) < 0) {
        return arbre_rechercher(d->fils_g, titre);
    } else if(strcmp(titre, d->titre) > 0){
        return arbre_rechercher(d->fils_d, titre);
    } else {
        return arbre_inserer(arbre_creer_discotheque(),
            d->titre, d->interprete, d->label, d->date, d->style);
    }
}

int arbre_album_present(Discotheque d){
    return d != NULL;
}

/* compter_interpretes
 * @brief Cherche le nombre d'interpretes uniques dans la discothèque entrée en paramètre
 * @pre d doit être dans un format valide.
 * @post La fonction retourne le nombre entier d'artistes uniques des différents albums de d.
 * @invariant La discothèque d ne varie pas.
 * @param d La discothèque dans laquelle compter les interprêtes
 * @return Le nombre d'inteprêtes uniques de la discothèque
 */
int arbre_compter_interpretes(Discotheque d)
{
    mlist_t* l = mlist_empty(); // Liste dans laquelle on stocke les interpretes
    int incr = 0; // Permet de compter, car ça devient trèèèèèèèèèèèèèèèèèèèès long avec de grandes bases de données
    int nb = arbre_compter_interpretes_rec(d, &l, &incr);
    mlist_delete(l);
    return nb;
}

/* compter_interpretes_rec
 * @brief Cherche le nombre d'interpretes uniques dans la discothèque entrée en paramètre après les avoir comparés à une liste. Fonctionne de manière récursive.
 * @param dvoid La discothèque dans laquelle compter les interprêtes
 * @param pl Un pointeur vers une liste contenant les noms des interprêtes déjà comptés
 * @param pIncr Un pointeur vers un entier contenant le nombre de noeuds déjà traités
 * @return Le nombre d'inteprêtes uniques de la discothèque
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

/* detruire_discotheque
 * @brief Supprime complètement la discothèque de la mémoire
 * @pre La discothèque d doit être dans un format valide
 * @post La discothèque d disparaît de la mémoire
 * @invariant Aucun
 * @param dvoid La discothèque à supprimer
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

/* detruire_album
 * @brief Supprime seulement un album de la mémoire, sans prendre en compte les eventuels enfants de la discothèque
 * @param dvoid La discothèque à supprimer
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

int arbre_est_vide(Discotheque d)
{
    return (d == NULL);
}
