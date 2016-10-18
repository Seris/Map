#include <stdlib.h>
#include <types/mlist.h>
#include <assert_malloc.h>

int mlist_add(mlist_t** head_ptr, char* key, void* value){
    mlist_t* head = *head_ptr;
    mlist_t* new = malloc(sizeof(mlist_t));
    assert_malloc(new, "new list");

    new->key = key;
    new->value = value;
    new->next = head;

    *head_ptr = new;

    return 1;
}

void* mlist_rem(mlist_t** head_ptr, char** key){
    mlist_t* head = *head_ptr;
    void* ret = NULL;

    if(head != NULL){
        if(key != NULL) *key = head->key;
        ret = head->value;
        *head_ptr = head->next;
        free(head);
    }

    return ret;
}

int mlist_merge(mlist_t** head_ptr, mlist_t* tail){
    mlist_t* head = *head_ptr;

    if(head != NULL){
        while(head->next != NULL){
           head = head->next; 
        }
        head->next = tail;
    } else {
        *head_ptr = tail; 
    }

    return 1;
}

