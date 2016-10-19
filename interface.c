#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/disco.h>
#include <types/tree.h>
#include <interface.h>


/*
 * Fonction : effEcr
 *            Efface l'écran en plaçant plein de retours à la ligne. Ce n'est pas très professionnel, je sais.
 */
void effEcr()
{
    printf("\n\n\n\n\n\n");
}

/*
 * Fonction : saisie
 *            Fait rentrer une chaîne de caractères à l'utilisateur, la tronque à la bonne longueur, vide le buffer et retire le saut de ligne final.
 *
 * Arguments : chaine - Un pointeur vers la chaîne de caractères dans laquelle écrire
 *             longueur_max - La longueur maximale de la chaîne
 */
void saisie(char * chaine, int longueur_max)
{
    fgets(chaine, longueur_max, stdin); // La fonction miracle
    int i;
    for(i = 0; i < longueur_max; i++) // Suppression du '\n'
    {
        if(chaine[i] == '\n')
            chaine[i] = '\0';
    }
    i = 0;
    while(i != EOF && i != '\n') // Vidange du buffer
        i = getchar();
}

/*
 * Fonction : saisieNb
 *            Fait rentrer un nombre à l'utilisateur, et gère la saisie non souhaitée de texte.
 *
 * Arguments : chaine - Un pointeur vers la chaîne de caractères dans laquelle écrire
 *             longueur_max - La longueur maximale de la chaîne
 *
 * Retourne : Le nombre entier saisi, ou 0 si c'est du texte qui est entré
 */
int saisieNb(char * chaine, int longueur_max)
{
    saisie(chaine, longueur_max);
    return strtol(chaine, NULL, 10);
}

/*
 * Fonction : chargement_BD
 *            Charge la base de donnée dont on donne l'emplacement, et la rentre dans la discothèque donnée en paramètre
 *
 * Arguments : nom_fichier - Un pointeur vers la chaîne de caractères correspondant à l'emplacement du fichier à lire
 *             d - Un pointeur vers la discothèque à remplir
 */
void chargement_BD(char * nom_fichier, Discotheque * d)
{
    FILE * fichier = fopen(nom_fichier, "r");
    if(fichier != NULL)
    {
        int ret = 0, li = 1;
        char * pTitre, * pInterprete, * pLabel, * pDate, * pStyle;
        char * ligne;

        while(ret != EOF)
        {
            if(li%1000 == 0)
                printf("Lecture de la ligne %d.\n", li);
            ret = fscanf(fichier, "%m[^\n]", &ligne); // Lecture de la ligne
            fseek(fichier, 1, SEEK_CUR); // Passage du retour à la ligne

            if(ret != EOF)
            {
                pTitre = strdup(strtok(ligne, "|"));
                pInterprete = strdup(strtok(NULL, "|"));
                pLabel = strdup(strtok(NULL, "|"));
                pDate = strdup(strtok(NULL, "|"));
                pStyle = strdup(strtok(NULL, "|"));

                *d = arbre_inserer(*d, pTitre, pInterprete, pLabel, pDate, pStyle);
                li++;
            }

            free(ligne);
        }

        fclose(fichier);

        printf("Fichier charge !!!\n");
    }
    else
        printf("Ouverture foiree.\n");
}

void lancer_interface()
{
    int implementation = 0;
    char titre[100] = {'\0'};

    printf("Quel mode d'implementation utiliser ?\n1. Listes chainees\n2. Arbres binaires de recherche\n3. Tables de hachage\n\n");
    do
    {
        implementation = 0;
        printf("--> ");
        implementation = saisieNb(titre, 2);
    }
    while(implementation <= 0 || implementation > 3);
    printf("\n");

    Discotheque d = arbre_creer_discotheque();

    printf("Une discotheque vide a ete creee.\n");
    char interprete[100] = {'\0'}, label[100] = {'\0'}, date[100] = {'\0'}, style[100] = {'\0'};
    char * pTitre, * pInterprete, * pLabel, * pDate, * pStyle;

    int boucle = 1;
    int choix = 0;

    while(boucle == 1)
    {
        effEcr();
        printf("\n----- Menu principal -----\n\n");
        printf("01. Afficher la discotheque actuelle\n02. Charger la base de donnees melangee\n03. Charger la base de donnees reduite\n04. Charger la base de donnees triee\n");
        printf("05. Inserer un album\n06. Supprimer un album\n07. Rechercher un album\n08. Compter les interpretes de la discotheque\n09. Detruire la discotheque\n10. Quitter\n\n");

        do
        {
            choix = 0;
            printf("--> ");
            choix = saisieNb(titre, 3);
        }
        while(choix <= 0 || choix > 10);
        printf("\n");

        switch(choix)
        {
            case 1:
            printf("Affichage de la discothèque :\n");
            arbre_afficher(d);
            printf("\n");
            break;

            case 2:
            chargement_BD("discogs_random.dat", &d);
            break;

            case 3:
            chargement_BD("discogs_limited.dat", &d);
            break;

            case 4:
            chargement_BD("discogs_sorted.dat", &d);
            break;

            case 5:

            printf("Nom : "); saisie(titre, 100);
            printf("Interprete : "); saisie(interprete, 100);
            printf("Label : "); saisie(label, 100);
            printf("Date : "); saisie(date, 100);
            printf("Style : "); saisie(style, 100);

            printf("Vous avez entre : %s | %s | %s | %s | %s\n", titre, interprete, label, date, style);

            pTitre = strdup(titre);
            pInterprete = strdup(interprete);
            pLabel = strdup(label);
            pDate= strdup(date);
            pStyle = strdup(style);

            if(implementation == 1);
            else if(implementation == 2)
                d = arbre_inserer(d, pTitre, pInterprete, pLabel, pDate, pStyle);
            else;

            break;

            case 6:

            printf("Entrez le nom de l'album à supprimer : ");
            saisie(titre, 100);
            printf("Recherche de \'%s\' en cours...\n", titre);

            if(arbre_rechercher(d, titre) == NULL)
                printf("L'album n'a pas ete trouve.\n");
            else
            {
                d = arbre_supprimer(d, titre);
                printf("Album supprime.\n");
            }

            break;

            case 7:

            printf("Nom :");
            saisie(titre, 100);
            printf("Recherche de \'%s\' en cours...\n", titre);

            Discotheque drecherche = arbre_rechercher(d, titre);

            if(drecherche == NULL)
                printf("L'album n'a pas ete trouve.\n");
            else
            {
                //printf("%s | %s | %s | %s | %s\n", drecherche->titre, drecherche->interprete, drecherche->label, drecherche->date, drecherche->style); // Marche pas
            }

            break;

            case 8:
            printf("Il y a %d interpretes.\n", arbre_compter_interpretes(d));
            break;

            case 10:
            boucle = 0;
            case 9:
            printf("Destruction de la discotheque en cours...\n");
            arbre_detruire_discotheque(d);
            printf("Creation d'une discotheque vide en cours...\n");
            d = arbre_creer_discotheque();
            printf("Termine.\n");
            break;
        }

        if(boucle != 0)
        {
            getchar();
        }
    }
}
