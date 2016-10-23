#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert_malloc.h>
#include <types/map.h>
#include <types/mlist.h>

/**
 * map_new
 * @desc Create a new map with a table of size "size"
 * @param <int size> Size of the map (if 0, will use a default value)
 * @return <map_t*> A pointer to the map. Should be free'd using map_del(map_t*)
 **/
map_t* map_new(int size){
    map_t* map = malloc(sizeof(map_t));
    assert_malloc(map, "map");

    map->table = NULL;
    map->table_size = 0;
    map->load_factor = 0;
    map->max_load_factor = 0.75;
    map->min_load_factor = 0.6;
    map->destructor = NULL;

    map_set_table_size(map, 
        (size > 0) ? size : MAP_DEFAULT_SIZE);

    return map;
}


/**
 * map_del
 * @desc Free the map
 * @param <map_t* map> Map that will be free
 * @return <int> 1 on success
 **/
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


/**
 * map_set
 * @desc Link value with key in the map
 * @param <map_t* map>
 * @param @invariant <char* key>
 * @param @invariant <void* value> Value can't be NULL
 * @return <int> 1 on success,
 *         0 when key is already set, therefore value will not be inserted in the map
 **/
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
                map_set_table_size(map, (float) map->elem_count / map->min_load_factor + 1);
            }

            ret = 1;
        }
    }

    return ret;
}


/**
 * map_get
 * @desc Get value linked with the key
 * @param @invariant <map_t* map>
 * @param @invariant <char* key>
 * @return @invariant <void*> The value linked with key.
 *         If no couple (key, value) is found, return NULL.
 **/
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


/**
 * map_unset
 * @desc Remove the couple (key, value) from the map
 * @param <map_t* map>
 * @param @invariant <char* key>
 * @return 1 on success, 0 when (key, value) is not in the map
 **/
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

            map->load_factor = (float) map->elem_count / map->table_size;
            if(map->load_factor < map->max_load_factor){
                map_set_table_size(map, (float) map->elem_count / map->min_load_factor + 1);
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


/**
 * map_default_hash
 * @desc Get a hash h from key such as ( 0 <= h <= m )
 * @param @invariant <char* key>
 * @param <int modulo> 
 * @return <int>
 **/
int map_default_hash(char* key, int m){
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

    return h1 % m;
}


/**
 * map_set_destructor
 * @desc set the destructor of the map that will be called when a value will be removed
 *       (in map_unset and map_del). if destructor is NULL, no function is called
 * @param <map_t* map> 
 * @param <void (*delete)(char*, void*)> a function pointer that take a key and value in argument
 * @return 1 on success
 **/
int map_set_destructor(map_t* map, void (*delete)(char*, void*)){
    map->destructor = delete;
    return 1;
}


/**
 * map_set_table_size
 * @desc Set the size of the hash table and recalculate the hash of every element
 * @param <map_t* map>
 * @param <int nsize>
 * @return 1 on success
 **/
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

