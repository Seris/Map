#ifndef TYPES_MLIST_H
#define TYPES_MLIST_H

typedef struct mlist_st {
    char*   key;
    void*   value;
    struct  mlist_st* next;
} mlist_t;

#define mlist_empty() (mlist_t*) NULL
int     mlist_add(mlist_t** head_ptr, char* key, void* value);
void*   mlist_rem(mlist_t** head_ptr, char** key);
int     mlist_merge(mlist_t** head_ptr, mlist_t *tail);

#endif // TYPES_MLIST_H

