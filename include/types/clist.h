#ifndef MUSIC_TYPES_CLIST_H
#define MUSIC_TYPES_CLIST_H

#include <types/music.h>

typedef struct clist_st {
    music_t *music; 
    struct clist_st* next;
} clist_t;

#define     clist_new_empty() (clist_t*) NULL
clist_t*    clist_push(clist_t** list, music_t* music);
clist_t*    clist_unshift(clist_t** list, music_t* music);
int         clist_pop(clist_t** list, music_t** music);
int         clist_shift(clist_t** list, music_t** music);
int         clist_next(clist_t** list);
int         clist_count(clist_t* list);

#endif // MUSIC_TYPES_CLIST_H

