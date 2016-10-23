#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert_malloc.h>
#include <types/map.h>
#include <types/mlist.h>

map_t* map_new(int size){
    map_t* map = malloc(sizeof(map_t));
    assert_malloc(map, "map");

    map->table = NULL;
    map->table_size = 0;
    map->load_factor = 0;
    map->max_load_factor = 0.75;
    map->destructor = NULL;

    map_set_table_size(map, 
        (size > 0) ? size : MAP_DEFAULT_SIZE);

    return map;
}


int map_del(map_t* map){
    void* value;
    char* key;
    for(int i = 0; i < map->table_size; i++){
        while( (value = mlist_rem(&map->table[i], &key)) != NULL){
            if(map->destructor != NULL){
                map->destructor(key, value);
            }
        }
    }

    free(map->table);
    free(map);

    return 1;
}


int map_set(map_t* map, char* key, void* value){
    int pos;
    int ret = 0;

    if(value != NULL){
        if(map_get(map, key) == NULL){
            pos = map_default_hash(key, map->table_size);
            mlist_add(&map->table[pos], key, value);
            map->elem_count++;

            map->load_factor = ((float) map->elem_count) / map->table_size;

            if(map->load_factor > map->max_load_factor){
                map_set_table_size(map, (float) map->table_size * 1.2 + 1);
            }

            ret = 1;
        }
    }

    return ret;
}


void* map_get(map_t* map, char* key){
    int pos = map_default_hash(key, map->table_size);
    void* value = NULL;

    mlist_t* elem = map->table[pos];
    while(value == NULL && elem != NULL){
        if(strcmp(elem->key, key) == 0){
            value = elem->value;
        } else {
            elem = elem->next;
        }
    }

    return value;
}


int map_unset(map_t* map, char* key){
    int pos = map_default_hash(key, map->table_size);
    int result = 0;

    mlist_t *child = map->table[pos];
    mlist_t *parent = NULL;
    while(result == 0 && child != NULL){
        if(strcmp(key, child->key) == 0){
            if(map->destructor != NULL){
                map->destructor(child->key, child->value);
            }

            if(parent != NULL){
                parent->next = child->next;
            } else {
                map->table[pos] = NULL;
            }

            result = 1;

            free(child);
        } else {
            parent = child;
            child = child->next;
        }
    }

    return result;
}


int map_default_hash(char* key, int modulo){
    int h1 = 0xffff0000,
        h2 = 0x12ae13fa,
        h3 = 0x87d5a7bb;

    for(int i = 0; key[i] != '\0'; i++){
        h3 += (h1 * i) << (key[i] % 7);
        h2 += (h3 * i + h1 + key[i]);
        h1 += (h2 + h3) * (h2 - key[i] * i);
    }

    h1 += (h2 - h3);
    if(h1 < 0) h1 *= -1;

    return h1 % modulo;
}


int map_set_destructor(map_t* map, void (*delete)(char*, void*)){
    map->destructor = delete;
    return 1;
}


int map_set_table_size(map_t* map, int nsize){
    char *key;
    void *value;

    int osize = map->table_size;
    mlist_t** otable = map->table;

    map->table = calloc(nsize, sizeof(mlist_t*));
    assert_malloc(map->table, "new hash table for map");

    map->load_factor = 0;
    map->elem_count = 0;
    map->table_size = nsize;

    for(int i = 0; i < osize; i++){
        while((value = mlist_rem(&otable[i], &key)) != NULL){
           map_set(map, key, value);
        }
    }

    free(otable);

    return 1;
}

