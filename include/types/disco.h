#ifndef TYPES_DISCO_H
#define TYPES_DISCO_H

typedef void    *Discotheque;
typedef char    *Titre, *Interprete, *Label, *Date, *Style;

typedef struct {
    Titre       title;
    Interprete  author;
    Label       label;
    Date        date;
    Style       style;
} music_t;

typedef enum {
    METHODE_HASH,
    METHODE_ARBRE,
    METHODE_LISTE
} methode_t;

/**
 * Discotheque Prototypes
 */
Discotheque         creer_discotheque_fichier(char* file);
int                 discotheque_methode(methode_t methode);
extern  Discotheque (*creer_discotheque)(void);
extern  Discotheque (*inserer)(Discotheque, Titre, Interprete, Label, Date, Style);
extern  Discotheque (*supprimer)(Discotheque, Titre);
extern  Discotheque (*rechercher)(Discotheque, Titre);
extern  int         (*compter_interpretes)(Discotheque);
extern  void        (*afficher)(Discotheque);
extern  void        (*detruire_discotheque)(Discotheque);

/**
 * Hash Table Prototypes
 **/
Discotheque hash_creer_discotheque(void);
Discotheque hash_inserer(Discotheque, Titre, Interprete, Label, Date, Style);
Discotheque hash_supprimer(Discotheque, Titre);
Discotheque hash_rechercher(Discotheque, Titre);
int         hash_compter_interpretes(Discotheque);
void        hash_afficher(Discotheque);
void        hash_detruire_discotheque(Discotheque);

/**
 * Tree Prototypes
 **/
Discotheque arbre_creer_discotheque();
Discotheque arbre_inserer(Discotheque, Titre, Interprete, Label, Date, Style);
Discotheque arbre_supprimer(Discotheque, Titre);
Discotheque arbre_rechercher(Discotheque, Titre);
int         arbre_compter_interpretes(Discotheque);
void        arbre_afficher(Discotheque);
void        arbre_detruire_discotheque(Discotheque);

#endif // TYPES_DISCO_H
