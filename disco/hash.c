#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/map.h>
#include <types/mlist.h>
#include <types/disco.h>

void hash_destructor(char* key, void* m);


Discotheque hash_creer_discotheque(){
    map_t* disco = map_new(0);
    map_set_destructor(disco, &hash_destructor);
    return disco;
}


void hash_detruire_discotheque(Discotheque d){
    map_del(d);
}


Discotheque hash_inserer(Discotheque disco, Titre t, Interprete i, Label l, Date d, Style s){
    music_t* music = malloc(sizeof(music_t));
    
    music->title  = strdup(t);
    music->author = strdup(i);
    music->label  = strdup(l);
    music->date   = strdup(d);
    music->style  = strdup(s);

    map_set(disco, music->title, music);

    return disco;
}


Discotheque hash_supprimer(Discotheque disco, Titre t){
    map_unset(disco, t);
    return disco;
}


Discotheque hash_rechercher(Discotheque d, Titre t){
    Discotheque result = hash_creer_discotheque();
    map_set_table_size(result, 1);
    music_t* music = map_get(d, t);

    if(music != NULL){
        hash_inserer(result, music->title, music->author, music->label, music->date, music->style);
    }

    return result;
}

void hash_display_music(music_t* music){
    printf("%s :\n", music->title);
    printf("* Interprete: %s\n", music->author);
    printf("* Label:      %s\n", music->label);
    printf("* Style:      %s\n", music->style);
    printf("* Date:       %s\n", music->date);
}

void hash_afficher_album(Discotheque d){
    map_t* map = d;
    if(map->table_size == 1){
        if(map->table[0] != NULL){
            hash_display_music(map->table[0]->value);
        }
    } else {
        fprintf(stderr, "afficher_album: Ce n'est pas un album mais une discothèque complète\n");
        exit(EXIT_FAILURE);
    }
}

void hash_afficher(Discotheque d){
    map_t* map = d;
    mlist_t* list;
    for(int i = 0; i < map->table_size; i++){
        list = map->table[i];
        while(list != NULL){ 
            hash_display_music(list->value);
            list = list->next;
        }
        printf("---------------\n");
    }
}

int hash_compter_interpretes(Discotheque d){
    map_t* disco = (map_t*) d;
    map_t* authors = map_new(0);
    mlist_t* item;
    music_t* music;
    int count;

    for(int i = 0; i < disco->table_size; i++){
        item = disco->table[i];
        while(item != NULL){
            music = (music_t*) item->value;
            map_set(authors, music->author, MAP_EXIST);
            item = item->next;
        }
    }

    count = authors->elem_count;
    map_del(authors);

    return count;
}


void hash_destructor(char* key, void* m){
    music_t* music = (music_t*) m;
    free(music->title);
    free(music->author);
    free(music->label);
    free(music->date);
    free(music->style);
    free(music);
}

