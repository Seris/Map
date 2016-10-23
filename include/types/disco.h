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
    METHODE_LISTE = 1,
    METHODE_ARBRE,
    METHODE_HASH
} methode_t;

/**
 * Discotheque Prototypes
 */
int                 charger_discotheque_fichier(const char*, Discotheque*);
int                 discotheque_methode(methode_t);
extern  Discotheque (*creer_discotheque)(void);
extern  Discotheque (*inserer)(Discotheque, Titre, Interprete, Label, Date, Style);
extern  Discotheque (*supprimer)(Discotheque, Titre);
extern  Discotheque (*rechercher)(Discotheque, Titre);
extern  int         (*album_present)(Discotheque); 
extern  int         (*compter_interpretes)(Discotheque);
extern  void        (*afficher)(Discotheque);
extern  void        (*afficher_album)(Discotheque);
extern  void        (*afficher_stats)(Discotheque);
extern  void        (*detruire_discotheque)(Discotheque);

#endif // TYPES_DISCO_H

