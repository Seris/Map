#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

void effEcr();

void saisie(char * chaine, int longueur_max);

int saisieNb(char * chaine, int longueur_max);

void chargement_BD(char * nom_fichier, Discotheque * d);

void lancer_interface();

#endif // INTERFACE_H_INCLUDED
