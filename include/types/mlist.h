#ifndef TYPES_MLIST_H
#define TYPES_MLIST_H

typedef struct mlist_st {
    char*   key;
    void*   value;
    struct  mlist_st* next;
} mlist_t;

#define mlist_empty()   (mlist_t*) NULL
#define mlist_delete(l) while(mlist_rem(&l, NULL) != NULL);

int     mlist_add(mlist_t** head_ptr, char* key, void* value);
void*   mlist_rem(mlist_t** head_ptr, char** key);
int     mlist_merge(mlist_t** head_ptr, mlist_t *tail);
int     mlist_key_exist(mlist_t* head, char* key);


#define MLIST_EXIST (void*) 1

#endif // TYPES_MLIST_H

