#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/mlist.h>
#include <types/map.h>
#include <types/disco_intern.h>
#include <types/disco.h>

void liste_free(music_t* music);

Discotheque liste_creer_discotheque(void) {
    return mlist_empty();
}


void liste_detruire_discotheque(Discotheque d){
    music_t* music;
    mlist_t* disco = d;

    while((music = mlist_rem(&disco, NULL)) != NULL){
        liste_free(music);
    }
}


Discotheque liste_inserer(Discotheque di, Titre t, Interprete i, Label l, Date d, Style s) {
    mlist_t* disco = di;
    music_t* music = malloc(sizeof(music_t));
    
    music->title    = strdup(t);
    music->author   = strdup(i);
    music->label    = strdup(l);
    music->date     = strdup(d);
    music->style    = strdup(s);

    mlist_add(&disco, music->title, music);
    return disco;
}


Discotheque liste_rechercher(Discotheque d, Titre t){
    Discotheque result = liste_creer_discotheque();
    
    music_t* music;
    mlist_t* disco = d;
    while(result == NULL && disco != NULL){
        if(strcmp(disco->key, t) == 0){
            music = disco->value;
            result = liste_inserer(result,
                music->title, music->author, music->label, music->date, music->style);
        }
        disco = disco->next;
    }

    return result;
}


Discotheque liste_supprimer(Discotheque d, Titre t){
    mlist_t* parent = NULL;
    mlist_t* child = d;
    music_t* music = NULL;

    while(child != NULL && music == NULL){
        if(strcmp(child->key, t) == 0){
            if(parent != NULL){
                parent->next = child->next;
            } else {
                d = parent;
            }

            music = mlist_rem(&child, NULL);
            liste_free(music);
        } else {
            parent = child;
            child = child->next;
        }
    }


    return d;
}

int liste_compter_interpretes(Discotheque d){
    mlist_t* disco = d;
    map_t* authors = map_new(0);
    music_t* music;
    int count;

    while(disco != NULL){
        music = disco->value;
        map_set(authors, music->author, MAP_EXIST);
        disco = disco->next;
    }

    count = authors->elem_count;
    
    map_del(authors);
    return count;
}

void liste_afficher(Discotheque d){
    mlist_t* list = d;
    music_t* music;

    while(list != NULL){
        music = list->value;
        printf("%s (%s)\n", music->title, music->author);
        list = list->next;
    }
}

void liste_afficher_album(Discotheque d){
    if(d != NULL){
        
    }
}

void liste_free(music_t* music){
    if(music != NULL){
        free(music->title);
        free(music->author);
        free(music->label);
        free(music->date);
        free(music->style);
        free(music);
    }
}
