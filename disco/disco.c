#include <types/disco.h>

Discotheque (*creer_discotheque)(void);
Discotheque (*inserer)(Discotheque, Titre, Interprete, Label, Date, Style);
Discotheque (*supprimer)(Discotheque, Titre);
Discotheque (*rechercher)(Discotheque, Titre);
int         (*compter_interpretes)(Discotheque);
void        (*afficher)(Discotheque);
void        (*detruire_discotheque)(Discotheque);

