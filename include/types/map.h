#ifndef MUSIC_TYPES_MAP_H
#define MUSIC_TYPES_MAP_H

#include <types/clist.h>
#include <types/music.h>

typedef struct map_st {
    int table_size;
    int elem_count;
    float max_load_factor;
    float current_load_factor;
    clist_t **table;
} map_t;

map_t*  map_create(void);
int     map_set(map_t* map, music_t* music);
int     map_get(map_t* map, char* title, music_t** music);
int     map_unset(map_t* map, char* title, music_t** music);
int     map_delete(map_t* map);
void    map_resize_to_fit(map_t* map);

void    map_show_stack(map_t* map);

#endif // MUSIC_TYPES_MAP_H

