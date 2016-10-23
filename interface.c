#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/disco.h>
#include <types/tree.h>
#include <interface.h>

#define vide_stdin() char __c; while( (__c = getchar()) != EOF && __c != '\n');

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
        for(int i = 0; i < 40; i++) printf("\n");
    #endif
}

/*
 * Fonction : saisie
 *            Fait rentrer une chaîne de caractères à l'utilisateur, la tronque à la bonne longueur, vide le buffer et retire le saut de ligne final.
 *
 * Arguments : chaine - Un pointeur vers la chaîne de caractères dans laquelle écrire
 *             longueur_max - La longueur maximale de la chaîne
 */
void saisie(const char* prompt, char * chaine, int longueur_max){
    int len;
    printf("%s ", prompt);
    fgets(chaine, longueur_max, stdin);
    
    len = strlen(chaine);
    
    for(int i = 0; i < len; i++){
        if(chaine[i] == '\r' || chaine[i] == '\n') chaine[i] = 0;
    }
    
    if(len == longueur_max - 1){
        vide_stdin();
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
int saisieNb(const char* prompt){
    int n;
    int result = 0;

    char buf[10];

    while(result != 1){
        saisie(prompt, buf, 10);
        result = sscanf(buf, "%d", &n);
        if(result != 1){
            printf("Entrée invalide\n");
        }
    }

    return n;
}


void lancer_interface(){
    int implementation = 0;

    effEcr();
    printf("Implémentation de la discothèque:\n"
           "1. Listes chainees\n"
           "2. Arbres binaires de recherche\n"  
           "3. Tables de hachage\n");

    do {
        implementation = saisieNb(">");
    } while(implementation <= 0 || implementation > 3);
    discotheque_methode(implementation);

    Discotheque d = creer_discotheque();

    char titre[100]      = "",
         interprete[100] = "",
         label[100]      = "",
         date[100]       = "",
         style[100]      = "",
         buffer[100]     = "";

    int boucle = 1;
    int choix = 0;

    while(boucle == 1){
        effEcr();
        printf("----- Menu principal -----\n"
               "1. Afficher la discotheque actuelle\n"
               "2. Charger un fichier\n"
               "3. Insérer un album\n"
               "4. Supprimer un album\n"
               "5. Rechercher un album\n"
               "6. Compter les interpretes de la discotheque\n"  
               "7. Detruire la discotheque\n"  
               "8. Quitter\n");

        do {
            choix = saisieNb(">");
        } while(choix <= 0 || choix > 10);

        effEcr();
 
        switch(choix) {
            case 1:
            printf("Affichage de la discothèque: \n");
            afficher(d);
            break;

            case 2:
            saisie("Chemin vers le fichier:", buffer, 100);
            printf("Chargement du fichier... ");
            fflush(stdout);
            if(charger_discotheque_fichier(buffer, &d)){
                printf("Terminé\n");
            } else {
                printf("\nLe fichier n'existe pas !\n");
            }
            break;
            
            case 3:
            do {
                saisie("Nom:", titre, 100);
                saisie("Interprète:", interprete, 100);
                saisie("Label:", label, 100);
                saisie("Date:", date, 100);
                saisie("Style:", style, 100);

                effEcr();
                printf("Nouveau album: %s | %s | %s | %s | %s\n\n",
                        titre, interprete, label, date, style);

                saisie("Insérer ([O]ui, [N]on, [A]nnuler) [O] ?", buffer, 100);
            } while(buffer[0] == 'N');
           
            if(buffer[0] == 'O' || buffer[0] == 0){
                d = inserer(d, titre, interprete, label, date, style);
                printf("Insertion réussi\n");
            } else {
                printf("Le titre n'a pas été inséré\n");
            }
            break;

            case 4:
            saisie("Entrez le nom de l'album à supprimer:", titre, 100);
            printf("Recherche de '%s' en cours...\n", titre);

            Discotheque resultat = rechercher(d, titre);
            if(album_present(resultat)){
                afficher_album(resultat);
                d = supprimer(d, titre);
                printf("Album supprimé\n");
            } else {
                printf("L'album n'a pas ete trouve.\n");
            }
            detruire_discotheque(resultat);
            break;

            case 5:
            saisie("Nom:", titre, 100);
            printf("Recherche de '%s' en cours...\n", titre);

            Discotheque drecherche = rechercher(d, titre);
            if(album_present(drecherche)){
                afficher_album(drecherche);
            } else {
                printf("L'album n'a pas ete trouve.\n");
            }
            detruire_discotheque(drecherche);
            break;

            case 6:
            printf("Il y a %d interpretes.\n", compter_interpretes(d));
            break;

            case 8:
            boucle = 0;
            case 7:
            printf("Destruction de la discotheque en cours...\n");
            detruire_discotheque(d);
            
            printf("Creation d'une discotheque vide en cours...\n");
            d = creer_discotheque();
            printf("Termine.\n");
            break;
        }

        if(boucle != 0){
            saisie("\nAppuyez sur Entrée pour continuer", buffer, 1);
        }
    }

    detruire_discotheque(d);
}

