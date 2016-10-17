#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/music.h>
#include <types/clist.h>
#include <types/map.h>
#include <assert.h>

int map_default_hash(map_t* map, char* key){
    int h1 = 0xffff0000,
        h2 = 0x12ae13fa,
        h3 = 0x87d5a7bb;

    for(int i = 0; key[i] != 0; i++){
        h3 += (h1 * i) << (key[i] % 7);
        h2 += (h3 * i + h1 + key[i]);
        h1 += (h2 & 0xffff0000 + h3 & 0xffff) * (h2 - key[i] * i);
    }

    h1 += h2 - h3;
    if(h1 < 0) h1 *= -1;

    return h1 % map->table_size;
}

void map_change_size(map_t* map, int nsize){
    music_t *music;
    clist_t **ntable = calloc(nsize, sizeof(clist_t*));
    assert_malloc(ntable, "new hashtable");

    clist_t **otable = map->table;
    int osize = map->table_size;

    #ifdef DEBUG
    printf("DEBUG: resizing map\n");
    printf("DEBUG: \tlf(%lf), mlf(%lf), os(%d), ns(%d), ",
        map->current_load_factor, map->max_load_factor,
        osize, nsize);
    #endif // DEBUG
 
    map->table = ntable;
    map->table_size = nsize;
    map->current_load_factor = 0;
    map->elem_count = 0;

    for(int i = 0; i < osize; i++){
        while(clist_shift(&otable[i], &music) == 0){
            map_set(map, music);
        }
    }

    #ifdef DEBUG
    printf("nlf(%f)\n", map->current_load_factor);
    #endif

    free(otable);
}

int map_author_exist(char** list, int s, char* author){
    for(int i = 0; i < s; i++){
        if(strcmp(list[i], author) == 0){
            return 0;
        }
    }

    return -1;
}

int map_count_author(map_t* map){
    int count = 0;
    int i = 0;
    char** author_list = malloc(0);
    clist_t* elem;

    for(; i < map->table_size; i++){
        elem = map->table[i];
        while(elem != NULL){
            if(map_author_exist(author_list, count, elem->music->author) == -1){
                author_list = realloc(author_list, (count+1) * sizeof(char*));
                author_list[count++] = elem->music->author;
            }
            clist_next(&elem);
        }
    }

    free(author_list);

    return count;
}

void map_resize_to_fit(map_t* map){
    int nsize = map->elem_count;
    if(nsize == 0) nsize = 1;
    map_change_size(map, nsize);
}

map_t* map_create(void){
    map_t *map = calloc(1, sizeof(map_t));
    assert_malloc(map, "map");

    map->max_load_factor = 0.75;
    map->table_size  = 0;
    map->table = NULL;

    map_change_size(map, 100); 
    return map;
}

int map_set(map_t* map, music_t* music){
    int pos;

    map->current_load_factor = (float) map->elem_count / map->table_size;

    if(map->current_load_factor > map->max_load_factor){
        int new_size = (int) (map->table_size * 1.1);
        map_change_size(map, new_size);
    }

    if(map_get(map, music->title, NULL) != 0){
        pos = map_default_hash(map, music->title);
        clist_unshift(&map->table[pos], music);
        map->elem_count++;
        return 0;
    } else {
        #ifdef DEBUG
        printf("DEBUG: /!\\ entry %s already exist\n", music->title);
        #endif // DEBUG
    }

    return -1;
}

int map_get(map_t* map, char* title, music_t** music){
    int pos = map_default_hash(map, title);
    clist_t* elem = map->table[pos];
    int status = -1;

    while(elem != NULL && status == -1){
        if(strcmp(title, elem->music->title) == 0){
            status = 0;
            if(music != NULL) *music = elem->music;
        } else {
            clist_next(&elem);
        }
    }

    return status;
}

int map_unset(map_t* map, char* title, music_t** music){
   int pos = map_default_hash(map, title);
   clist_t* child = map->table[pos], *parent = NULL;
   int deleted = -1;

    while(child != NULL && deleted == -1){
       if(strcmp(title, child->music->title) == 0){
            
            if(parent != NULL){
                parent->next = child->next;
            } else {
                map->table[pos] = child->next;
            }

            if(music != NULL)  *music = child->music;
            free(child);
            deleted = 0;
       } else {
            parent = child;
            clist_next(&child);
       }
    }

    return deleted;
}

int map_delete(map_t* map){
    clist_t *link;
    for(int i = 0; i < map->table_size; ++i){
       link = map->table[i];
       while(clist_shift(&link, NULL) == 0);
    }

    free(map->table);
    free(map);
    return 0;
}

void map_show_stack(map_t *map){
    clist_t *list;
    for(int i = 0; i < map->table_size; ++i){
        list = map->table[i];
        while(clist_next(&list) == 0){
            printf("♩");
        }
        printf("\n");
    }
}
