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
int                 charger_discotheque_fichier(char*, Discotheque*);
int                 discotheque_methode(methode_t);
extern  Discotheque (*creer_discotheque)(void);
extern  Discotheque (*inserer)(Discotheque, Titre, Interprete, Label, Date, Style);
extern  Discotheque (*supprimer)(Discotheque, Titre);
extern  Discotheque (*rechercher)(Discotheque, Titre);
extern  int         (*compter_interpretes)(Discotheque);
extern  void        (*afficher)(Discotheque);
extern  void        (*detruire_discotheque)(Discotheque);

#endif // TYPES_DISCO_H

