#ifndef TYPES_MAP_H
#define TYPES_MAP_H

#include <types/mlist.h>

typedef struct {
    int elem_count;
    int table_size;

    float load_factor;
    float max_load_factor;

    mlist_t** table;
} map_t;

map_t*  map_new(void);
int     map_del(map_t* map);
int     map_set(map_t* map, char* key, void* value);
void*   map_get(map_t* map, char* key);
void*   map_unset(map_t* map, char* key);

int     map_set_table_size(map_t* map, int nsize);
int     map_default_hash(char* key, int modulo);

#endif // TYPES_MAP_H

