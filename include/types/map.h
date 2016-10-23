#ifndef TYPES_MAP_H
#define TYPES_MAP_H

#include <types/mlist.h>

#define MAP_DEFAULT_SIZE 100

typedef struct {
    int elem_count;
    int table_size;

    float load_factor;
    float max_load_factor;

    void (*destructor)(char*, void*);

    mlist_t** table;
} map_t;

#define MAP_EXIST (void*) 1

map_t*  map_new(int initial_size);
int     map_del(map_t* map);
int     map_set(map_t* map, char* key, void* value);
void*   map_get(map_t* map, char* key);
int     map_unset(map_t* map, char* key);

int     map_set_destructor(map_t* map, void (*delete)(char*, void*));
int     map_set_table_size(map_t* map, int nsize);
int     map_default_hash(char* key, int modulo);

#endif // TYPES_MAP_H

