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
    #ifdef __linux__
        printf("\033[H\033[J");
    #elif defined __MINGW32__ || defined __WIN32__
        system("cls");
    #else
        for(int i = 0; i < 20; i++) printf("\n");
    #endif
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
    while(implementation <= 0 || implementation >= 3);
    printf("\n");

    switch(implementation){
        case 1:
        discotheque_methode(METHODE_LISTE);
        break;

        case 2:
        discotheque_methode(METHODE_ARBRE);
        break;

        case 3:
        discotheque_methode(METHODE_HASH);
        break;
    }

    Discotheque d = creer_discotheque();

    char interprete[100] = {'\0'},
         label[100] = {'\0'},
         date[100] = {'\0'},
         style[100] = {'\0'};

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
        while(choix <= 0 || choix > 3);
        printf("\n");

        switch(choix)
        {
            case 1:
            printf("Affichage de la discothèque :\n");
            afficher(d);
            printf("\n");
            break;

            case 2:
            charger_discotheque_fichier("./databases/bigger.dat", &d);
            break;
            
            case 3:
            charger_discotheque_fichier("./databases/test.dat", &d);
            break;

            case 4:
            charger_discotheque_fichier("./databases/big.dat", &d);
            break;

            case 5:
            printf("Nom : "); saisie(titre, 100);
            printf("Interprete : "); saisie(interprete, 100);
            printf("Label : "); saisie(label, 100);
            printf("Date : "); saisie(date, 100);
            printf("Style : "); saisie(style, 100);

            printf("Vous avez entre : %s | %s | %s | %s | %s\n", titre, interprete, label, date, style);

            if(implementation == 1);
            else if(implementation == 2)
                d = inserer(d, titre, interprete, label, date, style);
            else;

            break;

            case 6:
            printf("Entrez le nom de l'album à supprimer : ");
            saisie(titre, 100);
            printf("Recherche de \'%s\' en cours...\n", titre);

            if(rechercher(d, titre) == NULL)
                printf("L'album n'a pas ete trouve.\n");
            else
            {
                d = supprimer(d, titre);
                printf("Album supprime.\n");
            }

            break;

            case 7:

            printf("Nom :");
            saisie(titre, 100);
            printf("Recherche de \'%s\' en cours...\n", titre);

            Discotheque drecherche = rechercher(d, titre);

            if(drecherche == NULL)
                printf("L'album n'a pas ete trouve.\n");

            break;

            case 8:
            printf("Il y a %d interpretes.\n", compter_interpretes(d));
            break;

            case 10:
            boucle = 0;
            case 9:
            printf("Destruction de la discotheque en cours...\n");
            detruire_discotheque(d);
            printf("Creation d'une discotheque vide en cours...\n");
            d = creer_discotheque();
            printf("Termine.\n");
            break;
        }

        printf("Appuyez sur Entrée pour continuer\n");
        if(boucle != 0)
        {
            getchar();
        }
    }

    detruire_discotheque(d);
}
