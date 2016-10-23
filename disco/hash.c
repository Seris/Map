#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/map.h>
#include <types/mlist.h>
#include <types/disco.h>

void hash_destructor(char* key, void* m);
void hash_display_music(music_t* music);


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

    if(!map_set(disco, music->title, music)){
        hash_destructor(music->title, music);
    }

    return disco;
}


Discotheque hash_supprimer(Discotheque disco, Titre t){
    map_unset(disco, t);
    return disco;
}


Discotheque hash_rechercher(Discotheque d, Titre t){
    map_t* disco = hash_creer_discotheque();
    music_t* music = map_get(d, t);
    
    disco->max_load_factor = 1;
    map_set_table_size(disco, 1);

    if(music != NULL){
        hash_inserer(disco,
            music->title, music->author, music->label, music->date, music->style);
        disco->table[0]->key = strdup("__selected__");
    }

    return disco;
}


void hash_afficher_album(Discotheque d){
    music_t* music = map_get(d, "__selected__");
    if(music != NULL){
        hash_display_music(music);
    }
}


int hash_album_present(Discotheque d){
    return map_get(d, "__selected__") != NULL;
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
    if(music->title != key){
        free(key);
    }
    free(music->title);
    free(music->author);
    free(music->label);
    free(music->date);
    free(music->style);
    free(music);
}

void hash_display_music(music_t* music){
    printf("%s :\n", music->title);
    printf("* Interprete: %s\n", music->author);
    printf("* Label:      %s\n", music->label);
    printf("* Style:      %s\n", music->style);
    printf("* Date:       %s\n", music->date);
}


