#include <stdlib.h>
#include <string.h>

#include <types/mlist.h>
#include <assert_malloc.h>

/**
 * mlist_add
 * @desc Add a couple (key, value) at the head of a list
 * @param <mlist_t** head_ptr> A pointer to a list element pointer
 * @param @invariant <char* key>
 * @param @invariant <void* value> Can't be NULL
 * @return 1 on success, 0 when value is NULL
 **/
int mlist_add(mlist_t** head_ptr, char* key, void* value){
    int status = 0;
    mlist_t* head = *head_ptr;
    mlist_t* new = malloc(sizeof(mlist_t));
    assert_malloc(new, "new list");

    if(value != NULL){
        new->key = key;
        new->value = value;
        new->next = head;
        *head_ptr = new;
        status = 1;
    }

    return status;
}


/**
 * mlist_rem
 * @desc Remove the first element of a list
 * @param <mlist_** head_ptr> A pointer to a list element pointer
 * @param <char** key> If key != NULL, return the value of the key
 * @return <void*> return the value of the first element or NULL when list is empty
 **/
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


/**
 * mlist_key_exist
 * @desc Check if a couple (key, value) exist in the list
 * @param @invariant <mlist_t* head>
 * @param @invariant <char* key>
 * @return 1 if key exist in the list, 0 otherwise
 **/
int mlist_key_exist(mlist_t* head, char* key){
    int status = 0;
    while(head != NULL && !status){
        if(head->key != NULL){
            status = (strcmp(key, head->key) == 0);
        }
        head = head->next;
    }
    return status;
}

